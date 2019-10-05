//
// Created by cpasjuste on 30/09/2019.
//

#include <cross2d/c2d.h>
#include "SceneManager.h"
#include "main.h"

using namespace c2d;
using namespace tinyxml2;

int main(int argc, char **argv) {

    // create main stuff
    auto renderer = new C2DRenderer({1280 / 2.0f, 720 / 2.0f});
    auto manager = new SceneManager(renderer, "skin.xml");

    auto scene = new Scene(manager->getSceneNode("LoadingScene"));
    renderer->add(scene);

    while (true) {

        // stop if any key is pressed
        if (renderer->getInput()->getKeys()) {
            break;
        }

        renderer->flip();
    }

    delete (renderer);
}
