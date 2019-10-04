//
// Created by cpasjuste on 30/09/2019.
//

#ifndef RETROMENU_XMLTEXT_H
#define RETROMENU_XMLTEXT_H

#include "XMLWidget.h"

class XMLText : public c2d::C2DText, public XMLWidget {

public:

    explicit XMLText(tinyxml2::XMLNode *node, c2d::C2DObject *parent);

private:

    void load_derived(tinyxml2::XMLElement *element) override;

    void onUpdate() override;

    std::string xmlString;
    bool hasVars = false;
};

#endif //RETROMENU_XMLTEXT_H
