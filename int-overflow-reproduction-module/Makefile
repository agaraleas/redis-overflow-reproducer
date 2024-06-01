#set environment variable INCLUDE_DIR to the location of redismodule.h
ifndef INCLUDE_DIR
	INCLUDE_DIR=./include
endif

ifndef SRC_DIR
	SRC_DIR=src
endif


all: module.so

module.so:
	$(MAKE) -C ./$(SRC_DIR)
	cp ./$(SRC_DIR)/module.so ./out/module.so

clean:
	rm -rf *.xo *.so *.o
	rm -rf ./$(SRC_DIR)/*.xo ./$(SRC_DIR)/*.so ./$(SRC_DIR)/*.o