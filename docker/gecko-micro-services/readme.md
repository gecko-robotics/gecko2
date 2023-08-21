# Docker Micro Services for Gecko

This is a simple way to do it using Alpine Linux with the image

- Pub: ![Docker Image Size (tag)](https://img.shields.io/docker/image-size/walchko/alpine-gecko-pub/latest)
- Sub: ![Docker Image Size (tag)](https://img.shields.io/docker/image-size/walchko/alpine-gecko-sub/latest)

## Usage with `docker-compose`

- `docker-compose build`
- `docker-compose up`

You can use `docker exec -it alpine-gecko-sub /bin/sh` to create
another `sh` terminal login on sub ... can do the same on pub too.

## Usage with `docker`

- local: `docker run -it --rm walchko/alpine-gecko /bin/sh`
- start daemon: `docker run -d -it walchko/alpine-gecko`
- stop daemon: `docker stop friendly_jang`
- join local/daemon: `docker exec -it friendly_jang /bin/sh`

However, notice, the name is now some random thing instead of what
was set inside the `docker-compose.yml`.

```
docker ps
CONTAINER ID   IMAGE                  COMMAND     CREATED         STATUS         PORTS     NAMES
16b9bb597c56   walchko/alpine-gecko   "/bin/sh"   7 seconds ago   Up 5 seconds   22/tcp    friendly_jang
```
