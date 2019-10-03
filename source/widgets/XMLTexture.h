//
// Created by cpasjuste on 30/09/2019.
//

#ifndef RETROMENU_XMLTEXTURE_H
#define RETROMENU_XMLTEXTURE_H

#include "XMLWidget.h"

class XMLTexture : public c2d::C2DTexture, public XMLWidget {

public:
    explicit XMLTexture(tinyxml2::XMLNode *node, c2d::C2DObject *parent, const std::string &path);
};

#endif //RETROMENU_XMLTEXTURE_H
