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
    make && make install

# Expose the Redis port
EXPOSE 6379

# Start Redis
CMD ["redis-7.2.5/src/redis-server", "redis-7.2.5/redis.conf"]
