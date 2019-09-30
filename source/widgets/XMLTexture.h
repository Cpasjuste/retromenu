//
// Created by cpasjuste on 30/09/2019.
//

#ifndef RETROMENU_XMLTEXTURE_H
#define RETROMENU_XMLTEXTURE_H

#include <tinyxml2.h>
#include <cross2d/c2d.h>

class XMLTexture : public c2d::C2DTexture {

public:
    explicit XMLTexture(c2d::C2DObject *parent, tinyxml2::XMLNode *node, const std::string &path);
};

#endif //RETROMENU_XMLTEXTURE_H
