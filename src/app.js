import cors from "cors"
import fs from 'node:fs'
import express from "express"
import { refreshTunes, shuffle, recentSongs, } from './music.js'
import { getMeme, refreshMemes } from './meme.js'
import ShortUniqueId from "short-unique-id"
import path from "path"
import pino from "pino"
import pretty from "pino-pretty"
import compression from "compression"

const stream = pretty({
  colorize: true
})

export const log = pino(stream)

const __dirname = path.resolve()

export const TUNES_PATH = path.join(__dirname, 'public', 'tunes', '/')
export const MEMES_PATH = path.join(__dirname, 'public', 'memes', '/')

const SHARE_URL = "https://shinysocks.net/s/"
const suid = new ShortUniqueId({ length: 6 })

const app = express()
const port = 8888

log.info(`found ${refreshTunes()} tunes 🎶`)
log.info(`found ${refreshMemes()} memes 🤪`)

// refresh tunes every 5 minutes
setInterval(refreshTunes, 1000 * 60 * 5)

app.use(cors(), express.json(), compression({ level: 9, threshold: 512 }))
app.use('/s', express.static(path.join(__dirname, 'public', 'share')))

app.get('/', (req, res) => {
  // shinysocks.net homepage route
  try {
    const userAgent = req.headers['user-agent']
    if (userAgent.includes('curl')) {
      res.status(200).sendFile(path.join(__dirname, 'public', 'static', 'index'))
      log.info("terminal query! 🐚")
    } else {
      res.status(200).sendFile(path.join(__dirname, 'public', 'static', 'index.html'))
    }
  } catch (err) {
    res.status(200).sendFile(path.join(__dirname, 'public', 'static', 'index.html'))
    log.error("probably no user agent", err)
  }
})

app.get('/logo.png', (_req, res) => res.sendFile(path.join(__dirname, 'public', 'static', 'logo.png')))

app.get('/robots.txt', (_req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'static', 'robots.txt'))
  log.info("bot found! 🤖")
})

app.get('/t/:query?', (req, res, next) => {
  // t (tunes) route streams a random file
  const song = shuffle(req.params.query)
  if (song) {
    res.sendFile(path.join(TUNES_PATH + song.song))
  } else {
    log.error("tunes query returned no matches")
    next()
  }
})

app.get('/recentsongs', (_req, res) => {
  // grabs recent songs
  res.send(recentSongs())
})

app.get('/meme', (_req, res) => {
  // grab random meme
  const meme = getMeme()
  res.setHeader('meme', meme)
  res.sendFile(path.join(MEMES_PATH, meme))
})

app.put('/up', (req, res) => {
  let filename = req.headers["name"];
  let message = `uploaded ${filename}`

  if (filename == undefined) {
    filename = suid.rnd() + ".txt"
    message = `no "name" header provided, uploaded ${filename}`
  } else {
    for (const entry of Deno.readDirSync(path.join(__dirname, 'public', 'share'))) {
      if (filename == entry.name) {
        filename = suid.rnd() + "." + req.headers['name'].split(".")[1]; 
        message = `${req.headers['name']} already exists, uploaded ${filename}`
      }
    }
  }

  const filepath = path.join(__dirname, 'public', 'share', filename)
  const stream = fs.createWriteStream(filepath)

  req.pipe(stream).on('finish', () => {
    res.send(message)
    log.info(message)
  }).on('error', () => {
    res.status(500).send('upload failed.')
    log.error("file upload failed")
  })
})

app.get('*', (req, res) => {
  log.warn(`client recieved not found: ${req.originalUrl}`)
  res.status(404).send("not found")
})

app.listen(port, () => {
  log.info(`shinysocks.net started on port ${port}! 🚀`)
})

