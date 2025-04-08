FROM denoland/deno:alpine
WORKDIR /shinysocks.net
COPY . .
RUN apk add --no-cache make
CMD ["make"]
