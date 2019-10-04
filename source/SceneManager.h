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

    struct Variable {
        std::string name;
        std::string value;
    };

    explicit SceneManager(c2d::Renderer *renderer, const std::string &xml);

    ~SceneManager();

    Scene *load(const std::string &name);

    void remove(const std::string &name);

    c2d::Font *getFont(const std::string &path);

    c2d::Texture *getTexture(const std::string &path);

    void setVar(const std::string &name, const std::string &value);

    const std::string &getVar(const std::string &name);

private:

    tinyxml2::XMLDocument xmlDocument;
    tinyxml2::XMLNode *xmlRoot = nullptr;
    c2d::Renderer *renderer = nullptr;
    std::vector<Scene *> scenes;
    std::vector<c2d::Font *> fonts;
    std::vector<c2d::Texture *> textures;
    std::vector<Variable> variables;
};

extern SceneManager *sceneManager;

#endif //RETROMENU_SCENEMANAGER_H
