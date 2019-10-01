//
// Created by cpasjuste on 30/09/2019.
//

#include "XMLUtility.h"
#include "XMLRectangle.h"
#include "XMLText.h"
#include "XMLTexture.h"

using namespace c2d;

void XMLUtility::addChild(c2d::C2DObject *parent, tinyxml2::XMLNode *node) {

    std::string value = node->Value();

    if (value == "rectangle") {
        // ADD CHILD (RECTANGLE)
        auto obj = new XMLRectangle(parent, node);
        parent->add(obj);
    } else if (value == "texture") {
        // ADD CHILD (TEXTURE)
        tinyxml2::XMLElement *e = node->ToElement()->FirstChildElement("path");
        if (e) {
            std::string path = XMLUtility::getText(e);
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

void XMLUtility::addTween(c2d::C2DObject *parent, tinyxml2::XMLNode *node) {

    std::string value = node->Value();
    tinyxml2::XMLElement *element = node->ToElement();

    if (value == "tweenPosition") {
        auto tween = XMLUtility::getTweenPosition(element);
        if (tween) {
            parent->add(tween);
        }
    } else if (value == "tweenRotation") {
        auto tween = XMLUtility::getTweenRotation(element);
        if (tween) {
            parent->add(tween);
        }
    } else if (value == "tweenScale") {
        auto tween = XMLUtility::getTweenScale(element);
        if (tween) {
            parent->add(tween);
        }
    } else if (value == "tweenColor") {
        auto tween = XMLUtility::getTweenColor(element);
        if (tween) {
            parent->add(tween);
        }
    } else if (value == "tweenAlpha") {
        auto tween = XMLUtility::getTweenAlpha(element);
        if (tween) {
            parent->add(tween);
        }
    }
}

c2d::Vector2f XMLUtility::getParentSize(c2d::C2DObject *parent) {

    Vector2f parentSize{};

    if (parent) {
        if (parent->getType() == Type::Shape) {
            parentSize = ((XMLRectangle *) parent)->getSize();
        } else if (parent->getType() == Type::Texture) {
            parentSize = ((XMLTexture *) parent)->getSize();
        } else if (parent->getType() == Type::Text) {
            parentSize.x = ((XMLText *) parent)->getGlobalBounds().width;
            parentSize.y = ((XMLText *) parent)->getGlobalBounds().height;
        } else {
            // assume renderer is parent
            parentSize = ((Renderer *) parent)->getSize();
        }
    }

    return parentSize;
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
    if (str == "left") {
        origin = Origin::Left;
    } else if (str == "topLeft") {
        origin = Origin::TopLeft;
    } else if (str == "top") {
        origin = Origin::Top;
    } else if (str == "topRight") {
        origin = Origin::TopRight;
    } else if (str == "right") {
        origin = Origin::Right;
    } else if (str == "bottomRight") {
        origin = Origin::BottomRight;
    } else if (str == "bottom") {
        origin = Origin::Bottom;
    } else if (str == "bottomLeft") {
        origin = Origin::BottomLeft;
    } else if (str == "center") {
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

