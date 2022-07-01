#include "Camera/Camera.h"
void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch) noexcept{}
void Camera::ProcessMouseScroll(float yOffset) noexcept {}
void Camera::ProcessKeyboard(Camera::Movement direction, float deltaTime){}
void Camera::OnPause() {Pausable::OnPause();}
void Camera::OnResume() {Pausable::OnResume();}
