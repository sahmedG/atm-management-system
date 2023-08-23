# Use an official PostgreSQL image as the base image
FROM postgres:latest

# Set environment variables for PostgreSQL
ENV POSTGRES_DB atm_system
ENV POSTGRES_USER postgres
ENV POSTGRES_PASSWORD password

# Install necessary build tools and libraries
RUN apt-get update && \
    apt-get install -y build-essential libpq-dev libsqlite3-dev libncurses5-dev libssl-dev

# Set up a working directory for your application
WORKDIR /app

# Copy your application files to the container
COPY atm-management-system /app

# Build and install your application
RUN make -C /app atm.exe

# Start your application (replace with actual start command)
CMD ["/app/atm.exe"]

# Expose the necessary port (if your application listens on a specific port)
EXPOSE 8080
