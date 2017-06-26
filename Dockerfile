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
    build-essential \
    make \
    cmake
RUN mkdir build && cd build && cmake .. && make

ENV DISPLAY=$DISPLAY
ENV XAUTHORITY=$XAUTHORITY

# Run the game
CMD ["deadlywish"]
