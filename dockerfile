# Use an official PostgreSQL image as the base image
FROM postgres:latest

# Set environment variables for PostgreSQL
ENV POSTGRES_DB atm_system
ENV POSTGRES_USER postgres
ENV POSTGRES_PASSWORD password

# Install necessary build tools and libraries
RUN apt-get update && \
    apt-get install -y \
    gcc \
    make \
    libsqlite3-dev \
    libncurses5-dev \
    libssl-dev \
    postgresql-client \
    && rm -rf /var/lib/apt/lists/*
# Install PostgreSQL and create the database
RUN service postgresql start && \
    sudo -u postgres psql -c "CREATE DATABASE atm_system;" && \
    service postgresql stop

# Copy and execute the SQL commands to create tables
COPY setup.sql /app/setup.sql
RUN service postgresql start && \
    sudo -u postgres psql -d atm_system -a -f setup.sql && \
    service postgresql stop

# Set up a working directory for your application
WORKDIR /app

# Copy your application files to the container
COPY . /app

# Build and install your application
RUN make

# Start your application (replace with actual start command)
CMD ["./atm.exe"]

# Expose the necessary port (if your application listens on a specific port)
EXPOSE 8080
