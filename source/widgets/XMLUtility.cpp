//
// Created by cpasjuste on 30/09/2019.
//

#include <cross2d/c2d.h>
#include "XMLUtility.h"
#include "XMLRectangle.h"
#include "XMLText.h"

using namespace c2d;

bool XMLUtility::loadSection(c2d::C2DObject *object, tinyxml2::XMLNode *node) {

    if (!object) {
        fprintf(stderr, "XMLUtility::loadRecurse: parent is null\n");
        return false;
    }

    if (!node) {
        fprintf(stderr, "XMLUtility::loadRecurse: xml node is null\n");
        return false;
    }

    std::string nodeType = node->Value();
    // parse size and origin
    FloatRect rect = XMLUtility::getRectangle(node->ToElement());
    Origin origin = XMLUtility::getOrigin(node->ToElement());
    if (nodeType == "rectangle") {
        ((XMLRectangle *) object)->setPosition(rect.left, rect.top);
        ((XMLRectangle *) object)->setSize(rect.width, rect.height);
        ((XMLRectangle *) object)->setOrigin(origin);
    } else if (nodeType == "text") {
        ((XMLText *) object)->setCharacterSize((unsigned int) rect.height);
        ((XMLText *) object)->setPosition(rect.left, rect.top);
        ((XMLText *) object)->setSizeMax(rect.width, rect.height);
        ((XMLText *) object)->setOrigin(origin);
    }

    // parse child's
    tinyxml2::XMLNode *child = node->FirstChild();
    while (child) {
        tinyxml2::XMLElement *element = child->ToElement();
        std::string value = child->Value();
        if (value == "rectangle") {
            auto rectangle = new XMLRectangle(child);
            object->add(rectangle);
        } else if (value == "text") {
            auto text = new XMLText(child);
            object->add(text);
        } else if (value == "string") {
            ((XMLText *) object)->setString(getText(element));
        } else if (value == "color") {
            Color color = XMLUtility::getColor(element);
            if (nodeType == "rectangle") {
                ((XMLRectangle *) object)->setFillColor(color);
            } else if (std::string(node->Value()) == "text") {
                ((XMLText *) object)->setFillColor(color);
            }
        } else if (value == "outline") {
            Color color = XMLUtility::getOutlineColor(element);
            int size = XMLUtility::getOutlineSize(element);
            if (nodeType == "rectangle") {
                ((XMLRectangle *) object)->setOutlineColor(color);
                ((XMLRectangle *) object)->setOutlineThickness((float) size);
            } else if (std::string(node->Value()) == "text") {
                ((XMLText *) object)->setOutlineColor(color);
                ((XMLText *) object)->setOutlineThickness((float) size);
            }
        } else if (value == "tweenPosition") {
            auto tween = XMLUtility::getTweenPosition(element);
            if (tween) {
                object->add(tween);
            }
        } else if (value == "tweenRotation") {
            auto tween = XMLUtility::getTweenRotation(element);
            if (tween) {
                object->add(tween);
            }
        } else if (value == "tweenScale") {
            auto tween = XMLUtility::getTweenScale(element);
            if (tween) {
                object->add(tween);
            }
        } else if (value == "tweenColor") {
            auto tween = XMLUtility::getTweenColor(element);
            if (tween) {
                object->add(tween);
            }
        } else if (value == "tweenAlpha") {
            auto tween = XMLUtility::getTweenAlpha(element);
            if (tween) {
                object->add(tween);
            }
        }

        child = child->NextSibling();
    }

    return true;
}

std::string XMLUtility::getAttribute(tinyxml2::XMLElement *element, const std::string &name) {

    if (!element || !element->Attribute(name.c_str())) {
        return "";
    }

    return element->Attribute(name.c_str());
}

int XMLUtility::getAttributeInt(tinyxml2::XMLElement *element, const std::string &name) {
    return Utility::parseInt(getAttribute(element, name));
}

float XMLUtility::getAttributeFloat(tinyxml2::XMLElement *element, const std::string &name) {
    return Utility::parseFloat(getAttribute(element, name));
}

std::string XMLUtility::getText(tinyxml2::XMLElement *element) {

    if (!element || !element->GetText()) {
        return "";
    }

    return element->GetText();
}

int XMLUtility::getTextInt(tinyxml2::XMLElement *element) {
    return Utility::parseInt(getText(element));
}

c2d::FloatRect XMLUtility::getRectangle(tinyxml2::XMLElement *element) {

    FloatRect rect{};

    if (element) {
        rect.left = getAttributeInt(element, "x");
        rect.top = getAttributeInt(element, "y");
        rect.width = getAttributeInt(element, "w");
        rect.height = getAttributeInt(element, "h");
    }

    return rect;
}

c2d::Color XMLUtility::getColor(tinyxml2::XMLElement *element) {

    Color color{};

    if (element) {
        color.r = getAttributeInt(element, "r");
        color.g = getAttributeInt(element, "g");
        color.b = getAttributeInt(element, "b");
        color.a = getAttributeInt(element, "a");
    }

    return color;
}

c2d::Color XMLUtility::getOutlineColor(tinyxml2::XMLElement *element) {

    Color color{};

    if (element) {
        color.r = getAttributeInt(element, "r");
        color.g = getAttributeInt(element, "g");
        color.b = getAttributeInt(element, "b");
        color.a = getAttributeInt(element, "a");
    }

    return color;
}

int XMLUtility::getOutlineSize(tinyxml2::XMLElement *element) {

    int size = 0;

    if (element) {
        size = getAttributeInt(element, "size");
    }

    return size;
}

c2d::Origin XMLUtility::getOrigin(tinyxml2::XMLElement *element) {

    Origin origin = Origin::TopLeft;
    if (!element) {
        return origin;
    }

    std::string str = getAttribute(element, "origin");
    if (str == "Left") {
        origin = Origin::Left;
    } else if (str == "TopLeft") {
        origin = Origin::TopLeft;
    } else if (str == "Top") {
        origin = Origin::Top;
    } else if (str == "TopRight") {
        origin = Origin::TopRight;
    } else if (str == "Right") {
        origin = Origin::Right;
    } else if (str == "BottomRight") {
        origin = Origin::BottomRight;
    } else if (str == "Bottom") {
        origin = Origin::Bottom;
    } else if (str == "BottomLeft") {
        origin = Origin::BottomLeft;
    } else if (str == "Center") {
        origin = Origin::Center;
    }

    return origin;
}

c2d::TweenPosition *XMLUtility::getTweenPosition(tinyxml2::XMLElement *element) {

    if (!element || std::string(element->Value()) != "tweenPosition") {
        return nullptr;
    }

    Vector2f from = {XMLUtility::getAttributeInt(element, "fromX"),
                     XMLUtility::getAttributeInt(element, "fromY")};
    Vector2f to = {XMLUtility::getAttributeInt(element, "toX"),
                   XMLUtility::getAttributeInt(element, "toY")};
    float duration = XMLUtility::getAttributeFloat(element, "duration");
    TweenLoop loop = TweenLoop::None;
    std::string str = XMLUtility::getAttribute(element, "loop");
    if (str == "loop") {
        loop = TweenLoop::Loop;
    } else if (str == "pingpong") {
        loop = TweenLoop::PingPong;
    }

    auto tween = new TweenPosition(from, to, duration, loop, TweenState::Playing);
    return tween;
}

c2d::TweenRotation *XMLUtility::getTweenRotation(tinyxml2::XMLElement *element) {

    if (!element || std::string(element->Value()) != "tweenRotation") {
        return nullptr;
    }

    float from = (float) XMLUtility::getAttributeInt(element, "from");
    float to = (float) XMLUtility::getAttributeInt(element, "to");
    float duration = XMLUtility::getAttributeFloat(element, "duration");
    TweenLoop loop = TweenLoop::None;
    std::string str = XMLUtility::getAttribute(element, "loop");
    if (str == "loop") {
        loop = TweenLoop::Loop;
    } else if (str == "pingpong") {
        loop = TweenLoop::PingPong;
    }

    auto tween = new TweenRotation(from, to, duration, loop, TweenState::Playing);
    return tween;
}

c2d::TweenScale *XMLUtility::getTweenScale(tinyxml2::XMLElement *element) {

    if (!element || std::string(element->Value()) != "tweenScale") {
        return nullptr;
    }

    Vector2f from = {XMLUtility::getAttributeFloat(element, "fromX"),
                     XMLUtility::getAttributeFloat(element, "fromY")};
    Vector2f to = {XMLUtility::getAttributeFloat(element, "toX"),
                   XMLUtility::getAttributeFloat(element, "toY")};
    float duration = XMLUtility::getAttributeFloat(element, "duration");
    TweenLoop loop = TweenLoop::None;
    std::string str = XMLUtility::getAttribute(element, "loop");
    if (str == "loop") {
        loop = TweenLoop::Loop;
    } else if (str == "pingpong") {
        loop = TweenLoop::PingPong;
    }

    auto tween = new TweenScale(from, to, duration, loop, TweenState::Playing);
    return tween;
}

c2d::TweenColor *XMLUtility::getTweenColor(tinyxml2::XMLElement *element) {

    if (!element || std::string(element->Value()) != "tweenColor") {
        return nullptr;
    }

    Color from = {XMLUtility::getAttributeInt(element, "fromR"),
                  XMLUtility::getAttributeInt(element, "fromG"),
                  XMLUtility::getAttributeInt(element, "fromB"),
                  XMLUtility::getAttributeInt(element, "fromA")};
    Color to = {XMLUtility::getAttributeInt(element, "toR"),
                XMLUtility::getAttributeInt(element, "toG"),
                XMLUtility::getAttributeInt(element, "toB"),
                XMLUtility::getAttributeInt(element, "toA")};
    float duration = XMLUtility::getAttributeFloat(element, "duration");
    TweenLoop loop = TweenLoop::None;
    std::string str = XMLUtility::getAttribute(element, "loop");
    if (str == "loop") {
        loop = TweenLoop::Loop;
    } else if (str == "pingpong") {
        loop = TweenLoop::PingPong;
    }

    auto tween = new TweenColor(from, to, duration, loop, TweenState::Playing);
    return tween;
}

c2d::TweenAlpha *XMLUtility::getTweenAlpha(tinyxml2::XMLElement *element) {

    if (!element || std::string(element->Value()) != "tweenAlpha") {
        return nullptr;
    }

    // parse rectangle outline
    float from = XMLUtility::getAttributeFloat(element, "from");
    float to = XMLUtility::getAttributeFloat(element, "to");
    float duration = XMLUtility::getAttributeFloat(element, "duration");
    TweenLoop loop = TweenLoop::None;
    std::string str = XMLUtility::getAttribute(element, "loop");
    if (str == "loop") {
        loop = TweenLoop::Loop;
    } else if (str == "pingpong") {
        loop = TweenLoop::PingPong;
    }

    auto tween = new TweenAlpha(from, to, duration, loop, TweenState::Playing);
    return tween;
}


