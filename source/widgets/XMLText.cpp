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
        xmlString = XMLWidget::getText(element);
        hasVars = Utility::contains(xmlString, "${");
        setString(xmlString);
    } else if (value == "font") {
        std::string path = XMLWidget::getText(element);
        setFont(sceneManager->getFont(path));
    }
}

void XMLText::onUpdate() {

    if (!isVisible() || !hasVars) {
        return;
    }

    std::string str;
    std::vector<std::string> split = Utility::split(xmlString, "${");
    for (const auto &s : split) {
        if (Utility::contains(s, "}")) {
            str += sceneManager->getVar(Utility::remove(s, "}"));
        } else {
            str += s;
        }
    }

    if (getString() != str) {
        setString(str);
    }

    Text::onUpdate();
}
