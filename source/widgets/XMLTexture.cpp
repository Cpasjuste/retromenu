//
// Created by cpasjuste on 30/09/2019.
//

#include "XMLUtility.h"
#include "XMLTexture.h"

using namespace c2d;
using namespace tinyxml2;

XMLTexture::XMLTexture(c2d::C2DObject *parent, tinyxml2::XMLNode *node, const std::string &path) : C2DTexture(path) {

    // should not happen
    if (!node) {
        setVisibility(Visibility::Hidden);
        return;
    }

    Vector2f parentSize = XMLUtility::getParentSize(parent);
    // parse size and origin
    FloatRect rect = XMLUtility::getRectangle(node->ToElement(), parentSize);
    setPosition(rect.left, rect.top);
    setScale(rect.width / getSize().x, rect.height / getSize().y);
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
            } else if (value == "ratio") {
                if (XMLUtility::getText(element) == "keep_width") {
                    setScale(getScale().x, getScale().x);
                } else if (XMLUtility::getText(element) == "keep_height") {
                    setScale(getScale().y, getScale().y);
                }
            }
        }
        child = child->NextSibling();
    }
}
