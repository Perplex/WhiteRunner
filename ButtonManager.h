//
// Created by Ceegan on 2017-12-22.
//

#ifndef WHITERUNNER_BUTTONMANAGER_H
#define WHITERUNNER_BUTTONMANAGER_H

#include "common.h"
#include <windows.h>
#include <opencv2/opencv.hpp>

using namespace cv;

class WRBot;

class ButtonManager {
    WRBot & m_bot;
    double templateMatching(Mat img, Mat templ, bool hover, bool object=false, int button=0, DWORD sleep=0, double maximum=1000000);
    Mat screenToBmp(int x, int y, int w, int h);

public:
    ButtonManager(WRBot & bot);
    void OnStart();
    void OnEnd();
    void Salvage();
    void getQuest();
};


#endif //WHITERUNNER_BUTTONMANAGER_H
