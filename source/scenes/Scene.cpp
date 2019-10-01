//
// Created by cpasjuste on 30/09/2019.
//

#include "widgets/XMLUtility.h"
#include "Scene.h"

using namespace c2d;
using namespace tinyxml2;

Scene::Scene(const std::string &n, c2d::C2DObject *parent, tinyxml2::XMLNode *root) : XMLRectangle(parent, root) {
    name = n;
    setFillColor(Color::Transparent);
}

std::string Scene::getName() {
    return name;
}
