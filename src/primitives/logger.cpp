/* logger.cpp
 * Implements methods for the logger class
 */

#include "primitives.h"

Logger::Logger()
{
}

void Logger::attachMsgBus(MessageBus *msgBus)
{
    this->msgBus = msgBus;
}

void Logger::log(std::string msg)
{
    std::cout << "[LOG] " << msg << std:: endl;
}

void Logger::logerr(std::string errmsg)
{
	std::cout << "[ERROR]" << errmsg << std::endl;
}

void Logger::processMsg(Message *msg)
{
    switch (msg->getType()) {
    case msgType::log_message:
        log(((LogMsg *)msg)->msg);
        break;
    case msgType::key_input:
        log("Input Event");
        break;
    default:
        // do nothing
        break;
    }
}
