FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    libsdl2-dev \
    libsdl2-image-dev \
    libsdl2-mixer-dev \
    libsdl2-ttf-dev

WORKDIR /app

COPY . .

WORKDIR /app/MonkeyDave

CMD ["bash"]