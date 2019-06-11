/*
	camera.cpp
	Primitives

	implementation of a basic camera
*/

#include "primitives.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
{
	this->position = pos;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	speed = 2.5;
	mouseSensitivity = 0.01;
	zoom = 45.0;
	updateVectors();
}

Camera::Camera()
{
	this->position = glm::vec3(0,0,0);
	this->worldUp = glm::vec3(0,1.0,0);
	this->yaw = -90.0;
	this->pitch = 0.0;
	speed = 2.5;
	mouseSensitivity = 0.1;
	zoom = 45.0;
	updateVectors();
}

// move along the X and Y axis
void Camera::moveXZ(MovementDirection dir, float dt)
{
	float velocity = speed * dt;
	
	switch(dir) {
	case FORWARD:
		position += front * velocity;
		break;
	case BACKWARD:
		position -= front * velocity;
		break;
	case LEFT:
		position -= right * velocity;
		break;
	case RIGHT:
		position += right * velocity;
		break;
	default:
		break;
	}
}

void Camera::mouseInput(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateVectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
    if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= yoffset;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
}

void Camera::updateVectors()
{
	 // Calculate the new Front vector
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(f);
    // Also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up    = glm::normalize(glm::cross(right, front));
}

// ---------------Getters---------------
glm::vec3 Camera::getCamPos()
{
	return position;
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(position, position + front, up);
}

float Camera::getX()
{
	return position[0];
}

float Camera::getY()
{
	return position[1];
}

float Camera::getZ()
{
	return position[2];
}

// ---------------Setters---------------
void Camera::setPos(glm::vec3 newPos)
{
	position = newPos;
}

void Camera::setX(float x)
{
	position[0] = x;
}

void Camera::setY(float y)
{
	position[1] = y;
}

void Camera::setZ(float z)
{
	position[2] = z;
}
