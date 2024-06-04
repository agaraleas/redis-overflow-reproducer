FROM registry.access.redhat.com/ubi8/ubi:latest

# Install necessary packages
RUN yum update -y && \
    yum install -y gcc make wget git

# Download and extract Redis
RUN git clone https://github.com/agaraleas/redis.git redis-patched && \
    cd redis-patched && \
    git checkout fix-int-overflow

# These files contain some debug prints to validate that everything works as intended 
# since redis does not uses any unit test framework to test at function level
COPY ae.c redis-patched/src/ae.c
COPY module.c redis-patched/src/module.c

# Build Redis
RUN cd redis-patched && \
    make && \ 
    make install && \
    make clean

#Build versioning module that reproduces the integer overflow
COPY int-overflow-reproduction-module int-overflow-reproduction-module
RUN cd int-overflow-reproduction-module && \
    make && \
    make clean

# Copy the Redis configuration file
COPY redis.conf redis-patched/redis.conf

# Expose the Redis port
EXPOSE 6379

# Start Redis
CMD ["/usr/local/bin/redis-server", "redis-patched/redis.conf"]
