//
// Created by cpasjuste on 30/09/2019.
//

#include <cross2d/c2d.h>
#include "XMLUtility.h"
#include "XMLRectangle.h"
#include "XMLText.h"
#include "XMLTexture.h"

using namespace c2d;

bool XMLUtility::loadObject(c2d::C2DObject *me, c2d::C2DObject *parent, tinyxml2::XMLNode *node) {

    if (!node) {
        fprintf(stderr, "XMLUtility::loadObject: xml node is null\n");
        return false;
    }

    XMLRectangle *rectangle = me->getType() == Type::Shape ? (XMLRectangle *) me : nullptr;
    XMLTexture *texture = me->getType() == Type::Texture ? (XMLTexture *) me : nullptr;
    XMLText *text = me->getType() == Type::Text ? (XMLText *) me : nullptr;

    // get parent size for percent capability
    Vector2f parentSize{};
    if (parent) {
        if (parent->getType() == Type::Shape) {
            parentSize = ((XMLRectangle *) parent)->getSize();
        } else if (parent->getType() == Type::Texture) {
            parentSize = ((XMLTexture *) parent)->getSize();
        } else if (parent->getType() == Type::Text) {
            parentSize.x = ((XMLText *) parent)->getLocalBounds().width;
            parentSize.y = ((XMLText *) parent)->getLocalBounds().height;
        } else {
            // assume renderer is parent
            parentSize = ((Renderer *) parent)->getSize();
        }
    }

    // parse size and origin
    FloatRect rect = XMLUtility::getRectangle(node->ToElement(), parentSize);
    Origin origin = XMLUtility::getOrigin(node->ToElement());
    if (rectangle) {
        rectangle->setPosition(rect.left, rect.top);
        rectangle->setSize(rect.width, rect.height);
        rectangle->setOrigin(origin);
    } else if (texture) {
        texture->setPosition(rect.left, rect.top);
        texture->setScale(rect.width / texture->getSize().x, rect.height / texture->getSize().y);
        texture->setOrigin(origin);
    } else if (text) {
        text->setCharacterSize((unsigned int) rect.height);
        text->setPosition(rect.left, rect.top);
        text->setSizeMax(rect.width, rect.height);
        text->setOrigin(origin);
    }

    // parse child's
    tinyxml2::XMLNode *child = node->FirstChild();
    while (child) {
        tinyxml2::XMLElement *element = child->ToElement();
        std::string value = child->Value();
        if (value == "rectangle") {
            auto obj = new XMLRectangle(me, child);
            me->add(obj);
        } else if (value == "texture") {
            tinyxml2::XMLElement *e = element->FirstChildElement("path");
            if (e) {
                std::string path = getText(e);
                if (!path.empty()) {
                    auto obj = new XMLTexture(me, child, path);
                    me->add(obj);
                }
            }
        } else if (value == "text") {
            auto obj = new XMLText(me, child);
            me->add(obj);
        } else if (value == "string") {
            text->setString(getText(element));
        } else if (value == "color") {
            Color color = XMLUtility::getColor(element);
            if (rectangle) {
                rectangle->setFillColor(color);
            } else if (texture) {
                texture->setFillColor(color);
            } else if (text) {
                text->setFillColor(color);
            }
        } else if (value == "outline") {
            Color color = XMLUtility::getOutlineColor(element);
            int size = XMLUtility::getOutlineSize(element);
            if (rectangle) {
                rectangle->setOutlineColor(color);
                rectangle->setOutlineThickness((float) size);
            } else if (texture) {
                texture->setOutlineColor(color);
                texture->setOutlineThickness((float) size);
            } else if (text) {
                text->setOutlineColor(color);
                text->setOutlineThickness((float) size);
            }
        } else if (value == "ratio") {
            // TODO

        } else if (value == "tweenPosition") {
            auto tween = XMLUtility::getTweenPosition(element);
            if (tween) {
                me->add(tween);
            }
        } else if (value == "tweenRotation") {
            auto tween = XMLUtility::getTweenRotation(element);
            if (tween) {
                me->add(tween);
            }
        } else if (value == "tweenScale") {
            auto tween = XMLUtility::getTweenScale(element);
            if (tween) {
                me->add(tween);
            }
        } else if (value == "tweenColor") {
            auto tween = XMLUtility::getTweenColor(element);
            if (tween) {
                me->add(tween);
            }
        } else if (value == "tweenAlpha") {
            auto tween = XMLUtility::getTweenAlpha(element);
            if (tween) {
                me->add(tween);
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

c2d::FloatRect XMLUtility::getRectangle(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize) {

    FloatRect rect{};

    if (element) {
        std::string x = getAttribute(element, "x");
        std::string y = getAttribute(element, "y");
        std::string w = getAttribute(element, "w");
        std::string h = getAttribute(element, "h");

        if (Utility::contains(x, "%")) {
            float scaling = Utility::parseFloat(Utility::remove(x, "%")) / 100;
            rect.left = parentSize.x * scaling;
        } else {
            rect.left = getAttributeInt(element, "x");
        }

        if (Utility::contains(y, "%")) {
            float scaling = Utility::parseFloat(Utility::remove(y, "%")) / 100;
            rect.top = parentSize.y * scaling;
        } else {
            rect.top = getAttributeInt(element, "y");
        }

        if (Utility::contains(w, "%")) {
            float scaling = Utility::parseFloat(Utility::remove(w, "%")) / 100.0f;
            rect.width = parentSize.x * scaling;
        } else if (Utility::contains(w, "-")) {
            rect.width = parentSize.x - Utility::parseFloat(Utility::remove(w, "-"));
        } else {
            rect.width = getAttributeInt(element, "w");
        }

        if (Utility::contains(h, "%")) {
            float scaling = Utility::parseFloat(Utility::remove(h, "%")) / 100;
            rect.height = parentSize.y * scaling;
        } else if (Utility::contains(h, "-")) {
            rect.height = parentSize.y - Utility::parseFloat(Utility::remove(h, "-"));
        } else {
            rect.height = getAttributeInt(element, "h");
        }
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


