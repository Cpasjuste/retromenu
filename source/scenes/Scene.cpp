//
// Created by cpasjuste on 30/09/2019.
//

#include "Scene.h"

using namespace c2d;
using namespace tinyxml2;

Scene::Scene(tinyxml2::XMLNode *r, c2d::C2DObject *p) : XMLRectangle(r, p) {

    if (r) {
        printf("Scene(): %s\n", r->Value());
        name = r->Value();
    }
}

std::string Scene::getName() {
    return name;
}
