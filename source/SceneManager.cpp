//
// Created by cpasjuste on 01/10/2019.
//

#include "SceneManager.h"

// TODO: this is not really clean, but this is safe
SceneManager *sceneManager;

SceneManager::SceneManager(c2d::Renderer *r, const std::string &x) {

    sceneManager = this;
    renderer = r;
    tinyxml2::XMLError e = xmlDocument.LoadFile(x.c_str());
    if (e != tinyxml2::XML_SUCCESS) {
        printf("main: %s\n", tinyxml2::XMLDocument::ErrorIDToName(e));
        return;
    }

    xmlRoot = xmlDocument.FirstChildElement("Skin");
    if (!xmlRoot) {
        printf("main: Skin node not found\n");
        return;
    }
}

SceneManager::~SceneManager() {
    xmlDocument.Clear();
    for (const auto &font : fonts) {
        delete (font.data);
    }
}

Scene *SceneManager::load(const std::string &name) {

    tinyxml2::XMLNode *sceneNode = xmlRoot->FirstChildElement(name.c_str());
    if (!sceneNode) {
        printf("Scene::Scene(): could not find Scene xml node\n");
        return nullptr;
    }

    auto scene = new Scene(name, nullptr, sceneNode);
    scenes.emplace_back(scene);
    return scene;
}

void SceneManager::remove(const std::string &name) {

    auto scene = std::find_if(scenes.begin(), scenes.end(), [&name](Scene *scene) {
        return scene->getName() == name;
    });

    if (*scene) {
        delete (*scene);
    }
}

c2d::Font *SceneManager::getFont(const std::string &path) {

    auto font = std::find_if(fonts.begin(), fonts.end(), [&path](const Font &font) {
        return font.path == path;
    });

    if (font != fonts.end()) {
        printf("SceneManager::getFont: font already loaded (%s)\n", path.c_str());
        return (*font).data;
    }

    auto data = new c2d::Font();
    if (!data->loadFromFile(path)) {
        fprintf(stderr, "SceneManager::getFont: font not found (%s)\n", path.c_str());
        delete (data);
        // return default (built-in) font
        return renderer->getFont();
    }

    fonts.push_back({data, path});

    return data;
}
