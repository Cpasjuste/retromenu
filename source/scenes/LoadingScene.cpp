//
// Created by cpasjuste on 05/10/2019.
//

#include "LoadingScene.h"

using namespace ss_api;

LoadingScene::LoadingScene(SceneManager *sm) : Scene(sm->getSceneNode("LoadingScene")) {

    sm->setVar(LOADING_PERCENT, "0");
    gameList = Api::gameList("gamelist.xml", "/media/cpasjuste/SSD/emulation/fba_0.2.97.44/roms/");
    sm->setVar(LOADING_PERCENT, "100");
    sm->setVar(GAMES_AVAILABLE, std::to_string(gameList.roms_count));
    sm->setVar(GAMES_COUNT, std::to_string(gameList.games.size()));

    printf("LoadingScene: gamelist contains %zu games, available roms: %i\n",
           gameList.games.size(), gameList.roms_count);
}
