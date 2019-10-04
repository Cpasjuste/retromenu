//
// Created by cpasjuste on 02/10/2019.
//

#include <cstdio>
#include "XMLWidget.h"
#include "XMLRectangle.h"
#include "XMLTexture.h"
#include "XMLText.h"

using namespace c2d;

XMLWidget::XMLWidget(tinyxml2::XMLNode *n, c2d::C2DObject *p) {

    printf("XMLWidget()\n");
    parent = p;
    node = n;
}

void XMLWidget::load(c2d::C2DObject *w) {

    widget = w;

    // parse size and origin
    Vector2f parentSize = getParentSize();
    FloatRect rect = getRectangle(node->ToElement(), parentSize);
    widget->setPosition(rect.left, rect.top);
    widget->setSize(rect.width, rect.height);
    widget->setOrigin(getOrigin(node->ToElement()));

    // parse xml child's
    tinyxml2::XMLNode *child = node->FirstChild();
    while (child) {

        tinyxml2::XMLElement *element = child->ToElement();
        std::string value = child->Value();

        // add child object
        if (value == "rectangle" || value == "texture" || value == "text") {
            add(child);
        } else if (Utility::startWith(value, "tween")) {
            addTween(widget, parentSize, child);
        } else {
            // this object values
            if (value == "color") {
                widget->setFillColor(getColor(element));
            } else if (value == "outline") {
                widget->setOutlineColor(getColor(element));
                widget->setOutlineThickness((float) getOutlineSize(element));
            } else if (value == "ratio") {
                if (getText(element) == "keep_width") {
                    widget->setScale(widget->getScale().x, widget->getScale().x);
                } else if (getText(element) == "keep_height") {
                    widget->setScale(widget->getScale().y, widget->getScale().y);
                }
            }
            // parse derived class custom values
            load_derived(element);
        }

        child = child->NextSibling();
    }
}

void XMLWidget::add(tinyxml2::XMLNode *n) {

    std::string value = n->Value();
    if (value == "rectangle") {
        auto obj = new XMLRectangle(n, widget);
        widget->add(obj);
    } else if (value == "texture") {
        tinyxml2::XMLElement *e = n->ToElement()->FirstChildElement("path");
        if (e) {
            std::string path = getText(e);
            if (!path.empty()) {
                auto obj = new XMLTexture(n, widget, path);
                widget->add(obj);
            }
        }
    } else if (value == "text") {
        auto obj = new XMLText(n, widget);
        widget->add(obj);
    }
}

c2d::Vector2f XMLWidget::getParentSize() {

    if (parent) {
        return parent->getSize();
    }

    return c2d_renderer->getSize();
}

float XMLWidget::parseSize(const std::string &attribute, float parentSize) {

    if (Utility::contains(attribute, "%")) {
        float scaling = Utility::parseFloat(Utility::remove(attribute, "%")) / 100;
        return parentSize * scaling;
    } else if (Utility::contains(attribute, "-")) {
        return parentSize - Utility::parseFloat(Utility::remove(attribute, "-"));
    }

    return Utility::parseFloat(attribute);
}

void XMLWidget::addTween(c2d::C2DObject *parent, const c2d::Vector2f &parentSize, tinyxml2::XMLNode *node) {

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

c2d::TweenPosition *XMLWidget::getTweenPosition(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize) {

    if (!element || std::string(element->Value()) != "tweenPosition") {
        return nullptr;
    }

    Vector2f from = {
            parseSize(getAttribute(element, "from.x"), parentSize.x),
            parseSize(getAttribute(element, "from.y"), parentSize.y)
    };
    Vector2f to = {
            parseSize(getAttribute(element, "to.x"), parentSize.x),
            parseSize(getAttribute(element, "to.y"), parentSize.y)
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

c2d::TweenRotation *XMLWidget::getTweenRotation(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize) {

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

c2d::TweenScale *XMLWidget::getTweenScale(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize) {

    if (!element || std::string(element->Value()) != "tweenScale") {
        return nullptr;
    }

    Vector2f from = {
            getAttributeFloat(element, "from.x"),
            getAttributeFloat(element, "from.y")
    };
    Vector2f to = {
            getAttributeFloat(element, "to.x"),
            getAttributeFloat(element, "to.y")
    };

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

c2d::TweenColor *XMLWidget::getTweenColor(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize) {

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

c2d::TweenAlpha *XMLWidget::getTweenAlpha(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize) {

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

c2d::FloatRect XMLWidget::getRectangle(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize) {

    FloatRect rect{};

    if (element) {
        rect.left = parseSize(getAttribute(element, "x"), parentSize.x);
        rect.top = parseSize(getAttribute(element, "y"), parentSize.y);
        rect.width = parseSize(getAttribute(element, "w"), parentSize.x);
        rect.height = parseSize(getAttribute(element, "h"), parentSize.y);
    }

    return rect;
}

c2d::Color XMLWidget::getColor(tinyxml2::XMLElement *element) {

    Color color{};

    if (element) {
        color.r = getAttributeInt(element, "r");
        color.g = getAttributeInt(element, "g");
        color.b = getAttributeInt(element, "b");
        color.a = getAttributeInt(element, "a");
    }

    return color;
}

int XMLWidget::getOutlineSize(tinyxml2::XMLElement *element) {

    int size = 0;

    if (element) {
        size = getAttributeInt(element, "size");
    }

    return size;
}

c2d::Origin XMLWidget::getOrigin(tinyxml2::XMLElement *element) {

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

///
/// XML helper's
///
std::string XMLWidget::getAttribute(tinyxml2::XMLElement *element, const std::string &name) {

    if (!element || !element->Attribute(name.c_str())) {
        return "";
    }

    return element->Attribute(name.c_str());
}

int XMLWidget::getAttributeInt(tinyxml2::XMLElement *element, const std::string &name) {
    return Utility::parseInt(getAttribute(element, name));
}

float XMLWidget::getAttributeFloat(tinyxml2::XMLElement *element, const std::string &name) {
    return Utility::parseFloat(getAttribute(element, name));
}

std::string XMLWidget::getText(tinyxml2::XMLElement *element) {

    if (!element || !element->GetText()) {
        return "";
    }

    return element->GetText();
}

int XMLWidget::getTextInt(tinyxml2::XMLElement *element) {
    return Utility::parseInt(getText(element));
}

float XMLWidget::getTextFloat(tinyxml2::XMLElement *element) {
    return Utility::parseFloat(getText(element));
}
