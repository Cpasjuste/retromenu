//
// Created by cpasjuste on 30/09/2019.
//

#include <cross2d/c2d.h>
#include "scenes/LoadingScene.h"
#include "SceneManager.h"
#include "main.h"

using namespace c2d;
using namespace tinyxml2;

int main(int argc, char **argv) {
    // create main stuff
    auto renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});
    auto manager = new SceneManager(renderer, "skin.xml");

    auto scene = new LoadingScene(manager);
    renderer->add((Scene *) scene);

    while (true) {

        // stop if any key is pressed
        if (renderer->getInput()->getButtons()) {
            break;
        }

        renderer->flip();
    }

    delete (renderer);
}
