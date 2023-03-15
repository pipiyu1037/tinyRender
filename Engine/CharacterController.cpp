#include "CharacterController.h"
#include "Input.h"
#include "Time.h"
#include "Camera.h"
#include "GameObject.h"
#include <memory>

void CharacterController::Update() {
	static std::shared_ptr<Camera> 
		camera = gameObject.GetComponent<Camera>();
	if (Input::GetKey(Input::Key_W)) {
		glm::vec3 front = camera->Front;
		front.y = 0;
		front = glm::normalize(front);
		gameObject.transform.position += front * speed * Time::deltaTime;
	}
	if (Input::GetKey(Input::Key_S)) {
		glm::vec3 front = camera->Front;
		front.y = 0;
		front = glm::normalize(front);
		gameObject.transform.position -= front * speed * Time::deltaTime;
	}
	if (Input::GetKey(Input::Key_D)) {
		glm::vec3 right = camera->Right;
		right.y = 0;
		right = glm::normalize(right);
		gameObject.transform.position += right * speed * Time::deltaTime;
	}
	if (Input::GetKey(Input::Key_A)) {
		glm::vec3 right = camera->Right;
		right.y = 0;
		right = glm::normalize(right);
		gameObject.transform.position -= right * speed * Time::deltaTime;
	}

	static float verticalVelo = 0.0f;
	if (gameObject.transform.position.y == 0.0f) {
		verticalVelo = 0.0f;
		if (Input::GetKey(Input::Key_Space)) {
			verticalVelo = jumpForce;
			gameObject.transform.position.y += verticalVelo * Time::deltaTime;
		}
	}
	else {
		verticalVelo -= 9.8f * Time::deltaTime;
		gameObject.transform.position.y += verticalVelo * Time::deltaTime;
		if (gameObject.transform.position.y < 0.0f)
			gameObject.transform.position.y = 0.0f;
	}
}
