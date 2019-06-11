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

		ve = normalize(ve);
		vn = normalize(vn);


		float val1 =         dot  (ve,   vn);
		float val2 = length( cross(ve,   vn));
	
		// float dr = 0.10;
		// float dg = 0.2;
		// float db = 0.75 ;

		// float cr = 0.5;
		// float cg = 0.5;
		// float cb = 0.5;
		float fmult = 1.0f;
		float fr = 0.01f;
		float fg = 0.9f;
		float fb = 0.3f;

		float d = 0.0025f; //Dispersion
		float sr = 30;
		float sg = 10;
		float sb = 30;

		color.x = /*dr*val1 */ (fmult * fr * val2) + (d * sr/val2)   ;
		color.y = /*dg*val1 */ (fmult * fg * val2) + (d * sg/val2)   ;
		color.z = /*db*val1 */ (fmult * fb * val2) + (d * sb/val2)   ;

		gl_FragColor = vec4(color, 1.0);
	}
