//
// Created by lvjiaming on 2018/10/15.
//

#ifndef OPGL_TEST_CLION_CONSTANT_H
#define OPGL_TEST_CLION_CONSTANT_H

/**
 * 图片渲染效果
 */
enum class Filter: int {
    INVERSION,              // 反相
    GRAY_SCALE,             // 灰度
    KERNEL,                 // 核效果(kernel, 卷积矩阵 Convolution Matrix)
    KERNEL_BLUR,            // 核效果-模糊
    KERNEL_EDGE_DETECTION   // 核效果-边缘检测
};

#endif //OPGL_TEST_CLION_CONSTANT_H
