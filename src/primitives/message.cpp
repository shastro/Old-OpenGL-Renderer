/* message.cpp
 * Implements methods for the Message class, as well as a factory class that
 * constructs messages.
 */

#include "message.h"

// Message
// ------------------------------------------

Message::Message(msgType type)
{
    this->type = type;
}

msgType Message::getType()
{
    return type;
}

// KeyInputMsg
// ------------------------------------------

KeyInputMsg::KeyInputMsg(GLFWwindow* window, int key, int scancode, int action, int mods)
    : Message(msgType::key_input)
{
    this->window = window;
    this->key = key;
    this->scancode = scancode;
    this->action = action;
    this->mods = mods;
}

// MouseMoveInputMsg
// ------------------------------------------

MouseMoveInputMsg::MouseMoveInputMsg(GLFWwindow* window, double xpos, double ypos)
    : Message(msgType::mouse_move_input)
{
    this->xpos = xpos;
    this->ypos = ypos;
}

// RenderModelsMsg
// ------------------------------------------

RenderModelsMsg::RenderModelsMsg(std::vector<Model> *models, glm::mat4 view, glm::mat4 proj, void *shader)
    : Message(msgType::render_models)
{
    this->models = models;
    this->view = view;
    this->proj = proj;
    this->shader = shader;
}

// LogMsg
// ------------------------------------------

LogMsg::LogMsg(std::string msg)
    : Message(msgType::log_message)
{
    this->msg = msg;
}

// LogErr
// ------------------------------------------

LogErr::LogErr(std::string msg)
    : Message(msgType::log_message)
{
    this->msg = msg;
}

// ResizeWin
// ------------------------------------------

ResizeWin::ResizeWin(int width, int height)
    : Message(msgType::resize_window)
{
    this->width = width;
    this->height = height;
}

// MsgFactory
// ------------------------------------------

Message *MsgFactory::closeWin()
{
    return new Message(msgType::close_window);
}

Message *MsgFactory::swapBuffers()
{
    return new Message(msgType::swap_buffers);
}

Message *MsgFactory::clearScreen()
{
    return new Message(msgType::clear_screen);
}

Message *MsgFactory::pollEvents()
{
    return new Message(msgType::poll_events);
}

Message *MsgFactory::resizeWin(int w, int h)
{
    return new ResizeWin(w, h);
}

Message *MsgFactory::keyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    return new KeyInputMsg(window, key, scancode, action, mods);
}

Message *MsgFactory::mouseMove(GLFWwindow* window, double xpos, double ypos)
{
    return new MouseMoveInputMsg(window, xpos, ypos);
}

Message *MsgFactory::stopEngine()
{
    return new Message(msgType::stop_engine);
}

Message *MsgFactory::ignoreInput()
{
    return new Message(msgType::ignore_input);
}

Message *MsgFactory::renderModels(std::vector<Model> *models, glm::mat4 view, glm::mat4 proj, void *shader)
{
    return new RenderModelsMsg(models, view, proj, shader);
}

Message *MsgFactory::logMsg(std::string msg)
{
    return new LogMsg(msg);
}

Message *MsgFactory::logErr(std::string msg)
{
    return new LogErr(msg);
}
