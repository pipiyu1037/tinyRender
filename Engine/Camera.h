#pragma once

#include "Component.h"
#include "IMouseReceiver.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class RenderBase;

class Camera : 
    public Component,
    public IMouseReceiver
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MouseSensitivity;
    float Zoom;

    Camera(GameObject& gameObject,
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw = -90.0f, float pitch = 0.0f) : 
                Component(gameObject, "Camera"),
                Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
                MouseSensitivity(0.1f), 
                Zoom(45.0f) {
        posOffset = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        controlling = false;
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void DisableReceive() override;
    void EnableReceive() override;

    void Update() override;

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();

    glm::vec3 posOffset;
    bool controlling;
};

