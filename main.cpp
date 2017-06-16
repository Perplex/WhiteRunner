#include <iostream>
#include <windows.h>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"

using namespace std;
using namespace cv;

void button(WORD key);

void moveMouse(int x, int y, int button, DWORD sleep=0);

Mat screenBitmap(int x, int y, int w, int h);

bool templateMatching(Mat img, Mat templ, bool move, DWORD sleep=0);

int main() {
    /*DWORD processes[1024], cbNeeded, cProcesses;
    EnumProcesses(processes, sizeof(processes), &cbNeeded);
    cProcesses = cbNeeded/sizeof(DWORD);

    for (int x = 0; x < cProcesses; x++){
        if (processes[x] != 0){
            TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

            // Get a handle to the process.

            HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                           PROCESS_VM_READ,
                                           FALSE, processes[x] );

            // Get the process name.

            if (NULL != hProcess )
            {
                HMODULE hMod;

                if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod),
                                         &cbNeeded) )
                {
                    GetModuleBaseName( hProcess, hMod, szProcessName,
                                       sizeof(szProcessName)/sizeof(TCHAR) );
                }
            }

            // Print the process name and identifier.

            cout << szProcessName << " (PID: " << processes[x] << ")" << endl;

            // Release the handle to the process.

            CloseHandle( hProcess );
        }
    }*/

    Sleep(3000);
    int loop = 0;
    Mat img;
    while(loop != 1){
        /*img = screenBitmap(0, 0, 1920, 1080);
        while(templateMatching(img, imread("Assets/Ingame.bmp"), false)){
            Sleep(300);
            img = screenBitmap(0, 0, 1920, 1080);
        }
        moveMouse(200,585, 1);
        if (!templateMatching(img, imread("Assets/Home/Mode.bmp"), false)){
            moveMouse(600,400, 1);
            if (!templateMatching(img, imread("Assets/Home/Multiplayer.bmp"), false)){
                moveMouse(1240, 673, 1);
            }
        }
        else if (!templateMatching(img, imread("Assets/Home/Multiplayer.bmp"), false)){
            moveMouse(1240, 673, 1);
        }
        moveMouse(1000, 900, 1);

        img = screenBitmap(0, 0, 1920, 1080);
        Mat templ = imread("Assets/Ingame.bmp");
        while (!templateMatching(img, templ, false)){
            Sleep(500);
            img = screenBitmap(0, 0, 1920, 1080);
        }

        if (!templateMatching(img, imread("Assets/Templar.bmp"), false)){
            cout << "Lazy" << endl;
        }

        // Salvage
        //Mat img = screenBitmap(0, 0, 1920, 1080);
        if (loop%2 == 0){
            templateMatching(img, imread("Assets/Salvage/Salvage.bmp"), true);
            img = screenBitmap(0, 0, 1920, 1080);
            //imwrite("Assets/Salvage/InSalvage.bmp", screenBitmap(0, 0, 520, 150));
            while(!templateMatching(img, imread("Assets/Salvage/InSalvage.bmp"), false)){
                Sleep(300);
                img = screenBitmap(0, 0, 1920, 560);
            }
            templateMatching(img, imread("Assets/Salvage/SalvageTab.bmp"), true, 700);
            img = screenBitmap(0, 0, 1000, 440);
            templateMatching(img, imread("Assets/Salvage/SalvageWhite.bmp"), true, 700);
            img = screenBitmap(0, 0, 1000, 440);
            if(templateMatching(img, imread("Assets/Salvage/SalvageAccept.bmp"), false)){
                templateMatching(img, imread("Assets/Salvage/SalvageAccept.bmp"), true, 700);
            }
            templateMatching(img, imread("Assets/Salvage/SalvageBlue.bmp"), true, 700);
            img = screenBitmap(0, 0, 1000, 440);
            if(templateMatching(img, imread("Assets/Salvage/SalvageAccept.bmp"), false)){
                templateMatching(img, imread("Assets/Salvage/SalvageAccept.bmp"), true, 700);
            }
            templateMatching(img, imread("Assets/Salvage/SalvageYellow.bmp"), true, 700);
            img = screenBitmap(0, 0, 1000, 440);
            if(templateMatching(img, imread("Assets/Salvage/SalvageAccept.bmp"), false)){
                templateMatching(img, imread("Assets/Salvage/SalvageAccept.bmp"), true, 700);
            }
            button(VK_ESCAPE);
            while(templateMatching(img, imread("Assets/Salvage/InSalvage.bmp"), false)){
                Sleep(300);
                img = screenBitmap(0, 0, 1920, 560);
            }
        }*/

        // Getting quest
        moveMouse(140, 60, 2);
        moveMouse(200, 140, 0);
        img = screenBitmap(0, 0, 1920, 1080);
        while(!templateMatching(img, imread("Assets/Quest.bmp"), false)){
            Sleep(100);
            img = screenBitmap(0, 0, 1920, 1080);
        }
        moveMouse(500, 140, 1, 200);
        button(VK_ESCAPE);
        moveMouse(860, 666, 0, 1000);
        moveMouse(860, 666, 1, 2000);
        img = screenBitmap(0, 0, 1920, 1080);
        while(templateMatching(img, screenBitmap(0, 0, 1920, 1080), false))
            Sleep(500);

        // First room
        moveMouse(0, 1000, 1, 500);
        int x =0;
        while(!templateMatching(screenBitmap(1577, 45, 320, 320), screenBitmap(1557, 65, 280, 280), false) && x != 3){
            Sleep(4000);
            x++;
        }

        moveMouse(115, 110, 0, 4000);
        /*moveMouse(860, 340, 0, 500);
        moveMouse(860, 340, 1, 700);
        button(VK_ESCAPE);
        moveMouse(1000, 0, 0, 1000);
        moveMouse(1000, 0, 1, 4000);
        moveMouse(1500, 70, 1, 4000);
        moveMouse(1920, 700, 1, 4000);
        moveMouse(1080, 400, 0, 1000);
        moveMouse(1080, 400, 1, 1000);
        moveMouse(1080, 400, 1);
        img = screenBitmap(0, 0, 1920, 1080);
        while(templateMatching(img, screenBitmap(0, 0, 1920, 1080), false))
            Sleep(500);

        // Second room
        moveMouse(800, 300, 0, 1000);
        moveMouse(800, 300, 1, 2000);
        moveMouse(850, 480, 0, 1000);
        Point offset;
        if(templateMatching(screenBitmap(780, 440, 155, 20), imread("Assets/Drop.bmp"), false)){
            moveMouse(840, 480, 1);
        }
        else{
            moveMouse(780, 420, 0, 300);
            moveMouse(780, 420, 1);
            offset.y = 100;
            offset.x = 80;
            cout << "hello" << endl;
        }
        moveMouse(1350 + offset.x, 650 + offset.y, 0, 500);
        moveMouse(1350 + offset.x, 650 + offset.y, 1, 1500);
        moveMouse(1000, 720, 0, 500);
        if(!templateMatching(screenBitmap(950, 600, 155, 100), imread("Assets/Drop.bmp"), false)){
            moveMouse(1000, 580, 0, 500);
            moveMouse(1000, 580, 1);
        }
        else{
            moveMouse(1000, 720, 1);
            cout << "hello" << endl;
        }
        moveMouse(0, 575, 0, 1000);
        moveMouse(0, 575, 1, 2500);
        moveMouse(880, 575, 0, 500);
        moveMouse(880, 575, 1, 500);

        // Quiting session
        button(VK_ESCAPE);
        Sleep(500);
        img = screenBitmap(0, 0, 1920, 1080);
        //imwrite("Assets/EndGame.bmp", screenBitmap(90, 450, 280, 70));
        templateMatching(img, imread("Assets/EndGame.bmp"), true);
        Sleep(12000);*/
        loop++;
    }

    cout << "Hello, World!";
    return 0;
}

void button(WORD key){
    INPUT input;

    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;

    SendInput(1, &input, sizeof(INPUT));

    input.ki.dwFlags = KEYEVENTF_KEYUP;
    Sleep(100);
    SendInput(1, &input, sizeof(INPUT));
    return;
}

void moveMouse(int x, int y, int button, DWORD sleep){
    INPUT input;

    input.type = INPUT_MOUSE;
    input.mi.mouseData = 0;
    input.mi.time = 0;
    input.mi.dx = x * (65536 / GetSystemMetrics(SM_CXSCREEN));
    input.mi.dy = y * (65536 / GetSystemMetrics(SM_CYSCREEN));
    input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
    if (button == 1){
        input.mi.dwFlags = input.mi.dwFlags | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
    }
    else if (button == 2){
        input.mi.dwFlags = input.mi.dwFlags | MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP;
    }

    SendInput(1, &input, sizeof(input));
    Sleep(sleep);
    return;
}

Mat screenBitmap(int x, int y, int w, int h){
    Mat src;
    BITMAPINFOHEADER  bi;

    HDC hdcScreen = GetDC(NULL);
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

    HBITMAP hBitmapOld = (HBITMAP)SelectObject(hdcMemory, hBitmap);

    BitBlt(hdcMemory, 0, 0, w, h, hdcScreen, x, y, SRCCOPY);
    hBitmap = (HBITMAP)SelectObject(hdcMemory, hBitmapOld);

    // Converts hbitmap to src
    GetDIBits(hdcMemory, hBitmap, 0,(UINT) h, src.data,(BITMAPINFO *)&bi, DIB_RGB_COLORS);

    DeleteDC(hdcScreen);
    DeleteDC(hdcMemory);
    DeleteObject(hBitmap);

    return src;
}

bool templateMatching(Mat img, Mat templ, bool move, DWORD sleep){
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
    //rectangle(imgCopy, matchLoc, Point(matchLoc.x + templ.cols , matchLoc.y + templ.rows), Scalar::all(0), 4, 8, 0);
    imwrite("Assets/finding.bmp", imgCopy);

    cout << minVal << endl;

    if (move && minVal < 2090000){
        cout << matchLoc.x << endl << matchLoc.y << endl;
        moveMouse(matchLoc.x + 30, matchLoc.y + 30, 0, 500);
        moveMouse(matchLoc.x + 30, matchLoc.y + 30, 1, sleep);
    }

    return minVal < 1000000;
}