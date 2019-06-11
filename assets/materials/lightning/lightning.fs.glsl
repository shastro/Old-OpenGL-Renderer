#version 330 core

	varying vec4 vNormal;
	varying vec3 vEye;
	varying vec4 zunit;

	vec3 color;


	//out vec4 outColor;
	float c1;
	void main(){

		vec3 ve;
		ve.x = zunit.x;
		ve.y = zunit.y;
		ve.z = zunit.z;

		vec3 vn;
		vn.x = vNormal.x;
		vn.y = vNormal.y;
		vn.z = vNormal.z;

		float val  = length( dot  (ve,   vn));
		float val2 = length( cross(ve,   vn));
	
		float dr = 1.4 / 3.0f;
		float dg = 0.2 / 3.0f;
		float db = 0.6 / 3.0f;

		float cr = 0.1;
		float cg = 0.1;
		float cb = 0.5;

		color.x = dr/val + cr/val2   ;
		color.y = dg/val + cg/val2   ;
		color.z = db/val + cb/val2   ;

		gl_FragColor = vec4(color, 1.0);
	}
