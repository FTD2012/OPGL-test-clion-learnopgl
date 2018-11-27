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

#ifdef DEBUG
    #define CHECK_GL_ERROR_DEBUG() \
    do { \
        GLenum __error = glGetError(); \
        if(__error) { \
            printf("OpenGL error 0x%04X in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__); \
        } \
    } while (false)
#else
    #define CHECK_GL_ERROR_DEBUG()
#endif

#endif //OPGL_TEST_CLION_MACRO_H
