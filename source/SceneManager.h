//
// Created by cpasjuste on 01/10/2019.
//

#ifndef RETROMENU_SCENEMANAGER_H
#define RETROMENU_SCENEMANAGER_H

#include <string>
#include <tinyxml2.h>
#include <scenes/Scene.h>

class SceneManager {

public:

    explicit SceneManager(c2d::Renderer *renderer, const std::string &xml);

    ~SceneManager();

    Scene *load(const std::string &scene);

private:

    tinyxml2::XMLDocument xmlDocument;
    tinyxml2::XMLNode *xmlRoot = nullptr;
    c2d::Renderer *renderer = nullptr;
};

#endif //RETROMENU_SCENEMANAGER_H
