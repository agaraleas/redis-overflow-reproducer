This repository aims to reproduce an int overflow of redis 
happening when redis server processes time events of module

Prequisities:
- Linux
- Docker

How to use:
Clone the repository locally
Run shell script run.sh

What it does:
- Script will fetch and build latest redis version (at the time when it was written)
Before building, redis will be patched with an assertion to ease the investigation
The assertion is added in line 332 of ae.c and tests that return value will be >= -1
- A versioning module is also built with only a function to create timers
- When run.sh is executed, it adds 2 timers with such timeout values that will cause an overflow 