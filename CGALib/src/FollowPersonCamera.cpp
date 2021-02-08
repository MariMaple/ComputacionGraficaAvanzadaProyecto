#include "Headers/FollowPersonCamera.h"

FollowPersonCamera::FollowPersonCamera(glm::vec3 position, glm::vec3 worldUp,
	glm::vec3 front, float yaw, float pitch, float speed, float sensitivity) {
	this->yaw = yaw;
	this->pitch = pitch;
	this->speed = speed;
	this->sensitivity = sensitivity;
	this->position = position;
	this->front = front;
	this->worldUp = worldUp;
	updateCamera();
}

void FollowPersonCamera::mouseMoveCamera(float xoffset, float yoffset, float dt) {
	xoffset *= dt * sensitivity;
	yoffset *= -1 * dt * sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	updateCamera();
}

void FollowPersonCamera::scrollMoveCamera(float soffset, float dt) {
}

void FollowPersonCamera::updateCamera() {
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	this->front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front.y = sin(glm::radians(pitch));
	this->front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(this->front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}

void FollowPersonCamera::moveFrontCamera(bool dir, float dt) {
	if (dir)
		this->position += (float)dt * speed * this->front;
	else
		this->position -= (float)dt * speed * this->front;
	updateCamera();
}

void FollowPersonCamera::moveRightCamera(bool dir, float dt) {
	if (dir)
		this->position += (float)dt * speed * this->right;
	else
		this->position -= (float)dt * speed * this->right;
	updateCamera();
}
