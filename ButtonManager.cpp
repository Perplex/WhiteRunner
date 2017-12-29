//
// Created by Ceegan on 2017-12-22.
//

#include "ButtonManager.h"
#include "WRBot.h"

ButtonManager::ButtonManager(WRBot &bot): m_bot(bot) {}

void ButtonManager::OnStart() {
    Mat img, templ;

    img = screenToBmp(0, 0, 1920, 1080);
    templ = imread("Assets/Ingame.bmp");
    std::cout << "Checking if in game:\n";
    while(templateMatching(screenToBmp(0, 0, 1920, 1080), templ, false, false, 0, 300) < 1000000);

    std::cout << "=======================\n\nChecking Mode:\n";
    m_bot.m_paths.moveMouse(200,585, 1);
    if (templateMatching(img, imread("Assets/Home/Mode.bmp"), false) > 1000000){
        m_bot.m_paths.moveMouse(600,400, 1);
        if (templateMatching(img, imread("Assets/Home/Multiplayer.bmp"), false) > 1000000){
            m_bot.m_paths.moveMouse(1240, 673, 1);
        }
    }
    else if (templateMatching(img, imread("Assets/Home/Multiplayer.bmp"), false) > 1000000){
        m_bot.m_paths.moveMouse(1240, 673, 1);
    }
    m_bot.m_paths.moveMouse(1000, 900, 1);

    std::cout << "=======================\n\nChecking if in game:\n";
    while(templateMatching(screenToBmp(0, 0, 1920, 1080), templ, false, false, 0, 300) > 1000000);
}

void ButtonManager::OnEnd() {
    Sleep(1000);
    int loop = 0;
    m_bot.m_paths.keyboard(VK_ESCAPE);
    Mat templ = imread("Assets/EndGame.bmp");
    std::cout << "=======================\n\nLeaving Game:\n";

    while(templateMatching(screenToBmp(0, 0, 1920, 1080), templ, false, true, 1) > 1000000 && loop < 1000){
        loop++;
        if (loop % 100){
            m_bot.m_paths.keyboard(VK_ESCAPE);
        }
    };
    assert(loop != 1000);

}

void ButtonManager::Salvage() {
    Mat img, templ;
    int x=0, y=0;

    std::cout << "=======================\n\n\tSALVAGE\n";

    for (auto salvage: MemoryTools::getACDs(m_bot.proc)){
        if (salvage->Name.find("Blacksmith_ForgeWeapon") != std::string::npos){
            std::tie(x, y) = m_bot.m_paths.screenPos(salvage->Position);
            break;
        }
    }
    m_bot.m_paths.moveMouse(x, y, 0, 2000, true);

    img = screenToBmp(0, 0, 1920, 1080);
    std::cout << "\nChecking if in salvage:\n";
    templ = imread("Assets/Salvage/InSalvage.bmp");
    while(templateMatching(img, templ, false, false, 0, 300) > 1000000)
        img = screenToBmp(0, 0, 1920, 560);

    std::cout << "\nFinding salvage tab:\n";
    templ = imread("Assets/Salvage/SalvageTab.bmp");
    while(templateMatching(img, templ, false, true, 1, 300) > 1000000)
        img = screenToBmp(0, 0, 1920, 560);

    std::cout << "\nChecking white salvage:\n";
    img = screenToBmp(0, 0, 1000, 440);
    if(templateMatching(img, imread("Assets/Salvage/SalvageWhite.bmp"), false, true, 1, 1000) < 1000000){
        img = screenToBmp(0, 0, 1000, 440);
        templateMatching(img, imread("Assets/Salvage/SalvageAccept.bmp"), false, true, 1, 1000);
    }

    std::cout << "\nChecking blue salvage:\n";
    if(templateMatching(img, imread("Assets/Salvage/SalvageBlue.bmp"), false, true, 1, 1000) < 1000000){
        img = screenToBmp(0, 0, 1000, 440);
        templateMatching(img, imread("Assets/Salvage/SalvageAccept.bmp"), false, true, 1, 1000);
    }

    std::cout << "\nChecking yellow salvage:\n";
    if(templateMatching(img, imread("Assets/Salvage/SalvageYellow.bmp"), false, true, 1, 1000) < 1000000){
        img = screenToBmp(0, 0, 1000, 440);
        templateMatching(img, imread("Assets/Salvage/SalvageAccept.bmp"), false, true, 1, 1000);
    }

    m_bot.m_paths.keyboard(VK_ESCAPE);

    std::cout << "\nChecking if in salvage:\n";
    templ = imread("Assets/Salvage/InSalvage.bmp");
    while(templateMatching(img, templ, false) < 1000000){
        Sleep(300);
        img = screenToBmp(0, 0, 1920, 560);
    }
}

void ButtonManager::getQuest(){
    std::cout << "=======================\n\nFinding templar portrait:\n";
    Mat tmpl = imread("Assets/Templar.bmp");

    while(templateMatching(screenToBmp(0, 0, 1920, 1080), tmpl, false, true, 2) > 1100000)
        Sleep(300);

    std::cout << "Finding talk option:\n";
    tmpl = imread("Assets/Talk.bmp");
    while(templateMatching(screenToBmp(0, 0, 1920, 1080), tmpl, true) > 2000000)
        Sleep(300);

    std::cout << "Finding quest:\n";
    tmpl = imread("Assets/Quest.bmp");
    while(templateMatching(screenToBmp(0, 0, 1920, 1080), tmpl, false, true, 1) > 1000000)
        Sleep(300);

    Sleep(300);
    m_bot.m_paths.keyboard(VK_ESCAPE);

    std::cout << "Finding Accept button:\n";
    tmpl = imread("Assets/Accept.bmp");
    while(templateMatching(screenToBmp(0, 0, 1920, 1080), tmpl, false, true, 1) > 1000000)
        Sleep(300);

    tmpl = screenToBmp(0, 0, 1920, 1080);
    while(templateMatching(screenToBmp(0, 0, 1920, 1080), tmpl, false) < 1000000){
        Sleep(300);
    }
}

double ButtonManager::templateMatching(Mat img, Mat templ, bool hover, bool click, int button, DWORD sleep, double maximum) {
    cvtColor(templ, templ, CV_BGR2BGRA);
    Mat result;
    int result_cols = img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;

    int method = TM_SQDIFF;
    double minVal, maxVal;
    Point matchLoc, minLoc, maxLoc;

    result.create(result_rows, result_cols, CV_8UC4);

    matchTemplate(img, templ, result, method);

    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    matchLoc = minLoc;
    //matchLoc = maxLoc;

    Mat imgCopy;
    img.copyTo(imgCopy);

    std::cout << minVal << std::endl;

    if ((minVal < maximum || maximum == -1)){
        if (click){
            std::cout << "x: " << matchLoc.x << " y: " << matchLoc.y << std::endl;
            m_bot.m_paths.moveMouse(matchLoc.x + templ.cols/2, matchLoc.y + templ.rows/2, button, sleep, false);
        }
        else if (hover){
            std::cout << "x: " << matchLoc.x << " y: " << matchLoc.y << std::endl;
            m_bot.m_paths.moveMouse(matchLoc.x + templ.cols/2, matchLoc.y + templ.rows/2, 0, sleep, false);
        }
    }


    return minVal;
}

Mat ButtonManager::screenToBmp(int x, int y, int w, int h) {
    Mat src;
    BITMAPINFOHEADER  bi;

    HDC hdcScreen = GetDC(nullptr);
    HDC hdcMemory = CreateCompatibleDC(hdcScreen);
    src.create(h, w, CV_8UC4);

    HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, w, h);
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = w;
    bi.biHeight = -h;  //Postive height means upside down
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    auto hBitmapOld = (HBITMAP)SelectObject(hdcMemory, hBitmap);

    BitBlt(hdcMemory, 0, 0, w, h, hdcScreen, x, y, SRCCOPY);
    hBitmap = (HBITMAP)SelectObject(hdcMemory, hBitmapOld);

    // Converts hbitmap to src
    GetDIBits(hdcMemory, hBitmap, 0,(UINT) h, src.data,(BITMAPINFO *)&bi, DIB_RGB_COLORS);

    DeleteDC(hdcScreen);
    DeleteDC(hdcMemory);
    DeleteObject(hBitmap);

    return src;
}