#include "mesh.h"
#include "shaders.h"
#include "material.h"
#include "camera.h"


#define SWIDTH  1000
#define SHEIGHT 1000
int main(void) {

	//GLFW Setup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SWIDTH, SHEIGHT, "Hell yeah Spring Break!", nullptr,
	                                      nullptr);
	glfwMakeContextCurrent(window);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  //Use for fps camera control

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	//Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Vertex Buffer Object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	Camera camera(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0));


	Mesh mesh1("Monster", "./objs/", "uvs.obj");
	mesh1.objParse();
	mesh1.combinebuffers();

	//USES NEW MESH OBJECT
	glBufferData(GL_ARRAY_BUFFER, mesh1.combined_data.size() * sizeof(glm::vec3), &(mesh1.combined_data)[0], GL_DYNAMIC_DRAW);



	//Shader Instantiation and Compilation

	Material material_fl = Material("bubblegum", "./materials/");
	//material_fl.createfromfolder("./materials/");
	material_fl.compile();


	//Create and Link Shaders to the program
	GLuint glprogram = glCreateProgram();
	material_fl.attach(glprogram);
	glLinkProgram(glprogram);
	glUseProgram(glprogram);


	GLint postAttrib = glGetAttribLocation(glprogram, "aPosition");
	glVertexAttribPointer(postAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0); //Changed Attrib Pointer
	glEnableVertexAttribArray(postAttrib);

	GLint normAttrib = glGetAttribLocation(glprogram, "aNormal");
	glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * mesh1.vertices.size())); //Changed Attrib Pointer
	glEnableVertexAttribArray(normAttrib);





	//MAIN DRAW LOOP
	float angle = 0;
	while (!glfwWindowShouldClose(window)) {

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {

			glfwSetWindowShouldClose(window, GL_TRUE);

		}

		//Frame Refresh
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);

		//Matrix Identity Initializations

		glm::mat4 mModel(1.0f);
		glm::mat4 mView(1.0f);
		glm::mat4 mProjection(1.0f);

		//Matrix Transformations
		mModel = glm::rotate(mModel, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

		camera.setPos(glm::vec3(0.0, 0.0, -3.25f));
		camera.Heading = glm::vec3(0.0, 0.0, -1.0);
		camera.lookat(glm::vec3(0.0, 0.0, 0.0));
		mView = camera.getView();


		//mView = glm::rotate(mView, glm::radians(angle/2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		mProjection = glm::perspective(glm::radians(45.0f), (float)SWIDTH / (float)SHEIGHT, 0.01f, 100.0f);

		//printf("ID:%u\n", fresnelvt.shaderid);
		unsigned int modelLoc = glGetUniformLocation(glprogram, "mModel");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mModel));

		unsigned int viewLoc = glGetUniformLocation(glprogram, "mView");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mView));

		unsigned int projLoc = glGetUniformLocation(glprogram, "mProjection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mProjection));

		// Draw a triangle from the number of vertices in the vertices array, each member of the array is a vec3

		glDrawArrays(GL_TRIANGLES, 0, mesh1.vertices.size());

		//std::cout << angle << std::endl;
		angle += 0.5;
	}

	// Clean up after yourself (:
	glDeleteProgram(glprogram);

	material_fl.del();

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	glfwTerminate();

	//mesh1.free();
	return 0;
}