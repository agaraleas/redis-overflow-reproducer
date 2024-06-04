#Build a docker image of redis server with assertion in case of overflow
docker build -t redis-with-overflow-fix .

#Schedule sending the commands that would cause the overflow in 5 seconds
echo "Scheduling sending of test commands in 5 seconds ... wait"
(sleep 3 && ./startTests.sh redis-patched) &

#Start the docker container 
docker run --name redis-patched -p 6379:6379 redis-with-overflow-fix