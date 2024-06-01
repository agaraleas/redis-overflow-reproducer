FROM registry.access.redhat.com/ubi8/ubi:latest

# Install necessary packages
RUN yum update -y && \
    yum install -y gcc make wget

# Download and extract Redis
RUN wget http://download.redis.io/releases/redis-7.2.5.tar.gz && \
    tar xzf redis-7.2.5.tar.gz && \
    rm redis-7.2.5.tar.gz

# Build Redis
RUN cd redis-7.2.5 && \
    make && \ 
    make install && \
    make clean

#Build versioning module that reproduces the integer overflow
COPY int-overflow-reproduction-module int-overflow-reproduction-module
RUN cd int-overflow-reproduction-module && \
    make && \
    make clean

# Copy the Redis configuration file
COPY redis.conf redis-7.2.5/redis.conf

# Expose the Redis port
EXPOSE 6379

# Start Redis
CMD ["/usr/local/bin/redis-server", "redis-7.2.5/redis.conf"]
