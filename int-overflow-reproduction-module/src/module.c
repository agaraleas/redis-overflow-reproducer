#include "../include/redismodule.h"

static void timerFired(RedisModuleCtx *ctx, void *data){
    RedisModule_Log(ctx, "notice", "Timer fired");
}

static int createTimer(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModuleTimerID timer_id = 0;
    long long timeout = 0;
    
    RedisModule_AutoMemory(ctx);

    if (RedisModule_StringToLongLong(argv[1], &timeout) != REDISMODULE_OK) {
      return RedisModule_ReplyWithError(ctx, "ERR invalid timeout");
    }

    timer_id = RedisModule_CreateTimer(ctx, timeout, timerFired, NULL);
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

  // register overflow.createTimer to add custom timers that help on investigation
  if (RedisModule_CreateCommand(ctx, "overflow.createTimer", createTimer, "fast write",
                                1, 1, 1) == REDISMODULE_ERR) {
    return REDISMODULE_ERR;
  }

  return REDISMODULE_OK;
}
