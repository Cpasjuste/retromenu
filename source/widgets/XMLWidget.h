//
// Created by cpasjuste on 02/10/2019.
//

#ifndef RETROMENU_XMLWIDGET_H
#define RETROMENU_XMLWIDGET_H

#include <tinyxml2.h>
#include <cross2d/c2d.h>

class XMLWidget {

public:

    explicit XMLWidget(tinyxml2::XMLNode *node, c2d::C2DObject *parent);

    void load(c2d::C2DObject *widget);

    static std::string getAttribute(tinyxml2::XMLElement *element, const std::string &name);

    static int getAttributeInt(tinyxml2::XMLElement *element, const std::string &name);

    static float getAttributeFloat(tinyxml2::XMLElement *element, const std::string &name);

    static std::string getText(tinyxml2::XMLElement *element);

    static int getTextInt(tinyxml2::XMLElement *element);

    static float getTextFloat(tinyxml2::XMLElement *element);

private:

    void add(tinyxml2::XMLNode *node);

    virtual void parse(tinyxml2::XMLElement *element) {};

    static void addTween(c2d::C2DObject *parent, const c2d::Vector2f &parentSize, tinyxml2::XMLNode *node);

    static c2d::FloatRect getRectangle(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize);

    static c2d::Color getColor(tinyxml2::XMLElement *element);

    static int getOutlineSize(tinyxml2::XMLElement *element);

    static c2d::Origin getOrigin(tinyxml2::XMLElement *element);

    static c2d::TweenPosition *getTweenPosition(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize);

    static c2d::TweenRotation *getTweenRotation(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize);

    static c2d::TweenScale *getTweenScale(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize);

    static c2d::TweenColor *getTweenColor(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize);

    static c2d::TweenAlpha *getTweenAlpha(tinyxml2::XMLElement *element, const c2d::Vector2f &parentSize);

    static float parseSize(const std::string &attribute, float parentSize);

    c2d::Vector2f getParentSize();

    c2d::C2DObject *widget = nullptr;
    c2d::C2DObject *parent = nullptr;
    tinyxml2::XMLNode *node = nullptr;
};

#endif //RETROMENU_XMLWIDGET_H
