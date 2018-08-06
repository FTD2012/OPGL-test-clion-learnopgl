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
    return calculateLookAtMatrix(
            position,
            position + front,
            up
            );
//    return glm::lookAt(           // 摄像机将永远注视前方
//            position,             // camera position
//            position + front,     // camera target
//            up                    // up
//    );
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

glm::vec3 Camera::getPosition() const {
    return position;
}

void Camera::updateCameraVectors() {
    glm::vec3 vec;
    vec.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    vec.y = sin(glm::radians(pitch));
    vec.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    front = glm::normalize(vec);
}

glm::mat4 Camera::calculateLookAtMatrix(const glm::vec3 position, const glm::vec3 target, const glm::vec3 up) const {
    // 1. Position = known
    // 2. Calculate cameraDirection
    glm::vec3 zAxis = glm::normalize(position - target);
    // 3. Get positive right axis vector
    glm::vec3 xAxis = glm::normalize(glm::cross(glm::normalize(up), zAxis));
    // 4. Calculate camera up vector
    glm::vec3 yAxis = glm::cross(zAxis, xAxis);

    // Create translation and rotation matrix
    // In glm we access elements as mat[col][row] due to column-major layout
    glm::mat4 translation, rotation; // Identity matrix by default
    translation[3][0] = -position.x; // Third column, first row
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;
    rotation[0][0] = xAxis.x; // First column, first row
    rotation[1][0] = xAxis.y;
    rotation[2][0] = xAxis.z;
    rotation[0][1] = yAxis.x; // First column, second row
    rotation[1][1] = yAxis.y;
    rotation[2][1] = yAxis.z;
    rotation[0][2] = zAxis.x; // First column, third row
    rotation[1][2] = zAxis.y;
    rotation[2][2] = zAxis.z;

    return rotation * translation;
}
