FROM debian:jessie AS build-env
WORKDIR /app

RUN apt-get update 
RUN apt-get install -y build-essential make libc6-dev libc6-dev-i386 wget unzip
RUN apt-get clean

COPY . ./

RUN ./setup.sh

CMD ./launch.sh

EXPOSE 8000

