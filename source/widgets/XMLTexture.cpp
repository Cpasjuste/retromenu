//
// Created by cpasjuste on 30/09/2019.
//

#include "SceneManager.h"
#include "XMLTexture.h"

using namespace c2d;

XMLTexture::XMLTexture(tinyxml2::XMLNode *node, C2DObject *parent, const std::string &path)
        : Sprite(), XMLWidget(node, parent) {

    printf("XMLTexture()\n");
    auto tex = (C2DTexture *) sceneManager->getTexture(path);
    setTexture(tex, true);
    load(this);
}
