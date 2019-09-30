//
// Created by cpasjuste on 30/09/2019.
//

#include "XMLUtility.h"
#include "XMLText.h"

using namespace c2d;

XMLText::XMLText(tinyxml2::XMLNode *node) : C2DText("") {

    printf("XMLText()\n");

    // should not happen
    if (!node) {
        setVisibility(Visibility::Hidden);
        return;
    }

    XMLUtility::loadSection(this, node);
}
