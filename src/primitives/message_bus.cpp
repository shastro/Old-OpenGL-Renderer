/* message_bus.cpp
 * Implements methods for the message bus class.
 * The message bus is responsible for acting as a bridge
 * between the various components.
 */

#include "primitives.h"

// Bind Components
void MessageBus::attachWindow(Window *win)
{
    this->win.reset(win);
}

void MessageBus::attachLogic(GameLogic *glogic)
{
    this->glogic.reset(glogic);
}

void MessageBus::attachLogger(Logger *lggr)
{
    this->lggr.reset(lggr);
}

void MessageBus::attachInput(Input *in)
{
    this->in.reset(in);
}

void MessageBus::attachRenderer(Renderer *rndr)
{
    this->rndr.reset(rndr);
}

void MessageBus::postMsg(Message *msg)
{
    win->processMsg(msg);
    glogic->processMsg(msg);
    lggr->processMsg(msg);
    in->processMsg(msg);
    rndr->processMsg(msg);

    delete msg;
}
