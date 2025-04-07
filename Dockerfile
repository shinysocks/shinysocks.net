FROM denoland/deno:alpine
WORKDIR /shinysocks.net
COPY . .
CMD ["make"]
