//
// Created by cpasjuste on 30/09/2019.
//

#include "XMLTexture.h"

using namespace c2d;

XMLTexture::XMLTexture(tinyxml2::XMLNode *node, C2DObject *parent, const std::string &path)
        : C2DTexture(path), XMLWidget(node, parent) {

    printf("XMLTexture()\n");
    load(this);
}
