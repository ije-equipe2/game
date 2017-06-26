FROM debian:jessie

ADD . /home/game

USER game

WORKDIR /home/game

# Install deadly-wish dependency
RUN apt-get update
RUN apt-get install -y \
    libsdl2-dev \
    libsdl2-ttf-dev \
    libsdl2-image-dev \
    libsdl2-mixer-dev \
    build-essential
RUN cd ijengine && tar -vzxf ijengine.tar.gz && make && make install
RUN mkdir libs && cp ijengine/kernel/sdl2/kernel.so.0.1.0 libs/
RUN make

ENV DISPLAY=$DISPLAY
ENV XAUTHORITY=$XAUTHORITY

# Run the game
CMD ["./bin/ije02_game"]
