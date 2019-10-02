//
// Created by cpasjuste on 02/10/2019.
//

#ifndef RETROMENU_XMLWIDGET_H
#define RETROMENU_XMLWIDGET_H

#include <tinyxml2.h>

class XMLWidget {

public:

    enum class Type {
        Rectangle, Texture, Text
    };

    explicit XMLWidget(const Type &type, XMLWidget *parent, tinyxml2::XMLNode *node);

    void load();

    void addChild(tinyxml2::XMLNode *node);

    virtual void setPosition(float x, float y) {};

    virtual void setPosition(const c2d::Vector2f &position) {};

    virtual const c2d::Vector2f &getSize() const {};

    virtual void setSize(const c2d::Vector2f &size) {};

    virtual void setSize(float width, float height) {};

    virtual void setOrigin(const c2d::Origin &origin) {};

    c2d::Vector2f getParentSize();

    Type type = Type::Rectangle;

private:

    XMLWidget *parent = nullptr;
    tinyxml2::XMLNode *node = nullptr;
};

#endif //RETROMENU_XMLWIDGET_H
