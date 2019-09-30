//
// Created by cpasjuste on 30/09/2019.
//

#ifndef RETROMENU_SCENE_H
#define RETROMENU_SCENE_H

#include <tinyxml2.h>
#include <cross2d/c2d.h>
#include "widgets/XMLRectangle.h"

class Scene : public XMLRectangle {

public:

    explicit Scene(c2d::C2DObject *parent, tinyxml2::XMLNode *root);
};

#endif //RETROMENU_SCENE_H
