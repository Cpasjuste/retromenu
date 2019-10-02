//
// Created by cpasjuste on 30/09/2019.
//

#ifndef RETROMENU_XMLRECTANGLE_H
#define RETROMENU_XMLRECTANGLE_H

#include <tinyxml2.h>
#include <cross2d/c2d.h>
#include "XMLWidget.h"

class XMLRectangle : public c2d::C2DRectangle, public XMLWidget {

public:

    explicit XMLRectangle(XMLWidget *parent, tinyxml2::XMLNode *node);

    void setPosition(float x, float y) override { c2d::C2DRectangle::setPosition(x, y); };

    void setPosition(const c2d::Vector2f &position) override { c2d::C2DRectangle::setPosition(position); };

    const c2d::Vector2f &getSize() const override { return c2d::C2DRectangle::getSize(); };

    void setSize(const c2d::Vector2f &size) override { c2d::C2DRectangle::setSize(size); };

    void setSize(float width, float height) override { c2d::C2DRectangle::setSize(width, height); };

    void setOrigin(const c2d::Origin &origin) override { c2d::C2DRectangle::setOrigin(origin); };
};

#endif //RETROMENU_XMLRECTANGLE_H
