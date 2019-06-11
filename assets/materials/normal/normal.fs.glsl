#version 330 core

	varying vec4 vNormal;
	varying vec3 vEye;
	varying vec4 zunit;

	vec3 color;

	float l_map(float x, float input_start, float input_end, float output_start, float output_end)
	{

			float slope = (output_end - output_start) / (input_end - input_start);
			return output_start + slope * (x - input_start);

	}

	void main(){

		color.x = l_map(vNormal.x, -1.0, 1.0, 0.0, 1.0);
		color.y = l_map(vNormal.y, -1.0, 1.0, 0.0, 1.0);
		color.z = l_map(vNormal.z, -1.0, 1.0, 0.0, 1.0);

		gl_FragColor = vec4(color, 1.0);
	}
