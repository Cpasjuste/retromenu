//
// Created by cpasjuste on 30/09/2019.
//

#include "XMLUtility.h"
#include "XMLRectangle.h"

using namespace c2d;

XMLRectangle::XMLRectangle(c2d::C2DObject *parent, tinyxml2::XMLNode *node) : C2DRectangle(Vector2f()) {

    // should not happen
    if (!node) {
        setVisibility(Visibility::Hidden);
        return;
    }

    Vector2f parentSize = XMLUtility::getParentSize(parent);
    // parse size and origin
    FloatRect rect = XMLUtility::getRectangle(node->ToElement(), parentSize);
    setPosition(rect.left, rect.top);
    setSize(rect.width, rect.height);
    setOrigin(XMLUtility::getOrigin(node->ToElement()));

    // parse xml child's
    tinyxml2::XMLNode *child = node->FirstChild();
    while (child) {

        tinyxml2::XMLElement *element = child->ToElement();
        std::string value = child->Value();

        // add child object
        if (value == "rectangle" || value == "texture" || value == "text") {
            XMLUtility::addChild(this, child);
        } else if (Utility::startWith(value, "tween")) {
            XMLUtility::addTween(this, parentSize, child);
        } else {
            // this object values
            if (value == "color") {
                setFillColor(XMLUtility::getColor(element));
            } else if (value == "outline") {
                setOutlineColor(XMLUtility::getColor(element));
                setOutlineThickness((float) XMLUtility::getOutlineSize(element));
            }
        }

        child = child->NextSibling();
    }
}
