//
// Created by cpasjuste on 02/10/2019.
//

#include <cstdio>
#include <cross2d/c2d.h>
#include "XMLWidget.h"
#include "XMLRectangle.h"
#include "XMLUtility.h"

using namespace c2d;

XMLWidget::XMLWidget(const Type &t, XMLWidget *p, tinyxml2::XMLNode *n) {

    printf("XMLWidget()\n");
    type = t;
    parent = p;
    node = n;
}

void XMLWidget::load() {

    Vector2f parentSize = getParentSize();

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

void XMLWidget::addChild(tinyxml2::XMLNode *n) {

    std::string value = node->Value();

    if (value == "rectangle") {
        // ADD CHILD (RECTANGLE)
        auto obj = new XMLRectangle(parent, node);
        parent->add(obj);
    } else if (value == "texture") {
        // ADD CHILD (TEXTURE)
        tinyxml2::XMLElement *e = node->ToElement()->FirstChildElement("path");
        if (e) {
            std::string path = getText(e);
            if (!path.empty()) {
                auto obj = new XMLTexture(parent, node, path);
                parent->add(obj);
            }
        }
    } else if (value == "text") {
        // ADD CHILD (TEXT)
        auto obj = new XMLText(parent, node);
        parent->add(obj);
    }
}

c2d::Vector2f XMLWidget::getParentSize() {

    if (parent) {
        return parent->getSize();
    }

    return {};
}
