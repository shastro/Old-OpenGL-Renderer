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
	
		c1 = 0.6f;
		color.x = ((c1/(val))/0.5f + (c1/(val2))/6.0f)    ;
		color.y = ((c1/(val))/5.0f + (c1/(val2))/6.0f)    ;
		color.z = ((c1/(val))/2.3f + (c1/(val2))/1.0f)    ;

		gl_FragColor = vec4(color, 1.0);
	}
