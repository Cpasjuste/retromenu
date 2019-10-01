//
// Created by cpasjuste on 30/09/2019.
//

#include "XMLUtility.h"
#include "XMLText.h"

using namespace c2d;

XMLText::XMLText(c2d::C2DObject *parent, tinyxml2::XMLNode *node) : C2DText("") {

    // should not happen
    if (!node) {
        setVisibility(Visibility::Hidden);
        return;
    }

    Vector2f parentSize = XMLUtility::getParentSize(parent);
    // parse size and origin
    FloatRect rect = XMLUtility::getRectangle(node->ToElement(), parentSize);
    setCharacterSize((unsigned int) rect.height);
    setPosition(rect.left, rect.top);
    setSizeMax(rect.width, rect.height);
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
                setOutlineColor(XMLUtility::getOutlineColor(element));
                setOutlineThickness((float) XMLUtility::getOutlineSize(element));
            } else if (value == "string") {
                setString(XMLUtility::getText(element));
            }
        }
        child = child->NextSibling();
    }
}
