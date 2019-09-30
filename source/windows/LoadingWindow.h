//
// Created by cpasjuste on 30/09/2019.
//

#ifndef RETROMENU_LOADINGWINDOW_H
#define RETROMENU_LOADINGWINDOW_H

#include <tinyxml2.h>
#include <cross2d/c2d.h>

class LoadingWindow : public c2d::Rectangle {

public:

    explicit LoadingWindow(tinyxml2::XMLNode *root);
};

#endif //RETROMENU_LOADINGWINDOW_H
