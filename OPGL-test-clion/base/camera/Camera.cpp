//
// Created by invoker on 2018/7/22.
//

#include <camera/Camera.h>
#include <Macro.h>

const glm::vec3 Camera::POSITION = glm::vec3(0.0f, 0.0f, 13.0f);
const glm::vec3 Camera::FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 Camera::UP = glm::vec3(0.0f, 1.0f, 0.0f);
const float Camera::PITCH = 0.0f;
const float Camera::YAW = -90.0f;
const float Camera::ROLL = 0.0f;
const float Camera::SPEED = 2.5f;
const float Camera::SENSITIVITY = 0.1f;
const float Camera::FOV = 45.0f;

Camera::Camera(const glm::vec3 &cameraPos, const glm::vec3 &cameraUp, const float pitch, const float yaw, const float roll, const float speed, const float sensitivity, const float fov)
       :position(cameraPos), front(Camera::FRONT), up(cameraUp), pitch(pitch), yaw(yaw), roll(roll), speed(speed), sensitivity(sensitivity), fov(fov) {
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(           // 摄像机将永远注视前方
            position,             // camera position
            position + front,     // camera target
            up                    // up
    );
}

void Camera::onMove(const Camera::Direction &direction, const float &deltaTime) {
    float velocity = speed * deltaTime;

    switch (direction) {
        case Direction::FORWARD:
            position += front * velocity;
            break;

        case Direction::BACKWARD:
            position -= front * velocity;
            break;

        case Direction::LEFT:
            position -= glm::normalize(glm::cross(front, up)) * velocity;
            break;
        case Direction::RIGHT:
            position += glm::normalize(glm::cross(front, up)) * velocity;
            break;

        default:
            // TODO: ljm >>> error log
            break;
    }

    position.y = 0.0f;
}

void Camera::onMouseMove(float xOffset, float yOffset, bool constrainPitch) {
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw   += xOffset;
    pitch += yOffset;

    UNUSED_PARAM((constrainPitch && (pitch = (pitch > 89.0f) ? 89.0f : ((pitch < -89.0f) ? -89.0f : pitch))));

    updateCameraVectors();
}

void Camera::onZoom(const float yOffset) {
    fov -= yOffset;
    fov = (fov < 1.0f) ? 1.0f : ((fov > 45.0f) ? 45.0f : fov);

    updateCameraVectors();
}

float Camera::getFov() const {
    return fov;
}

void Camera::updateCameraVectors() {
    glm::vec3 vec;
    vec.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    vec.y = sin(glm::radians(pitch));
    vec.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    front = glm::normalize(vec);
}
