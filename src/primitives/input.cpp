/* input.cpp
 * Implements methods for the input class
 */

#include "primitives.h"

void Input::attachMsgBus(MessageBus *msgBus)
{
    this->msgBus = msgBus;
}

void Input::notifyKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (!msgBus)
        return;

    msgBus->postMsg(MsgFactory::keyInput(window, key, scancode, action, mods));
}

void Input::notifyCursorMove(GLFWwindow *window, double xpos, double ypos)
{
    if (!msgBus)
        return;

    msgBus->postMsg(MsgFactory::mouseMove(window, xpos, ypos));
}

void Input::notifyWindowClose(GLFWwindow *window)
{
    if (msgBus)
        msgBus->postMsg(MsgFactory::closeWin());
}

void Input::ignoreInput() {}

void Input::stopIgnore() {}

void Input::processMsg(Message *msg)
{
    switch (msg->getType()) {
    case msgType::ignore_input:
        ignoreInput();
        break;
    default:
        // do nothing
        break;
    }
}