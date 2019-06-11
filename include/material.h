#ifndef MATERIAL_H
#define MATERIAL_H

#include "shaders.h"
#include "texture.h"



class Material {

public:


	std::string name;

	FragmentShader *frags;
	VertexShader   *verts;
	Texture		   *tex;


	GLuint program;

	//Used for times when you want to instantiate a material but not associate it with any shaders yet
	Material(std::string name);

	//Used for instantiating a Material with a specific Fragment and Vertex Shader
	Material(std::string name, FragmentShader *frags, VertexShader *verts);

	//Used for instantiating a Material given a folder path and a name
	/*NOTE* This will create new sub-objects on the heap */
	Material(std::string name, std::string folderpath);

	Material::~Material();

	//Given a folder path, instantiates new shader objects
	void createfromfolder(std::string folderpath);

	//Attaches a texture to a given material, given a filepath to the texture, and a filename
	void attach_texture(std::string filepath, std::string filename);

	void Material::useProgram();

	void compile();

	void free_mem();

	void attach();

	void createProgram();

};









#endif