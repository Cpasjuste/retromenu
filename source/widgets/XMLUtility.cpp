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
        rect.left = getSize(getAttribute(element, "x"), parentSize.x);
        rect.top = getSize(getAttribute(element, "y"), parentSize.y);
        rect.width = getSize(getAttribute(element, "w"), parentSize.x);
        rect.height = getSize(getAttribute(element, "h"), parentSize.y);
    }

    return rect;
}

float XMLUtility::getSize(const std::string &attribute, float parentSize) {

    if (Utility::contains(attribute, "%")) {
        float scaling = Utility::parseFloat(Utility::remove(attribute, "%")) / 100;
        return parentSize * scaling;
    } else if (Utility::contains(attribute, "-")) {
        return parentSize - Utility::parseFloat(Utility::remove(attribute, "-"));
    }

    return Utility::parseFloat(attribute);
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

void XMLUtility::addTween(c2d::C2DObject *parent, const c2d::Vector2f &parentSize, tinyxml2::XMLNode *node) {

    std::string value = node->Value();
    tinyxml2::XMLElement *element = node->ToElement();

    if (value == "tweenPosition") {
        auto tween = getTweenPosition(element, parentSize);
        if (tween) {
            parent->add(tween);
        }
    } else if (value == "tweenRotation") {
        auto tween = getTweenRotation(element, parentSize);
        if (tween) {
            parent->add(tween);
        }
    } else if (value == "tweenScale") {
        auto tween = getTweenScale(element, parentSize);
        if (tween) {
            parent->add(tween);
        }
    } else if (value == "tweenColor") {
        auto tween = getTweenColor(element, parentSize);
        if (tween) {
            parent->add(tween);
        }
    } else if (value == "tweenAlpha") {
        auto tween = getTweenAlpha(element, parentSize);
        if (tween) {
            parent->add(tween);
        }
    }
}

c2d::TweenPosition *XMLUtility::getTweenPosition(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize) {

    if (!element || std::string(element->Value()) != "tweenPosition") {
        return nullptr;
    }

    Vector2f from = {
            getSize(getAttribute(element, "fromX"), parentSize.x),
            getSize(getAttribute(element, "fromY"), parentSize.y)
    };
    Vector2f to = {
            getSize(getAttribute(element, "toX"), parentSize.x),
            getSize(getAttribute(element, "toY"), parentSize.y)
    };
    float duration = getAttributeFloat(element, "duration");
    TweenLoop loop = TweenLoop::None;
    std::string str = getAttribute(element, "loop");
    if (str == "loop") {
        loop = TweenLoop::Loop;
    } else if (str == "pingpong") {
        loop = TweenLoop::PingPong;
    }

    return new TweenPosition(from, to, duration, loop, TweenState::Playing);
}

c2d::TweenRotation *XMLUtility::getTweenRotation(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize) {

    if (!element || std::string(element->Value()) != "tweenRotation") {
        return nullptr;
    }

    float from = (float) getAttributeInt(element, "from");
    float to = (float) getAttributeInt(element, "to");
    float duration = getAttributeFloat(element, "duration");
    TweenLoop loop = TweenLoop::None;
    std::string str = getAttribute(element, "loop");
    if (str == "loop") {
        loop = TweenLoop::Loop;
    } else if (str == "pingpong") {
        loop = TweenLoop::PingPong;
    }

    auto tween = new TweenRotation(from, to, duration, loop, TweenState::Playing);
    return tween;
}

c2d::TweenScale *XMLUtility::getTweenScale(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize) {

    if (!element || std::string(element->Value()) != "tweenScale") {
        return nullptr;
    }

    Vector2f from = {getAttributeFloat(element, "fromX"),
                     getAttributeFloat(element, "fromY")};
    Vector2f to = {getAttributeFloat(element, "toX"),
                   getAttributeFloat(element, "toY")};
    float duration = getAttributeFloat(element, "duration");
    TweenLoop loop = TweenLoop::None;
    std::string str = getAttribute(element, "loop");
    if (str == "loop") {
        loop = TweenLoop::Loop;
    } else if (str == "pingpong") {
        loop = TweenLoop::PingPong;
    }

    auto tween = new TweenScale(from, to, duration, loop, TweenState::Playing);
    return tween;
}

c2d::TweenColor *XMLUtility::getTweenColor(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize) {

    if (!element || std::string(element->Value()) != "tweenColor") {
        return nullptr;
    }

    Color from = {getAttributeInt(element, "fromR"),
                  getAttributeInt(element, "fromG"),
                  getAttributeInt(element, "fromB"),
                  getAttributeInt(element, "fromA")};
    Color to = {getAttributeInt(element, "toR"),
                getAttributeInt(element, "toG"),
                getAttributeInt(element, "toB"),
                getAttributeInt(element, "toA")};
    float duration = getAttributeFloat(element, "duration");
    TweenLoop loop = TweenLoop::None;
    std::string str = getAttribute(element, "loop");
    if (str == "loop") {
        loop = TweenLoop::Loop;
    } else if (str == "pingpong") {
        loop = TweenLoop::PingPong;
    }

    auto tween = new TweenColor(from, to, duration, loop, TweenState::Playing);
    return tween;
}

c2d::TweenAlpha *XMLUtility::getTweenAlpha(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize) {

    if (!element || std::string(element->Value()) != "tweenAlpha") {
        return nullptr;
    }

    // parse rectangle outline
    float from = getAttributeFloat(element, "from");
    float to = getAttributeFloat(element, "to");
    float duration = getAttributeFloat(element, "duration");
    TweenLoop loop = TweenLoop::None;
    std::string str = getAttribute(element, "loop");
    if (str == "loop") {
        loop = TweenLoop::Loop;
    } else if (str == "pingpong") {
        loop = TweenLoop::PingPong;
    }

    auto tween = new TweenAlpha(from, to, duration, loop, TweenState::Playing);
    return tween;
}
