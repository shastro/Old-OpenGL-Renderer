/*
    environment.cpp
    Module: Primitives
    Purpose: Implement the environment class methods
*/

#include <fstream>

#include "primitives.h"
#include "utils.h"
Environment::Environment()
{
    init(std::string("config.json"));
}

Environment::Environment(std::string path)
{
    init(path);
}

void Environment::init(std::string confPath)
{
    // read config file into "config" variable
    std::ifstream confjson(confPath);
    confjson >> config;
    confjson.close();
}

Window *Environment::loadWindow()
{
    // load window data
    json windowData = config["window"];
    return new Window(windowData["width"], windowData["height"], windowData["name"]);
}

Camera *Environment::loadCamera()
{
    // load camera data
    json cameraPos = config["camera"]["pos"];
    json cameraTarget = config["camera"]["target"];
    camera = new Camera();

    return camera;
}

std::vector<Model> *Environment::loadModels()
{

    std::vector<Model> *models = new std::vector<Model>;

    json modelpath  = config["paths"]["models"];
    json matpath    = config["paths"]["materials"];
    json modelsconf = config["models"];

    for(unsigned int i = 0; i != modelsconf.size(); i++){
                                    //Model Path plus Model name
        models->push_back(Model(std::string("assets/models/test2/test2.mtl")));
    }
    std::cout << "Models Loaded!" << std::endl;
    return models;
}

// Material *Environment::loadMaterial()
// {
//     // load shaders
//     return new Material(config["models"]["material"], config["paths"]["materials"]);
// }
