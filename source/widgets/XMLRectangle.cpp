//
// Created by cpasjuste on 30/09/2019.
//

#include "XMLUtility.h"
#include "XMLRectangle.h"

using namespace c2d;
using namespace tinyxml2;

XMLRectangle::XMLRectangle(c2d::C2DObject *parent, tinyxml2::XMLNode *node) : C2DRectangle(Vector2f()) {

    printf("XMLRectangle()\n");

    // should not happen
    if (!node) {
        setVisibility(Visibility::Hidden);
        return;
    }

    XMLUtility::loadObject(this, parent, node);
}