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

    if (!isVisible()) {
        return;
    }

    if (hasVars) {

        size_t pos = 0, end = 0;
        std::string var, line = xmlString;
        while ((pos = line.find("${", end - pos)) != std::string::npos) {
            end = line.find('}', pos) + 1;
            var = sceneManager->getVar(line.substr(pos, end - pos));
            line.replace(pos, end - pos, var);
        }

        if (getString() != line) {
            setString(line);
        }
    }

    Text::onUpdate();
}
