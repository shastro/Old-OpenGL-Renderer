#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"


class Camera {


private:


public:

	//Orientation Properties
	glm::vec3 Position;
	glm::vec3 Target;
	glm::vec3 Heading;


	//The all important World to View Matrix
	glm::mat4 viewMat;


	//Orientation Vectors
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;


	//Angles for ease of control
	float Yaw;
	float Pitch;

	//FPS interactivity, defunct currently

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	//Position and Target in World Space (IE after model transform)
	Camera(glm::vec3 ipos, glm::vec3 itarget) {

		MovementSpeed = 0.07;


		Position = ipos;
		Target  = itarget;
		Heading = glm::normalize(Position - Target);

		viewMat = glm::mat4(1.0f);
		defineCameraSpace();
		
	}

private:
	void UpdateCameraSpace()
	{

        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        // Also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up    = glm::normalize(glm::cross(Right, Front));
	}

public:
	void lookat(glm::vec3 itarget)
	{
		viewMat = glm::lookAt(Position, itarget, Up);
	}

	//Setters

	void setPos(glm::vec3 ipos)
	{
		Position = ipos;
	}

	void setTarget(glm::vec3 itarget)
	{
		Target = itarget;
	}

	//Getters

	glm::mat4 getViewMat()
	{
		return viewMat;
	}

	//Input


};







#endif