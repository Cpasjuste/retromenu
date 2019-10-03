//
// Created by cpasjuste on 30/09/2019.
//

#include "XMLRectangle.h"

using namespace c2d;

XMLRectangle::XMLRectangle(tinyxml2::XMLNode *node, c2d::C2DObject *parent)
        : C2DRectangle(Vector2f()), XMLWidget(node, parent) {

    printf("XMLRectangle()\n");
    load(this);
}
