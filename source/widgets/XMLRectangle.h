//
// Created by cpasjuste on 30/09/2019.
//

#ifndef RETROMENU_XMLRECTANGLE_H
#define RETROMENU_XMLRECTANGLE_H

#include <tinyxml2.h>
#include <cross2d/c2d.h>

class XMLRectangle : public c2d::C2DRectangle {

public:
    explicit XMLRectangle(tinyxml2::XMLNode *node);
};

#endif //RETROMENU_XMLRECTANGLE_H
