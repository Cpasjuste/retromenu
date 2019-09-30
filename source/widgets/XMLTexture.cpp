//
// Created by cpasjuste on 30/09/2019.
//

#include "XMLUtility.h"
#include "XMLTexture.h"

using namespace c2d;
using namespace tinyxml2;

XMLTexture::XMLTexture(c2d::C2DObject *parent, tinyxml2::XMLNode *node, const std::string &path) : C2DTexture(path) {

    printf("XMLTexture()\n");

    // should not happen
    if (!node) {
        setVisibility(Visibility::Hidden);
        return;
    }

    XMLUtility::loadObject(this, parent, node);
}
