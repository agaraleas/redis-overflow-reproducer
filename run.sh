docker build -t redis-with-overflow .
docker run -d --name redis-with-overflow -p 6379:6379 redis-with-overflow
docker exec -ti redis-with-overflow redis-cli overflow.reproduce