#include "../include/redismodule.h"

static void timerFired(RedisModuleCtx *ctx, void *data){
    RedisModule_Log(ctx, "notice", "Timer fired");
}

static int reproduce(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModuleTimerID timer_id = 0;
    
    RedisModule_AutoMemory(ctx);

    timer_id = RedisModule_CreateTimer(ctx, 2147583647000, timerFired, NULL);
    if (timer_id == 0) {
      return RedisModule_ReplyWithError(ctx, "ERR could not create timer");
    }

    timer_id = RedisModule_CreateTimer(ctx, 5, timerFired, NULL);
    if (timer_id == 0) {
      return RedisModule_ReplyWithError(ctx, "ERR could not create timer");
    }

    RedisModule_ReplyWithSimpleString(ctx, "OK");
    return REDISMODULE_OK;
}


int RedisModule_OnLoad(RedisModuleCtx *ctx) {
  // Register the module itself
  if (RedisModule_Init(ctx, "overflow", 1, REDISMODULE_APIVER_1) ==
      REDISMODULE_ERR) {
    return REDISMODULE_ERR;
  }

  // register overflow.reproduce to recreate the problem on demand
  if (RedisModule_CreateCommand(ctx, "overflow.reproduce", reproduce, "fast write",
                                1, 1, 1) == REDISMODULE_ERR) {
    return REDISMODULE_ERR;
  }

  return REDISMODULE_OK;
}
