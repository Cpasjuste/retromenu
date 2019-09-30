//
// Created by cpasjuste on 30/09/2019.
//

#ifndef RETROMENU_XMLTEXT_H
#define RETROMENU_XMLTEXT_H

#include <tinyxml2.h>
#include <cross2d/c2d.h>

class XMLText : public c2d::C2DText {

public:
    explicit XMLText(tinyxml2::XMLNode *node);
};

#endif //RETROMENU_XMLTEXT_H
