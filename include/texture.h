#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glew.h>



/* Implementation needs stb_image.h! */


class Texture {



private:

	int w;
	int h;
	int comp;

public:
	unsigned int id;



	std::string filepath;
	std::string filename;

	unsigned char *imagedata;

	Texture(std::string filepath, std::string filename) {

		id = *((unsigned int *)malloc(sizeof(unsigned int*)));
		glGenTextures(1, &id);

		this->filepath = filepath;
		this->filename = filename;
	}

	void load()
	{

		imagedata = stbi_load((filepath + filename).c_str(), &w, &h, &comp, STBI_rgb);

	}

	void activate()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, imagedata);

	}

	//glUniform1i(glGetUniformLocation(fresnelfg.shaderid, "tMatCap"), 0);



};



#endif