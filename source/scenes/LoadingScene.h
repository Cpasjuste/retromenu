//
// Created by cpasjuste on 05/10/2019.
//

#ifndef RETROMENU_LOADINGSCENE_H
#define RETROMENU_LOADINGSCENE_H

#include "ss_api.h"
#include "SceneManager.h"
#include "Scene.h"

class LoadingScene : public Scene {

public:

    explicit LoadingScene(SceneManager *sm);

private:

    ss_api::Api::GameList gameList;
};

#endif //RETROMENU_LOADINGSCENE_H
