//
// Created by cpasjuste on 01/10/2019.
//

#include "SceneManager.h"

using namespace c2d;

// TODO: this is not really clean, but well...
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

    setVar("LOADING_PERCENT", "100");
}

SceneManager::~SceneManager() {

    xmlDocument.Clear();

    for (const auto &texture : textures) {
        delete (texture);
    }

    for (const auto &font : fonts) {
        delete (font);
    }
}

Scene *SceneManager::load(const std::string &name) {

    tinyxml2::XMLNode *sceneNode = xmlRoot->FirstChildElement(name.c_str());
    if (!sceneNode) {
        printf("Scene::Scene(): could not find Scene xml node\n");
        return nullptr;
    }

    auto scene = new Scene(sceneNode, nullptr, name);
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

    auto font = std::find_if(fonts.begin(), fonts.end(), [&path](Font *fnt) {
        return fnt->getPath() == path;
    });

    if (font != fonts.end()) {
        return *font;
    }

    auto fnt = new c2d::Font();
    if (!fnt->loadFromFile(path)) {
        fprintf(stderr, "SceneManager::getFont: font not found (%s)\n", path.c_str());
        delete (fnt);
        // return default (built-in) font
        return renderer->getFont();
    }

    fonts.push_back(fnt);
    return fnt;
}

c2d::Texture *SceneManager::getTexture(const std::string &path) {

    auto texture = std::find_if(textures.begin(), textures.end(), [&path](Texture *tex) {
        return tex->path == path;
    });

    if (texture != textures.end()) {
        return *texture;
    }

    auto tex = new C2DTexture(path);
    textures.push_back(tex);
    return tex;
}

void SceneManager::setVar(const std::string &name, const std::string &value) {

    auto var = std::find_if(variables.begin(), variables.end(), [&name](const Variable &variable) {
        return variable.name == name;
    });

    if (var != variables.end()) {
        (*var).value = value;
    } else {
        variables.push_back({name, value});
    }
}

const std::string &SceneManager::getVar(const std::string &name) {

    auto var = std::find_if(variables.begin(), variables.end(), [&name](const Variable &variable) {
        return variable.name == name;
    });

    if (var != variables.end()) {
        return (*var).value;
    }

    return name;
}
