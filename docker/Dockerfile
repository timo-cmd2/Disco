FROM ubuntu:latest

WORKDIR Rift

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update 
RUN apt-get install -y --no-install-recommends build-essential
RUN apt-get update
RUN apt-get install -y --no-install-recommends cmake libcurl4-gnutls-dev \
RUN apt-get install -y gcc
RUN apt-get install -y make
RUN rm -rf /var/lib/apt/lists/*

COPY CMakeLists.txt .
COPY sources ./src/
COPY tests ./tests/

# more stuff to come soon xD
# ... too lazy
