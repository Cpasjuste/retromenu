//
// Created by cpasjuste on 30/09/2019.
//

#ifndef RETROMENU_XMLUTILITY_H
#define RETROMENU_XMLUTILITY_H

#include <string>
#include <tinyxml2.h>
#include <cross2d/c2d.h>

class XMLUtility {

public:

    static bool loadSection(c2d::C2DObject *object, tinyxml2::XMLNode *node);

    static std::string getAttribute(tinyxml2::XMLElement *element, const std::string &name);

    static int getAttributeInt(tinyxml2::XMLElement *element, const std::string &name);

    static float getAttributeFloat(tinyxml2::XMLElement *element, const std::string &name);

    static std::string getText(tinyxml2::XMLElement *element);

    static int getTextInt(tinyxml2::XMLElement *element);

    static c2d::FloatRect getRectangle(tinyxml2::XMLElement *element);

    static c2d::Color getColor(tinyxml2::XMLElement *element);

    static c2d::Color getOutlineColor(tinyxml2::XMLElement *element);

    static int getOutlineSize(tinyxml2::XMLElement *element);

    static c2d::Origin getOrigin(tinyxml2::XMLElement *element);

    static c2d::TweenPosition *getTweenPosition(tinyxml2::XMLElement *element);

    static c2d::TweenRotation *getTweenRotation(tinyxml2::XMLElement *element);

    static c2d::TweenScale *getTweenScale(tinyxml2::XMLElement *element);

    static c2d::TweenColor *getTweenColor(tinyxml2::XMLElement *element);

    static c2d::TweenAlpha *getTweenAlpha(tinyxml2::XMLElement *element);
};

#endif //RETROMENU_XMLUTILITY_H
