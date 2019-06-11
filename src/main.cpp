
#ifdef USING_LUA
#include "scriptloader.h"
#endif

#include "primitives.h"
#include "gldebug.h"

int main()
{
    
    // init glew and set experimental to true

        Environment env;

        //Loading data
        Window *win = env.loadWindow();

        glewExperimental = GL_TRUE;
        glewInit();
        glEnable(GL_DEPTH_TEST);

        GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
            glDebugMessageCallback(glDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        } 

        glDebugMessageControl(GL_DEBUG_SOURCE_API, 
                              GL_DEBUG_TYPE_ERROR, 
                              GL_DEBUG_SEVERITY_HIGH,
                              0, nullptr, GL_TRUE);
        
        Camera *cam = env.loadCamera();

        //Subsystem Creation
        Input *input = new Input();
        Logger *logger = new Logger();
        GameLogic *logic = new GameLogic();
        Renderer *renderer = new Renderer();

        logic->setCamera(cam);
        win->setInputHandler(input);

        MessageBus msgBus;

        // attach the subsystems to the bus
        msgBus.attachWindow(win);
        msgBus.attachLogic(logic);
        msgBus.attachLogger(logger);
        msgBus.attachInput(input);
        msgBus.attachRenderer(renderer);

        // attach the message bus to the subsystems
        win->attachMsgBus(&msgBus);
        logic->attachMsgBus(&msgBus);
        input->attachMsgBus(&msgBus);
        logger->attachMsgBus(&msgBus);
        renderer->attachMsgBus(&msgBus);


       
        // start the main loop
        logic->startLoop();


    // cleanup
    glfwTerminate();

    return 0;
}