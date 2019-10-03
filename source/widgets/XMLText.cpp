//
// Created by cpasjuste on 30/09/2019.
//

#include "SceneManager.h"
#include "XMLText.h"

using namespace c2d;

XMLText::XMLText(tinyxml2::XMLNode *node, c2d::C2DObject *parent)
        : C2DText(""), XMLWidget(node, parent) {

    printf("XMLText()\n");
    load(this);
}

void XMLText::load_derived(tinyxml2::XMLElement *element) {

    std::string value = element->Value();
    if (value == "string") {
        setString(XMLWidget::getText(element));
    } else if (value == "font") {
        std::string path = XMLWidget::getText(element);
        setFont(sceneManager->getFont(path));
    }
}
