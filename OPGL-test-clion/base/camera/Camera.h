//
// Created by invoker on 2018/7/22.
//

#ifndef OPGL_TEST_CLION_CAMERA_H
#define OPGL_TEST_CLION_CAMERA_H

#include <external/glm/glm.hpp>
#include <external/glm/gtc/matrix_transform.hpp>
#include <external/glm/gtc/type_ptr.hpp>

class Camera {

public:

    /**
     * 摄像机移动方向
     */
    enum Direction {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

public:
    explicit Camera(
            const glm::vec3 &cameraPos = Camera::POSITION,
            const glm::vec3 &cameraUp  = Camera::UP,
            float pitch = Camera::PITCH,
            float yaw = Camera::YAW,
            float roll = Camera::ROLL,
            float speed = Camera::SPEED,
            float sensitivity = Camera::SENSITIVITY,
            float fov = Camera::FOV
    );

    /**
     * 获得摄像机的lookAt矩阵
     * @return {glm::mat4} lookAt
     */
    glm::mat4 getViewMatrix() const;

    /**
     * 使用键盘WASD上下左右移动
     * @param direction
     * @param deltaTime
     */
    void onMove(const Camera::Direction &direction, const float &deltaTime);

    /**
     * 使用鼠标转动
     * @param xOffset 鼠标x轴位移
     * @param yOffset 鼠标y轴位移
     * @param constrainPitch[=true] 是否固定俯仰角
     */
    void onMouseMove(float xOffset, float yOffset, bool constrainPitch = true);

    /**
     * 使用鼠标滚轮缩放
     * @param yOffset 鼠标滚轮y轴位移
     */
    void onZoom(float yOffset);

    /**
     * get fov
     * @return fov
     */
    float getFov() const;

    glm::vec3 getPosition() const;
    glm::vec3 getFront() const;

private:
    void updateCameraVectors();

    glm::mat4 calculateLookAtMatrix(glm::vec3 position, glm::vec3 target, glm::vec3 up) const;
    
private:
    /**
     * 摄像机在世界坐标系中的位置
     */
    glm::vec3 position;

    /**
     * 摄像机观察的位置
     */
    glm::vec3 front;

    /**
     * 摄像机上方
     */
    glm::vec3 up;

    /**
     * 俯仰角
     */
    float pitch;

    /**
     * 偏转角
     */
    float yaw;

    /**
     * 滚转角
     */
    float roll;

    /**
     * 摄像机移动速度 使用键盘W、A、S、D时
     */
    float speed;

    /**
     * 鼠标灵敏度
     */
    float sensitivity;

    /**
     * 摄像机视窗范围
     */
     float fov;


private:
    /**
     * 宏定义
     */
    static const glm::vec3 POSITION;
    static const glm::vec3 FRONT;
    static const glm::vec3 UP;
    static const float PITCH;
    static const float YAW;
    static const float ROLL;
    static const float SPEED;
    static const float SENSITIVITY;
    static const float FOV;

};


#endif //OPGL_TEST_CLION_CAMERA_H



























