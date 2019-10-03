//
// Created by cpasjuste on 30/09/2019.
//

#include "Scene.h"

using namespace c2d;
using namespace tinyxml2;

Scene::Scene(tinyxml2::XMLNode *r, c2d::C2DObject *p, const std::string &n) : XMLRectangle(r, p) {

    printf("Scene(): %s\n", n.c_str());
    name = n;
}

std::string Scene::getName() {
    return name;
}
