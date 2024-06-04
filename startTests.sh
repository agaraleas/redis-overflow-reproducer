#!/bin/bash
container="$1"

echo "Executing tests... please wait"
ret=$(docker exec $container redis-cli overflow.testCase1)
sleep 2
ret=$(docker exec $container redis-cli overflow.testCase2)
sleep 2
ret=$(docker exec $container redis-cli overflow.testCase3)
sleep 2
ret=$(docker exec $container redis-cli overflow.testCase4)
sleep 2
ret=$(docker exec $container redis-cli overflow.testFinished)
echo "All tests finished"
