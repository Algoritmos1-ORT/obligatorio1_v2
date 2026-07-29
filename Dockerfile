FROM debian:bookworm-slim

RUN apt-get update \
    && apt-get install --yes --no-install-recommends cmake g++ make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["bash"]
