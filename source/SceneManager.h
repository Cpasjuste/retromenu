//
// Created by cpasjuste on 01/10/2019.
//

#ifndef RETROMENU_SCENEMANAGER_H
#define RETROMENU_SCENEMANAGER_H

#include <string>
#include <tinyxml2.h>
#include <scenes/Scene.h>

class SceneManager {

public:

    struct Font {
        c2d::Font *data;
        std::string path;
    };

    explicit SceneManager(c2d::Renderer *renderer, const std::string &xml);

    ~SceneManager();

    Scene *load(const std::string &name);

    void remove(const std::string &name);

    c2d::Font *getFont(const std::string &path);

private:

    tinyxml2::XMLDocument xmlDocument;
    tinyxml2::XMLNode *xmlRoot = nullptr;
    c2d::Renderer *renderer = nullptr;
    std::vector<Scene *> scenes;
    std::vector<Font> fonts;
};

extern SceneManager *sceneManager;

#endif //RETROMENU_SCENEMANAGER_H
