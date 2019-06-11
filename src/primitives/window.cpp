#include "primitives.h"

Window::Window(unsigned width, unsigned height, std::string name)
{
    this->width = width;
    this->height = height;

    // window setup
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, name.c_str(), nullptr,
    nullptr);

    objectsRef = nullptr;

    numVerts = 0;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    glfwMakeContextCurrent(window);
}

Window::~Window()
{
    glfwDestroyWindow(window);
}

void Window::makeCurrent()
{
    // make the current OpenGL context active
    glfwMakeContextCurrent(window);
}

void Window::startEventLoop()
{
    while(!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);
        glfwPollEvents();
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        }

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // make sure to use the depth buffer bit
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void Window::close()
{
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window);
}

void Window::clear()
{
    // Clear the screen to black
    glClearColor(0.4f, 0.2f, 0.4f, 1.0f);
    // make sure to use the depth buffer bit
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::attachMsgBus(MessageBus *msgBus)
{
    this->msgBus = msgBus;

    if (msgBus)
        msgBus->postMsg(MsgFactory::resizeWin(width, height));
}

void Window::setInputHandler(Input *input)
{
    glfwSetWindowUserPointer(window, input);

    auto keyfun = [](GLFWwindow* w, int k, int s, int a, int m)
    {
        static_cast<Input*>(glfwGetWindowUserPointer(w))->notifyKeyInput(w, k, s, a, m);
    };

    auto cursorfun = [](GLFWwindow* w, double x, double y)
    {
        static_cast<Input*>(glfwGetWindowUserPointer(w))->notifyCursorMove(w, x, y);
    };

    auto winclosefun = [](GLFWwindow* w)
    {
        static_cast<Input*>(glfwGetWindowUserPointer(w))->notifyWindowClose(w);
    };

    glfwSetKeyCallback(window, keyfun);
    glfwSetCursorPosCallback(window, cursorfun);
    glfwSetWindowCloseCallback(window, winclosefun);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

bool Window::isClosed()
{
    return glfwWindowShouldClose(window);
}

void Window::processMsg(Message *msg)
{
    switch (msg->getType()) {
    case msgType::close_window:
        close();
        break;
    case msgType::swap_buffers:
        swapBuffers();
        break;
    case msgType::clear_screen:
        clear();
        break;
    case msgType::poll_events:
        pollEvents();
        break;
    default:
        // do nothing
        break;
    }
}
