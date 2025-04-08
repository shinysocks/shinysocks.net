FROM denoland/deno:alpine
WORKDIR /shinysocks.net
COPY . .
CMD ["deno", "run", "-A", "src/app.js"]
