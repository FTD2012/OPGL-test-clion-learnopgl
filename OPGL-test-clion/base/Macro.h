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
#undef SHOW_FPS

#ifdef DEBUG
    #define ASSERT(cond, msg) do {                              \
                if (!(cond)) {                                  \
                    printf("Assert failed: %s", msg);           \
                }                                               \
            } while (0)
#else
    #define ASSERT(cond, msg)
#endif

#endif //OPGL_TEST_CLION_MACRO_H
