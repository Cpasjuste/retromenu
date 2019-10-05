//
// Created by cpasjuste on 05/10/2019.
//

#include "LoadingScene.h"

using namespace ss_api;

LoadingScene::LoadingScene(SceneManager *sm) : Scene(sm->getSceneNode("LoadingScene")) {

    sm->setVar(LOADING_PERCENT, "0");
    gameList = Api::gameList("gamelist.xml", "roms");
    sm->setVar(LOADING_PERCENT, "100");
    printf("LoadingScene: gamelist contains %zu games\n", gameList.games.size());
}
