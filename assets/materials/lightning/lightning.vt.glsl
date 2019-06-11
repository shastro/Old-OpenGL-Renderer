#version 330 core

	attribute vec3 aPosition;
	attribute vec3 aNormal;

	varying vec3 vEye;
	varying vec4 vNormal;
	varying vec4 zunit;

	uniform mat4 mProjection;
	uniform mat4 mModel;
	uniform mat4 mView;

	mat4 MVP =  mProjection * mView * mModel;

	void main(){

		zunit = vec4(0.0f, 0.0f, 0.0f, 1.0f);

		zunit =  mView * mModel * normalize(zunit);

		vNormal = mModel * vec4(aNormal, 1.0f);
		//Depricated
		//vEye = aPosition;

		vec4 position = MVP * vec4(aPosition, 1.0);

		gl_Position = position;  /*+ vec4(-0.5f, 0.75f, 0.0f, 0.0f))*/
		
	}
