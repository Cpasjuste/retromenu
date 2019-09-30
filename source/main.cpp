//
// Created by cpasjuste on 30/09/2019.
//

#include <cstdio>
#include <tinyxml2.h>
#include <cross2d/c2d.h>
#include "scenes/Scene.h"
#include "main.h"

using namespace c2d;
using namespace tinyxml2;

int main(int argc, char **argv) {

    // create main renderer
    auto renderer = new C2DRenderer({1280, 720});

    // load xml (testing)
    XMLDocument doc;
    XMLError e = doc.LoadFile("skin.xml");
    if (e != XML_SUCCESS) {
        printf("main: %s\n", tinyxml2::XMLDocument::ErrorIDToName(e));
        return -1;
    }

    XMLNode *root = doc.FirstChildElement("Skin");
    if (!root) {
        printf("main: Skin node not found\n");
        return -1;
    }

    XMLNode *sceneNode = root->FirstChildElement("LoadingScene");
    if (!sceneNode) {
        printf("Scene::Scene(): could not find Scene xml node\n");
        return -1;
    }

    auto scene = new Scene(renderer, sceneNode);
    renderer->add(scene);

    while (true) {

        // stop if any key is pressed
        if (renderer->getInput()->getKeys()) {
            break;
        }

        renderer->flip();
    }

    doc.Clear();
    delete (renderer);
}
