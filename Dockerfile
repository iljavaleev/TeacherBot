FROM ubuntu:latest

WORKDIR /usr/src/cppbot
COPY . .


RUN apt-get update -y \
    && apt-get install -y clang binutils \
    && apt-get install -y build-essential cmake libboost-system-dev libssl-dev zlib1g-dev libcurl4-openssl-dev git

RUN git clone https://github.com/reo7sp/tgbot-cpp \
    && cd tgbot-cpp \
    && cmake . \
    && make -j4 \
    && make install \
    && cd ..

RUN apt-get install -y libpq-dev libpqxx-dev 

RUN mkdir build \
    && cd build \
    && cmake .. \
    && make \
    && chmod +x ./cppbot

CMD ["/usr/src/cppbot/build/cppbot"]