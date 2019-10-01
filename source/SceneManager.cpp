//
// Created by cpasjuste on 01/10/2019.
//

#include "SceneManager.h"

SceneManager::SceneManager(c2d::Renderer *r, const std::string &x) {

    renderer = r;
    tinyxml2::XMLError e = xmlDocument.LoadFile(x.c_str());
    if (e != tinyxml2::XML_SUCCESS) {
        printf("main: %s\n", tinyxml2::XMLDocument::ErrorIDToName(e));
        return;
    }

    xmlRoot = xmlDocument.FirstChildElement("Skin");
    if (!xmlRoot) {
        printf("main: Skin node not found\n");
        return;
    }
}

SceneManager::~SceneManager() {
    xmlDocument.Clear();
}

Scene *SceneManager::load(const std::string &scene) {

    tinyxml2::XMLNode *sceneNode = xmlRoot->FirstChildElement(scene.c_str());
    if (!sceneNode) {
        printf("Scene::Scene(): could not find Scene xml node\n");
        return nullptr;
    }

    return new Scene(renderer, sceneNode);
}
