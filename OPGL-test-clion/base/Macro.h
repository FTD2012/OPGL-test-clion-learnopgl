//
// Created by invoker on 2018/7/21.
//

#ifndef OPGL_TEST_CLION_MACRO_H
#define OPGL_TEST_CLION_MACRO_H

#include <cassert>
#include <iostream>

#define UNUSED_PARAM(unusedParam) (void)unusedParam
#define DEBUG 1
//#undef  DEBUG

#define SHOW_FPS
//#undef SHOW_FPS

#ifdef DEBUG
    #define ASSERT(cond, msg) do {                              \
                if (!(cond)) {                                  \
                    printf("Assert failed: %s", msg);           \
                    assert(false);                              \
                }                                               \
            } while (0)

    #define BREAK_IF(condition)                                 \
                if (!!(condition)) {                            \
                    break;                                      \
                }

    #define BREAK_IF_ERR_LOG(condition, msg)                    \
                if (!!(condition)) {                            \
                    printf("Break failed: %s", msg);            \
                }

#else
    #define ASSERT(cond, msg)
    #define BREAK_IF(condition)
    #define BREAK_IF_ERR_LOG(condition, msg)
#endif


#endif //OPGL_TEST_CLION_MACRO_H
