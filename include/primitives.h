/* primitives.h
 * Defines primitive abstractions over openGL primitives
 */

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

// glew
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// glm
#include <glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"
// std lib
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <memory>
// assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
// json
#include "json.hpp"
// messages
#include "message.h"

using json = nlohmann::json;


enum texture_type {
    diffuse, specular
};

enum MovementDirection {
    FORWARD, BACKWARD, LEFT, RIGHT
};

// Forward declare some classes
// ------------------------------------------
class Window;
class Input;
class GameLogic;
class Camera;
class Logger;
class MessageBus;

// Vertex
// ------------------------------------------

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 bitangent;
    glm::vec3 tangent;
};

// ------------------------------------------

// Texture
// ------------------------------------------

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;  // we store the path of the texture to compare with other textures
};
// ------------------------------------------

// Shaders
// ------------------------------------------

// Shader exception class
class ShaderError {
private:
    std::string err;
public:
    ShaderError(std::string err);
    void printError();
};

// Abstract class ShaderError
// should not be instantiated

//Do Not instantiate shader
class Shader {
private:
    void checkCompileErrors(unsigned int shader, std::string type);
public:
    GLuint shaderid;
    GLuint program;

    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

    void use();
    // set values in the shader program
    void setBool(std::string name, bool value);
    void setInt(std::string name, int value);
    void setFloat(std::string name, float value);
    void setMat4(std::string name, glm::mat4 mat);
};

// ------------------------------------------

// Mesh
// ------------------------------------------

// wavefront object class
class Mesh {
private:
    GLuint vao; // vertex array
    GLuint vbo; // vertex buffer
    GLuint ebo; // element buffer
    
    void init();
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> v, std::vector<unsigned int> i, std::vector<Texture> t);

    void draw(Shader shader);
};

//------------------------------

//Model
//-----------------------------
class Model {
private:
    bool gammaCorrection;

    /*  Functions   */
    void loadModel(std::string path);
    void loadMesh(std::string path);
    void processNode(aiNode *node, aiScene *scene);
    Mesh processMesh(aiMesh *mesh, aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(std::string filename, std::string directory, bool gamma);

public:
    /*  Functions   */
    Model(std::string path, bool gamma = false);
    // void draw(glm::mat4 view, glm::mat4 proj);
    void draw(Shader shader);

    /*  Model Data  */
    std::string name;
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    // Material material;
};

// ------------------------------------------

// Window
// ------------------------------------------
/* TODO
 * 1. add callbacks
 * 2. add make resizeable option
 * 3. add make fullscreen option
 */
class Window {
private:
    GLFWwindow *window;
    std::map<int, Mesh *> *objectsRef;
    int numVerts;
    MessageBus *msgBus;
    int height;
    int width;

    void calcNumVerts();
public:
    Window(unsigned width, unsigned height, std::string name);
    ~Window();

    // bind the messageBus
    void attachMsgBus(MessageBus *msgBus);
    // make this window the currently used one
    void makeCurrent();
    // close the window
    void close();
    // swap the buffers
    void swapBuffers();
    // clear the screen
    void clear();
    // set input handler
    void setInputHandler(Input *input);
    // start the event loop
    void startEventLoop();
    void pollEvents();
    bool isClosed();
    void processMsg(Message *msg);
};

// ------------------------------------------

// Camera
// ------------------------------------------

class Camera {
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    void updateVectors();
public:
    Camera();
    Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch);

    glm::vec3 getCamPos();
    glm::mat4 getView();
    void moveXZ(MovementDirection dir, float dt);
    void mouseInput(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    float getX();
    float getY();
    float getZ();

    void setPos(glm::vec3 newPos);
    void setX(float x);
    void setY(float y);
    void setZ(float z);

    //euler angles
    float yaw;
    float pitch;
    // camera options
    float speed;
    float mouseSensitivity;
    float zoom;
};

// ------------------------------------------

// Environment
// ------------------------------------------
/* TODO
 * 1. make loadable from save file
 * 2. add everything
 */
class Environment {
private:
    Camera *camera;
    Window *window;
    Shader *shader;
    std::vector<Model> *models;
    std::map<int, Mesh *> objects; // a map of tags and objects
    json config; // the configuration

    void init(std::string confPath);
public:
    // by default, environment looks for a file called "config.json"
    Environment();
    // or you can specify the name
    Environment(std::string confName);

    Window *loadWindow();
    Camera *loadCamera();
    std::vector<Model> *loadModels();
};

// Game Logic
// ------------------------------------------

class GameLogic {
private:
    std::unique_ptr<Camera> camera;
    MessageBus *msgBus;
    bool engineRunning = true;
    float deltaTime;
    int winWidth = 600;
    int winHeight = 600;
    bool firstMouse = true;
    double lastMouseX;
    double lastMouseY;
public:
    GameLogic() = default;

    // bind the messageBus
    void attachMsgBus(MessageBus *msgBus);
    void processKeyInput(int key, int scancode, int action);
    void setCamera(Camera *camera);
    void startLoop();
    void stopEngine();
    void processMsg(Message *msg);
    void processMouseMove(double xpos, double ypos);
};

// ------------------------------------------

// Input Handler
// ------------------------------------------

class Input {
private:
    bool ignore = false;
    MessageBus *msgBus;
public:
    Input() = default;

    // bind the messageBus
    void attachMsgBus(MessageBus *msgBus);
    void notifyKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
    void notifyCursorMove(GLFWwindow *window, double xpos, double ypos);
    void ignoreInput();
    void stopIgnore();
    void processMsg(Message *msg);
    void notifyWindowClose(GLFWwindow *window);
};

// Logger
// ------------------------------------------

class Logger {
private:
    MessageBus *msgBus;
public:
    Logger();

    // bind the messageBus
    void attachMsgBus(MessageBus *msgBus);
    void log(std::string msg);
    void logerr(std::string errmsg);
    void processMsg(Message *msg);
};

// ------------------------------------------

// Renderer
// ------------------------------------------

class Renderer {
private:
    MessageBus *msgBus;
public:
    Renderer() = default;

    // bind the messageBus
    void attachMsgBus(MessageBus *msgBus);
    // process and draw a list of models to the screen
    void render(std::vector<Model> *models, glm::mat4 view, glm::mat4 proj, void *shader);
    void processMsg(Message *msg);
};

// ------------------------------------------

// Message Bus
// ------------------------------------------

class MessageBus {
private:
    std::unique_ptr<Window> win;
    std::unique_ptr<GameLogic> glogic;
    std::unique_ptr<Logger> lggr;
    std::unique_ptr<Input> in;
    std::unique_ptr<Renderer> rndr;

public:
    MessageBus() = default;

    // post a message
    void postMsg(Message *msg);

    // bind a Window to the bus
    void attachWindow(Window *win);
    // attach the game logic
    void attachLogic(GameLogic *glogic);
    // attach the logger
    void attachLogger(Logger *lggr);
    // attach the input
    void attachInput(Input *in);
    // attach the renderer
    void attachRenderer(Renderer *rndr);
};

#endif
