//
// Created by cpasjuste on 30/09/2019.
//

#include "widgets/XMLUtility.h"
#include "widgets/XMLRectangle.h"
#include "LoadingWindow.h"

using namespace c2d;
using namespace tinyxml2;

LoadingWindow::LoadingWindow(tinyxml2::XMLNode *root) : Rectangle(Vector2f()) {

    if (!root) {
        printf("LoadingWindow::LoadingWindow(): could not find root xml node\n");
        setVisibility(Visibility::Hidden);
        return;
    }

    XMLNode *node = root->FirstChildElement("LoadingWindow");
    if (!node) {
        printf("LoadingWindow::LoadingWindow(): could not find LoadingWindow xml node\n");
        setVisibility(Visibility::Hidden);
        return;
    }

    XMLUtility::loadSection(this, node);

    /*
    // parse rectangle size
    FloatRect rect = XMLUtility::getRectangle(node->ToElement());
    setPosition(rect.left, rect.top);
    setSize(rect.width, rect.height);
    // parse origin
    Origin origin = XMLUtility::getOrigin(node->ToElement());
    setOrigin(origin);

    XMLNode *child = node->FirstChild();
    while (child) {
        //printf("child: %s\n", child->Value());
        if (std::string(child->Value()) == "rectangle") {
            auto rectangle = new XMLRectangle(child);
            add(rectangle);

        }
        child = child->NextSibling();
    }
    */
}
