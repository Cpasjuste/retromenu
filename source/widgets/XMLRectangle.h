//
// Created by cpasjuste on 30/09/2019.
//

#ifndef RETROMENU_XMLRECTANGLE_H
#define RETROMENU_XMLRECTANGLE_H

#include "XMLWidget.h"

class XMLRectangle : public c2d::C2DRectangle, public XMLWidget {

public:
    explicit XMLRectangle(tinyxml2::XMLNode *node, c2d::C2DObject *parent);
};

#endif //RETROMENU_XMLRECTANGLE_H
