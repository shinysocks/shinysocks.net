import cors from "cors"
import fs from 'node:fs'
import express from "express"
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

const suid = new ShortUniqueId({ length: 6 })

const app = express()
const port = 8888

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

