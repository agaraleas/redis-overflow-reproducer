#Build a docker image of redis server with assertion in case of overflow
docker build -t redis-with-overflow .

#Schedule sending the commands that would cause the overflow in 5 seconds
echo "Scheduling sending of overflow commands in 5 seconds ... wait"
(sleep 5 && \
 docker exec redis-with-overflow redis-cli overflow.createTimer 2147583647 && \
 docker exec redis-with-overflow redis-cli overflow.createTimer 10) &

#Start the docker container 
docker run --name redis-with-overflow -p 6379:6379 redis-with-overflow