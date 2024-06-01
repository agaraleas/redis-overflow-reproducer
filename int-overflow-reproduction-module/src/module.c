#include "../include/redismodule.h"

int RunDummyCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  RedisModule_ReplyWithSimpleString(ctx, "OK");
  return REDISMODULE_OK;
}


int RedisModule_OnLoad(RedisModuleCtx *ctx) {

  // Register the module itself
  if (RedisModule_Init(ctx, "overflow", 1, REDISMODULE_APIVER_1) ==
      REDISMODULE_ERR) {
    return REDISMODULE_ERR;
  }

  // register overflow.CreateTimer to be able to create custom timers
  if (RedisModule_CreateCommand(ctx, "overflow.RunDummyCommand", RunDummyCommand, "fast write",
                                1, 1, 1) == REDISMODULE_ERR) {
    return REDISMODULE_ERR;
  }

  return REDISMODULE_OK;
}
