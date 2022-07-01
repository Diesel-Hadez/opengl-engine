#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>

class Camera {
private:
public:
    enum class Movement { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };
public:
    virtual void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true) noexcept;
    virtual void ProcessMouseScroll(float yOffset) noexcept;
    virtual void ProcessKeyboard(Camera::Movement direction, float deltaTime);
    virtual glm::mat4 GetViewMatrix() const noexcept = 0;
    virtual void OnPause();
    virtual void OnResume();
    Camera() = default;
    virtual ~Camera() = default;
};

#endif
