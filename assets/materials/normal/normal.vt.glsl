#version 330 core

	attribute vec3 aPosition;
	attribute vec3 aNormal;

	varying vec4 vNormal;

	uniform mat4 mProjection;
	uniform mat4 mModel;
	uniform mat4 mView;

	mat4 MVP =  mProjection * mView * mModel;
	mat4 MV = mView * mModel;

	void main(){

		vNormal = vec4(aNormal, 1.0f);

		vec4 position = MVP * vec4(aPosition, 1.0);

		gl_Position = position;
		
	}
