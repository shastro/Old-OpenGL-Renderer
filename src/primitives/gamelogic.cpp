/* gamelogic.cpp
 * Implements methods for the game logic class
 */

#include "primitives.h"

void GameLogic::startLoop()
{
    // create a reference to the configuration
    Environment env;
    // load the models
    std::vector<Model> *models = env.loadModels();
    Model m("assets/models/shipbase/shipbase.obj");

    float currentFrame = glfwGetTime();
    float lastFrame = 0.0;

    Shader shader("assets/materials/simple/simple.vt.glsl", "assets/materials/simple/simple.fs.glsl");
    shader.use();
    msgBus->postMsg(MsgFactory::logMsg("Starting main loop"));
    while (engineRunning) {
        // set delta time
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glm::mat4 projection = glm::perspective((float)glm::radians(45.0), (float)winWidth / (float)winHeight, 0.1f, 100.0f);
        glm::mat4 view = camera->getView();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setMat4("model", model);

        msgBus->postMsg(MsgFactory::pollEvents());
        msgBus->postMsg(MsgFactory::swapBuffers());
        msgBus->postMsg(MsgFactory::clearScreen());

        for (auto &i : *models) {
            i.draw(shader);
        }
        m.draw(shader);
        // msgBus->postMsg(MsgFactory::renderModels(models, projection, view, (void *)(&shader)));
    }
}

void GameLogic::attachMsgBus(MessageBus *msgBus)
{
    this->msgBus = msgBus;
}

void GameLogic::processKeyInput(int key, int scancode, int action)
{
    // if the message bus doesn't exist, then just return
    if (!msgBus || (action != GLFW_PRESS && action != GLFW_REPEAT))
        return;

    // movement
    if (key == GLFW_KEY_W) {
        camera->moveXZ(FORWARD, deltaTime);
        msgBus->postMsg(MsgFactory::logMsg("moving forward: camera_z = " + std::to_string(camera->getZ())));
    }
    else if (key == GLFW_KEY_S) {
        camera->moveXZ(BACKWARD, deltaTime);
        msgBus->postMsg(MsgFactory::logMsg("moving backward: camera_z = " + std::to_string(camera->getZ())));
    }
    else if (key == GLFW_KEY_A) {
        camera->moveXZ(LEFT, deltaTime);
        msgBus->postMsg(MsgFactory::logMsg("moving left: camera_x = " + std::to_string(camera->getX())));
    }
    else if (key == GLFW_KEY_D) {
        camera->moveXZ(RIGHT, deltaTime);
        msgBus->postMsg(MsgFactory::logMsg("moving backward: camera_x = " + std::to_string(camera->getX())));
    }

    else if (key == GLFW_KEY_ESCAPE) {
        msgBus->postMsg(MsgFactory::ignoreInput());
        msgBus->postMsg(MsgFactory::closeWin());
        stopEngine();
    }
}

void GameLogic::processMouseMove(double xpos, double ypos)
{
    if (!msgBus)
        return;

    if (firstMouse) {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastMouseX;
    float yoffset = lastMouseY - ypos;

    lastMouseX = xpos;
    lastMouseY = ypos;

    // msgBus->postMsg(MsgFactory::logMsg("mouse at: " + std::to_string(xpos) + std::string(", ") + std::to_string(ypos)));
    camera->mouseInput(xoffset, yoffset);
}

void GameLogic::setCamera(Camera *camera)
{
    this->camera.reset(camera);
}

void GameLogic::stopEngine()
{
    engineRunning = false;
    msgBus->postMsg(MsgFactory::logMsg("Exiting"));
}

void GameLogic::processMsg(Message *msg)
{
    // temp variable
    KeyInputMsg *kim_ptr = nullptr;
    ResizeWin *rw_ptr = nullptr;
    MouseMoveInputMsg *mmim_ptr = nullptr;

    switch (msg->getType()) {
    case msgType::key_input:
        kim_ptr = (KeyInputMsg *)msg;
        processKeyInput(kim_ptr->key, kim_ptr->scancode, kim_ptr->action);
        break;
    case msgType::mouse_move_input:
        mmim_ptr = (MouseMoveInputMsg *)msg;
        processMouseMove(mmim_ptr->xpos, mmim_ptr->ypos);
        break;
    case msgType::stop_engine:
        stopEngine();
        break;
    case msgType::close_window:
        stopEngine();
        break;
    case msgType::resize_window:
        rw_ptr = (ResizeWin *)msg;
        winWidth = rw_ptr->width;
        winHeight = rw_ptr->height;
        break;
    default:
        // do nothing
        break;
    }
}
