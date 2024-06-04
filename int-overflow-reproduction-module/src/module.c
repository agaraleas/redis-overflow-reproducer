#include "../include/redismodule.h"
#include <stdio.h>

static void timerFired(RedisModuleCtx *ctx, void *data){
    RedisModule_Log(ctx, "notice", "Timer fired");
}

static int testCase1(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    //Test case 1. Create a timer and cancel it immediately
    //What should be printed is:
    RedisModuleTimerID timer_id = 0;
    RedisModule_AutoMemory(ctx);
    printf("-------Test case 1-------\n");
    printf("EXPECTED RESULTS ARE:\n");
    printf("No active timers\n");
    printf("Calculated next period: 0\n");
    printf("Next execution period is 0\n");
    printf("Next should repeat is 0\n");
    printf(">>>>>>>>>>> GOT <<<<<<<<<<\n");

    timer_id = RedisModule_CreateTimer(ctx, 5, timerFired, NULL);
    RedisModule_StopTimer(ctx, timer_id, NULL);

    RedisModule_ReplyWithSimpleString(ctx, "OK");
    return REDISMODULE_OK;
}

static int testCase2(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  //Test case 2. Create a timer that expires soon and let it fire
  //What should be printed is:
  RedisModuleTimerID timer_id = 0;
    RedisModule_AutoMemory(ctx);
    printf("-------Test case 2-------\n");
    printf("EXPECTED RESULTS ARE:\n");
    printf("removing timer\n");
    printf("<overflow> Timer fired\n");
    printf("No active timers\n");
    printf("Calculated next period: 0\n");
    printf("Next execution period is 0\n");
    printf("Next should repeat is 0\n");
    printf(">>>>>>>>>>> GOT <<<<<<<<<<\n");

    timer_id = RedisModule_CreateTimer(ctx, 5, timerFired, NULL);
    RedisModule_ReplyWithSimpleString(ctx, "OK");
    return REDISMODULE_OK;
}

static int testCase3(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  //Test case 3. Create two timers with really small interval
  //This tests tries to simulate the case of two timers having really small difference, which
  RedisModuleTimerID timer_id = 0;
    RedisModule_AutoMemory(ctx);
    printf("-------Test case 3-------\n");
    printf("EXPECTED RESULTS ARE:\n");
    printf("removing timer\n");
    printf("<overflow> Timer fired\n");
    printf("setting should repeat = true\n");
    printf("Calculated next period: 1\n");
    printf("Next execution period is 1\n");
    printf("Next should repeat is 1\n");
    printf("removing timer\n");
    printf("<overflow> Timer fired\n");
    printf("No active timers\n");
    printf("Calculated next period: 0\n");
    printf("Next execution period is 0\n");
    printf("Next should repeat is 0\n");
    printf(">>>>>>>>>>> GOT <<<<<<<<<<\n");

    timer_id = RedisModule_CreateTimer(ctx, 1, timerFired, NULL);
    timer_id = RedisModule_CreateTimer(ctx, 3, timerFired, NULL);
    RedisModule_ReplyWithSimpleString(ctx, "OK");
    return REDISMODULE_OK;
}

static int testCase4(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  //Test case 3. Create two timers with large difference in exp time to check fix of overflow
  //This tests tries to simulate the case of two timers having really small difference, which
  RedisModuleTimerID timer_id = 0;
    RedisModule_AutoMemory(ctx);
    printf("-------Test case 4-------\n");
    printf("EXPECTED RESULTS ARE:\n");
    printf("removing timer\n");
    printf("<overflow> Timer fired\n");
    printf("setting should repeat = true\n");
    printf("Calculated next period: ~2147583636\n");
    printf("Next execution period is ~2147583636\n");
    printf("Next should repeat is 1\n");
    printf(">>>>>>>>>>> GOT <<<<<<<<<<\n");

    timer_id = RedisModule_CreateTimer(ctx, 2147583647, timerFired, NULL);
    timer_id = RedisModule_CreateTimer(ctx, 10, timerFired, NULL);
    RedisModule_ReplyWithSimpleString(ctx, "OK");
    return REDISMODULE_OK;
}

static int testFinished(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    printf("-------Tests finished-------\n");
    RedisModule_CreateTimer(ctx, 1, timerFired, NULL);
    RedisModule_ReplyWithSimpleString(ctx, "OK");
    return REDISMODULE_OK;
}



int RedisModule_OnLoad(RedisModuleCtx *ctx) {
    // Register the module itself
    if (RedisModule_Init(ctx, "overflow", 1, REDISMODULE_APIVER_1) ==
        REDISMODULE_ERR) {
      return REDISMODULE_ERR;
    }

    if (RedisModule_CreateCommand(ctx, "overflow.testCase1", testCase1, "fast write",
                                  1, 1, 1) == REDISMODULE_ERR) {
      return REDISMODULE_ERR;
    }

    if (RedisModule_CreateCommand(ctx, "overflow.testCase2", testCase2, "fast write",
                                  1, 1, 1) == REDISMODULE_ERR) {
      return REDISMODULE_ERR;
    }

    if (RedisModule_CreateCommand(ctx, "overflow.testCase3", testCase3, "fast write",
                                  1, 1, 1) == REDISMODULE_ERR) {
      return REDISMODULE_ERR;
    }

      if (RedisModule_CreateCommand(ctx, "overflow.testCase4", testCase4, "fast write",
                                  1, 1, 1) == REDISMODULE_ERR) {
      return REDISMODULE_ERR;
    }

      if (RedisModule_CreateCommand(ctx, "overflow.testFinished", testFinished, "fast write",
                                  1, 1, 1) == REDISMODULE_ERR) {
      return REDISMODULE_ERR;
    }

  return REDISMODULE_OK;
}
