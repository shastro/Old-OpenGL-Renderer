/* renderer.cpp
 * Implements methods for the Renderer class
 */

#include "primitives.h"

void Renderer::render(std::vector<Model> *models, glm::mat4 view, glm::mat4 proj, void *shader)
{
	for(unsigned int i = 0; i < models->size(); i++){
		// models->at(i).material.useProgram(); // model.draw already does this

        Shader *shader = (Shader *)shader;
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        shader->setMat4("projection", proj);
        shader->setMat4("view", view);
        shader->setMat4("model", model);

		models->at(i).draw(*shader);
	}
    if (msgBus) {
    }
}

void Renderer::attachMsgBus(MessageBus *msgBus)
{
    this->msgBus = msgBus;
}

void Renderer::processMsg(Message *msg)
{
    RenderModelsMsg *rmm_ptr = nullptr;

    switch (msg->getType()) {
    case msgType::render_models:
        rmm_ptr = (RenderModelsMsg *)msg;
        render(rmm_ptr->models, rmm_ptr->view, rmm_ptr->proj, rmm_ptr->shader);
        break;
    default:
        // do nothing
        break;
    }
}
