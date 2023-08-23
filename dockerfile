# Use a base image with necessary dependencies
FROM ubuntu:latest

# Install required packages
RUN apt-get update && \
    apt-get install -y \
    gcc \
    libsqlite3-dev \
    libncurses5-dev \
    libssl-dev \
    postgresql-client \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /app

# Copy the source code and Makefile into the container
COPY . /app

# Compile your code
RUN make

# Set the entry point
CMD ["./atm.exe"]
