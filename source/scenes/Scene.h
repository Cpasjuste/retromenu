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

    explicit Scene(const std::string &name, XMLWidget *parent, tinyxml2::XMLNode *root);

    std::string getName();

private:

    std::string name;
};

#endif //RETROMENU_SCENE_H
