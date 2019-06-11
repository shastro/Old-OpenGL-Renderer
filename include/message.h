#include <GLFW/glfw3.h>
#include <vector>
#include <list>
#include <string>
#include <glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Model;

enum class msgType {
    // window
    close_window,
    swap_buffers,
    clear_screen,
    poll_events,
    resize_window,
    // logic
    stop_engine,
    // input
    key_input,
    mouse_move_input,
    mouse_button_input,
    ignore_input,
    // renderer
    render_models,
    // logger
    log_message
};

class Message {
protected:
    msgType type;
public:
    Message(msgType type);

    msgType getType();
};

class KeyInputMsg : public Message {
public:
    GLFWwindow *window;
    int key;
    int scancode;
    int action;
    int mods;
    KeyInputMsg(GLFWwindow* window, int key, int scancode, int action, int mods);
};

class MouseMoveInputMsg : public Message {
public:
    GLFWwindow *window;
    double xpos;
    double ypos;
    MouseMoveInputMsg(GLFWwindow* window, double xpos, double ypos);
};

class RenderModelsMsg : public Message {
public:
    std::vector<Model> *models;
    glm::mat4 view;
    glm::mat4 proj;
    void *shader;
    RenderModelsMsg(std::vector<Model> *models, glm::mat4 view, glm::mat4 proj, void *shader);
};

class LogMsg : public Message {
public:
    std::string msg;
    LogMsg(std::string msg);
};

class LogErr : public Message {
public:
    std::string msg;
    LogErr(std::string msg);
};

class ResizeWin : public Message {
public:
    int width;
    int height;
    ResizeWin(int w, int h);
};


/* factory class */
class MsgFactory {
public:
    // window
    static Message *closeWin();
    static Message *swapBuffers();
    static Message *clearScreen();
    static Message *pollEvents();
    static Message *resizeWin(int w, int h);
    // logic
    static Message *stopEngine();
    // input
    static Message *keyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
    static Message *mouseMove(GLFWwindow *window, double xpos, double ypos);
    static Message *ignoreInput();
    // renderer
    static Message *renderModels(std::vector<Model> *models, glm::mat4 view, glm::mat4 proj, void *shader);
    // logger
    static Message *logMsg(std::string msg);
    static Message *logErr(std::string msg);
};