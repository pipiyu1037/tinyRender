#include "Camera.h"
#include "Input.h"
#include "MessageOut.h"
#include "GameObject.h"

void Camera::DisableReceive() {
    controlling = false;
    if (this == RenderBase::mainCamera.lock().get())
        glfwSetInputMode(RenderBase::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Camera::EnableReceive() {
    controlling = true;
    if (this == RenderBase::mainCamera.lock().get())
        glfwSetInputMode(RenderBase::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Camera::Update() {
    static float lastX = Input::GetMouseX();
    static float lastY = Input::GetMouseY();

    if (!controlling) {
        lastX = Input::GetMouseX();
        lastY = Input::GetMouseY();
        return;
    }

    Position = gameObject.transform.position + posOffset;

    float xoffset = Input::GetMouseX() - lastX;
    float yoffset = lastY - Input::GetMouseY(); // reversed since y-coordinates go from bottom to top
    lastX = Input::GetMouseX();
    lastY = Input::GetMouseY();

    Yaw += xoffset * MouseSensitivity;
    Pitch += yoffset * MouseSensitivity;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();

    // scroll
    Zoom -= (float)Input::GetScroll();
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 90.0f)
        Zoom = 90.0f;
}

void Camera::updateCameraVectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}
