#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

void button(WORD key);

void moveMouse(int x, int y, int button, DWORD sleep=0, bool move=false);

void leaveGame();

double templateMatching(Mat img, Mat templ, bool object, DWORD sleep=0, double maximum=1000000);

KeyPoint featureMatching(Mat templ);

Mat screenBitmap(int x, int y, int w, int h);

class Vector3{
public:
    float X;
    float Y;
    float Z;
};

class DiabloProc{
public:
    HANDLE proc = getHandle();
    long ObjectManger = 0x2146A80;
    long ACDManger = 0x940;
    long ActorCommonData = 0x0;
    long Items = 0x120;
    long FirstACD = 0x0;
    long ACDLocation = 0x114;
    long ActorType = 0x17c;
    long ACDPosition = 0xD0;

    pair<long, long> getACDs(){
        pair<long, long> ACDMangerPtr;
        if (proc != nullptr) {
            long address, name;
            int buff;

            ReadProcessMemory(proc, (LPCVOID) ObjectManger, &buff, 4, nullptr);
            //cout << "ObjectManger: 0x" << hex << buff << endl;

            // ACDManger
            address = buff + ACDManger;
            ReadProcessMemory(proc, (LPCVOID) address, &buff, 4, nullptr);

            // Pointer to ActorCommonData
            address = buff + ActorCommonData;
            ReadProcessMemory(proc, (LPCVOID) address, &buff, 4, nullptr);
            //cout << "Pointer: 0x" << hex << buff << endl;

            //ActorCommonData
            address = buff;
            /*ReadProcessMemory(proc, (LPCVOID) address, &name, 8, nullptr);
            convertHex(name);
            ReadProcessMemory(proc, (LPCVOID) (address + 0x8), &name, 8, nullptr);
            convertHex(name);
            cout << endl << endl;*/

            address += Items;
            int max;
            //cout << "0x" << hex << address << endl;
            ReadProcessMemory(proc, (LPCVOID) address, &buff, 4, nullptr);
            //cout << "0x" << hex << buff << endl;

            address = (address - Items) + 0x108;
            ReadProcessMemory(proc, (LPCVOID) address, &max, 4, nullptr);
            //cout << "Max: 0x" << hex << max << endl;

            address = buff + FirstACD;
            ReadProcessMemory(proc, (LPCVOID) address, &buff, 4, nullptr);
            //cout << "First: 0x" << hex << buff << endl << endl;
            ACDMangerPtr.first = buff;
            ACDMangerPtr.second = max;
        }
        return  ACDMangerPtr;
    }

    pair<int, int> screenPos(Vector3 position){
        pair<int, int> PixPos;
        Vector3 charPos = getCharPos();

        double xd = position.X - charPos.X;
        double yd = position.Y - charPos.Y;
        double zd = position.Z - charPos.Z;

        printf("xd: %f\nyd: %f\nzd: %f\n\n", xd, yd, zd);

        double w = -0.515 * xd + -0.514 * yd + -0.686 * zd + 97.985;
        double X = (-1.182 * xd + 1.283 * yd + 0 * zd + 7.045e-3) / w;
        double Y = (-1.54 * xd + -1.539 * yd + 2.307 * zd + 6.161) / w;

        double width = 1920;
        double height = 1080;
        double aspect = 16.0f/9.0f;

        double aspectChange = (width/height) / aspect;

        X /= aspectChange;

        PixPos.first = (int)((X + 1) / 2 * width);
        PixPos.second = (int)((1 - Y) / 2 * height);

        return PixPos;
    }

    Vector3 findLoot() {
        Vector3 position;
        if (proc != nullptr){
            pair<long, long> ACDManger = getACDs();
            long address = ACDManger.first;
            long name;
            bool found = false;
            //Looping through ACDs

            for (int x = 0; x <= ACDManger.second && !found; address += 0x2f0, x++) {
                int ID;
                int actorType;
                int location;

                ReadProcessMemory(proc, (LPCVOID) (address), &ID, 1, nullptr);
                ReadProcessMemory(proc, (LPCVOID) (address + ACDLocation), &location, 1, nullptr);
                ReadProcessMemory(proc, (LPCVOID) (address + ActorType), &actorType, 4, nullptr);

                if (ID != 0xff && location == 0xff && actorType == 8) {
                    ReadProcessMemory(proc, (LPCVOID) (address + 0x4), &name, 8, nullptr);
                    //cout << "Name: ";
                    //convertHex(name);
                    //cout << endl;
                    ReadProcessMemory(proc, (LPCVOID) (address + ACDPosition), &position.X, 4, nullptr);
                    ReadProcessMemory(proc, (LPCVOID) (address + ACDPosition + 0x4), &position.Y, 4, nullptr);
                    ReadProcessMemory(proc, (LPCVOID) (address + ACDPosition + 0x8), &position.Z, 4, nullptr);
                    //printf("PositionX: %f\nPositionY: %f\nPositionZ: %f\n\n", position.X, position.Y, position.Z);
                    if (position.X != 0 && position.Y != 0 && position.Z != 0)
                        found = true;
                }
            }
        }

        return position;
    }

    Vector3 getCharPos(){
        Vector3 charPos;
        if (proc != nullptr) {
            pair<long, long> ACDManger = getACDs();
            long address = ACDManger.first, name;
            bool found = false;

            for(int x=0; x <= ACDManger.second && !found; address+=0x2f0, x++){
                unsigned int ID, actorType;

                ReadProcessMemory(proc, (LPCVOID)(address), &ID, 1, nullptr);
                ReadProcessMemory(proc, (LPCVOID)(address + ActorType), &actorType, 4, nullptr);
                if(ID != 0xff && actorType == 7){

                    ReadProcessMemory(proc, (LPCVOID)(address + 0x4), &name, 8, nullptr);
                    //cout << "Name: ";
                    //convertHex(name);
                    //cout << endl;
                    ReadProcessMemory(proc, (LPCVOID)(address + ACDPosition), &charPos.X, 4, nullptr);
                    ReadProcessMemory(proc, (LPCVOID)(address + ACDPosition + 0x4), &charPos.Y, 4, nullptr);
                    ReadProcessMemory(proc, (LPCVOID)(address + ACDPosition + 0x8), &charPos.Z, 4, nullptr);
                    found = true;
                    //printf("Address: %lX\nPositionX: %f\nPositionY: %f\nPositionZ: %f\n\n", address, charPos.X, charPos.Y, charPos.Z);
                }
            }
        }
        return charPos;
    }

    void convertHex(long buff) {
        while ((buff & 0xff) != 0x00) {
            auto temp = (char) (buff & 0xff);
            cout << temp;
            buff >>= 8;
        }
        return;
    }

private:
    HANDLE getHandle(){
        PROCESSENTRY32 entry;
        HANDLE hProcess = nullptr;
        entry.dwSize = sizeof(PROCESSENTRY32);

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (Process32First(snapshot, &entry) == TRUE)
            while (Process32Next(snapshot, &entry) == TRUE)
                if (strcmp(entry.szExeFile, "Diablo III.exe") == 0)
                    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
        CloseHandle(snapshot);
        return hProcess;
    }
};

int main() {
    Sleep(3000);
    int loop = 0;
    Mat img, templ;
    DiabloProc D3;

    if (D3.proc == nullptr){
        CloseHandle(D3.proc);
        return 0;
    }

    while(loop != 1){
        KeyPoint loc;

        img = screenBitmap(0, 0, 1920, 1080);
        templ = imread("Assets/Ingame.bmp");
        cout << "Checking if in game:\n";
        while(templateMatching(screenBitmap(0, 0, 1920, 1080), templ, false, 300) < 1000000);

        cout << "=======================\n\nChecking Mode:\n";
        moveMouse(200,585, 1);
        if (templateMatching(img, imread("Assets/Home/Mode.bmp"), false) > 1000000){
            moveMouse(600,400, 1);
            if (templateMatching(img, imread("Assets/Home/Multiplayer.bmp"), false) > 1000000){
                moveMouse(1240, 673, 1);
            }
        }
        else if (templateMatching(img, imread("Assets/Home/Multiplayer.bmp"), false) > 1000000){
            moveMouse(1240, 673, 1);
        }
        moveMouse(1000, 900, 1);

        cout << "=======================\n\nChecking if in game:\n";
        templ = imread("Assets/Ingame.bmp");
        while (templateMatching(screenBitmap(0, 0, 1920, 1080), templ, false, 500) > 1000000);

        cout << "=======================\n\nChecking for templar:\n";
        if (templateMatching(img, imread("Assets/Templar.bmp"), false) > 1000000){
            cout << "Lazy" << endl;
        }

        // Salvage
        if (loop%3 == 0){
            cout << "=======================\n\n\tSALVAGE\n";
            cout << "\nFinding salvage:\n";
            loc = featureMatching(imread("Assets/Salvage/Salvage.bmp"));
            moveMouse((int) loc.pt.x, (int) loc.pt.y, 0, 2000, true);

            img = screenBitmap(0, 0, 1920, 1080);
            cout << "\nChecking if in salvage:\n";
            templ = imread("Assets/Salvage/InSalvage.bmp");
            while(templateMatching(img, templ, false, 300) > 1000000)
                img = screenBitmap(0, 0, 1920, 560);

            cout << "\nFinding salvage tab:\n";
            templ = imread("Assets/Salvage/SalvageTab.bmp");
            while(templateMatching(img, templ, true, 1000) > 1000000)
                img = screenBitmap(0, 0, 1920, 560);

            cout << "\nChecking white salvage:\n";
            img = screenBitmap(0, 0, 1000, 440);
            if(templateMatching(img, imread("Assets/Salvage/SalvageWhite.bmp"), true, 1000) < 1000000){
                img = screenBitmap(0, 0, 1000, 440);
                templateMatching(img, imread("Assets/Salvage/SalvageAccept.bmp"), true, 1000);
            }

            cout << "\nChecking blue salvage:\n";
            if(templateMatching(img, imread("Assets/Salvage/SalvageBlue.bmp"), true, 1000) < 1000000){
                img = screenBitmap(0, 0, 1000, 440);
                templateMatching(img, imread("Assets/Salvage/SalvageAccept.bmp"), true, 1000);
            }

            cout << "\nChecking yellow salvage:\n";
            if(templateMatching(img, imread("Assets/Salvage/SalvageYellow.bmp"), true, 1000) < 1000000){
                img = screenBitmap(0, 0, 1000, 440);
                templateMatching(img, imread("Assets/Salvage/SalvageAccept.bmp"), true, 1000);
            }

            button(VK_ESCAPE);

            cout << "\nChecking if in salvage:\n";
            templ = imread("Assets/Salvage/InSalvage.bmp");
            while(templateMatching(img, templ, false) < 1000000){
                Sleep(300);
                img = screenBitmap(0, 0, 1920, 560);
            }
        }

        // Getting quest
        cout << "=======================\n\nGetting quest:\n";
        moveMouse(140, 60, 2);
        moveMouse(200, 140, 0);
        while(templateMatching(screenBitmap(0, 0, 1920, 1080), imread("Assets/Quest.bmp"), false, 100) > 1000000);

        moveMouse(500, 140, 1, 200);
        button(VK_ESCAPE);
        moveMouse(860, 666, 0, 500, true);
        img = screenBitmap(0, 0, 1920, 1080);
        cout << "=======================\n\nChecking if in first room:\n";
        while(templateMatching(img, screenBitmap(0, 0, 1920, 1080), false, 500) < 1000000);

        // First room
        Sleep(700);
        moveMouse(0, 1000, 1, 3000);
        moveMouse(115, 110, 1, 4000);
        moveMouse(860, 340, 0, 2000, true);
        button(VK_ESCAPE);
        moveMouse(1000, 0, 0, 4000, true);
        moveMouse(1500, 70, 1, 3000);
        moveMouse(1900, 700, 1, 3000);
        moveMouse(1100, 400, 0, 3000, true);
        moveMouse(1100, 400, 1);
        img = screenBitmap(0, 0, 1920, 1080);
        cout << "=======================\n\nChecking if in second room:\n";
        while(templateMatching(img, screenBitmap(0, 0, 1920, 1080), false, 500) < 1000000);

        // Second room
        cout << "=======================\n\n\tFINDING LOOT\n";
        moveMouse(800, 290, 0, 3000, true);
        pair<LONG, LONG> screenPos = D3.screenPos(D3.findLoot());
        moveMouse(screenPos.first, screenPos.second, 0, 1000, true);

        cout << "=======================\n\n\tFINDING LOOT\n";
        moveMouse(1350, 680, 0, 3000, true);
        screenPos = D3.screenPos(D3.findLoot());
        moveMouse(screenPos.first, screenPos.second, 0, 1000, true);

        cout << "=======================\n\n\tFINDING LOOT\n";
        moveMouse(50, 590, 0, 3000, true);
        screenPos = D3.screenPos(D3.findLoot());
        moveMouse(screenPos.first, screenPos.second, 0, 1000, true);

        cout << "=======================\n\n\tFINDING LOOT\n";
        moveMouse(500, 600, 0, 3000, true);
        screenPos = D3.screenPos(D3.findLoot());
        moveMouse(screenPos.first, screenPos.second, 0, 1000, true);
        moveMouse(750, 870, 1, 3000);

        // Hallway
        moveMouse(240, 710, 0, 4000, true);
        cout << "=======================\n\n\tFINDING LOOT\n";
        screenPos = D3.screenPos(D3.findLoot());
        moveMouse(screenPos.first, screenPos.second, 0, 1000, true);

        cout << "=======================\n\n\tFINDING LOOT\n";
        moveMouse(530, 635, 0, 3000, true);
        screenPos = D3.screenPos(D3.findLoot());
        moveMouse(screenPos.first, screenPos.second, 0, 1000, true);

        moveMouse(700, 700, 0, 3000, true);

        cout << "=======================\n\n\tFINDING LOOT\n";
        moveMouse(850, 400, 0, 2800, true);
        screenPos = D3.screenPos(D3.findLoot());
        moveMouse(screenPos.first, screenPos.second, 0, 1000, true);

        moveMouse(0, 470, 1, 3000);

        cout << "=======================\n\n\tFINDING LOOT\n";
        moveMouse(940, 400, 0, 3000, true);
        screenPos = D3.screenPos(D3.findLoot());
        moveMouse(screenPos.first, screenPos.second, 0, 1000, true);

        moveMouse(600, 400, 0, 2000, true);
        moveMouse(600, 400, 1, 3000);
        moveMouse(970, 0, 1, 2000);
        moveMouse(870, 200, 0, 2000, true);
        moveMouse(600, 200, 1, 5600);

        // Torture and Grand Room
        moveMouse(900, 400, 0, 2000, true);
        button(VK_ESCAPE);
        Sleep(7000);
        moveMouse(1600, 0, 1, 4000);

        cout << "=======================\n\n\tFINDING LOOT\n";
        moveMouse(1100, 80, 0, 4000, true);
        screenPos = D3.screenPos(D3.findLoot());
        moveMouse(screenPos.first, screenPos.second, 0, 1000, true);

        moveMouse(1600, 950, 1, 3000);

        cout << "=======================\n\n\tFINDING LOOT\n";
        moveMouse(1100, 330, 0, 4000, true);
        screenPos = D3.screenPos(D3.findLoot());
        moveMouse(screenPos.first, screenPos.second, 0, 1000, true);

        moveMouse(800, 0, 1, 3000);

        cout << "=======================\n\n\tFINDING LOOT\n";
        moveMouse(850, 380, 0, 3000, true);
        screenPos = D3.screenPos(D3.findLoot());
        moveMouse(screenPos.first, screenPos.second, 0, 1000, true);

        cout << "=======================\n\n\tFINDING LOOT\n";
        moveMouse(1170, 450, 0, 4000, true);
        screenPos = D3.screenPos(D3.findLoot());
        moveMouse(screenPos.first, screenPos.second, 0, 1000, true);

        cout << "=======================\n\n\tFINDING LOOT\n";
        moveMouse(1750, 900, 0, 4000, true);
        screenPos = D3.screenPos(D3.findLoot());
        moveMouse(screenPos.first, screenPos.second, 0, 1000, true);

        cout << "=======================\n\n\tFINDING LOOT\n";
        moveMouse(1260, 680, 0, 4000, true);
        screenPos = D3.screenPos(D3.findLoot());
        moveMouse(screenPos.first, screenPos.second, 0, 1000, true);

        // Quiting session
        leaveGame();
        loop++;
    }

    CloseHandle(D3.proc);
    return 0;
}

void leaveGame(){
    Sleep(500);
    button(VK_ESCAPE);
    Mat templ = imread("Assets/EndGame.bmp");
    cout << "=======================\n\nLeaving Game:\n";
    while(templateMatching(screenBitmap(0, 0, 1920, 1080), templ, true) > 1000000);
    return;
}

KeyPoint featureMatching(Mat templ){
    vector<DMatch> good_matches;
    vector<KeyPoint> keypoints_1, keypoints_2;
    KeyPoint loc;
    Mat img2;
    double maxDist = 0, minDist = 100;

    while ((int) good_matches.size() < 6){
        Ptr<SURF> detector = SURF::create();
        detector->setHessianThreshold(400);

        keypoints_1.clear();
        keypoints_2.clear();
        good_matches.clear();
        Mat descriptors_1, descriptors_2;

        img2 = screenBitmap(0, 0, 1920, 1080);
        cvtColor(img2, img2, CV_BGRA2BGR);

        detector->detectAndCompute(templ, Mat(), keypoints_1, descriptors_1);
        detector->detectAndCompute(img2, Mat(), keypoints_2, descriptors_2);

        FlannBasedMatcher matcher;
        vector<DMatch> matches;
        matcher.match(descriptors_1, descriptors_2, matches);

        maxDist = 0;
        minDist = 100;

        for(int x = 0; x < descriptors_1.rows; x++){
            double dist = matches[x].distance;
            if (dist < minDist)
                minDist = dist;

            if (dist > maxDist)
                maxDist = dist;
        }

        for (int x = 0; x < descriptors_1.rows; x++){
            if(matches[x].distance <= max(2.2*minDist, 0.02))
                good_matches.push_back(matches[x]);
        }
    }

    Mat img_matches;
    drawMatches(templ, keypoints_1, img2, keypoints_2, good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    vector<float> locX, locY;
    for(int x = 0; x < (int)good_matches.size(); x++){
        printf("Good Match [%d] x: %f y: %f\n", x, keypoints_2[good_matches[x].trainIdx].pt.x,
               keypoints_2[good_matches[x].trainIdx].pt.y);
        locX.push_back(keypoints_2[good_matches[x].trainIdx].pt.x);
        locY.push_back(keypoints_2[good_matches[x].trainIdx].pt.y);
    }

    // Calculate median
    sort(locX.begin(), locX.end());
    sort(locY.begin(), locY.end());

    if (locX.size() % 2 == 0)
        loc.pt.x = (locX[locX.size()/2] + locX[locX.size()/2 + 1])/2;
    else
        loc.pt.x = locX[ceil(locX.size()/2)];

    if (locY.size() % 2 == 0)
        loc.pt.y = (locY[locY.size()/2] + locY[locY.size()/2 + 1])/2;
    else
        loc.pt.y = locY[int (locY.size()/2)];


    imwrite("Assets/test/featureMatching.jpg", img_matches);
    cout << "Found at: " << loc.pt.x << " " << loc.pt.y << endl;

    return loc;
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

void moveMouse(int x, int y, int button, DWORD sleep, bool move){
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
    if (move){
        Sleep(600);
        input.mi.dwFlags = input.mi.dwFlags | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
        SendInput(1, &input, sizeof(input));
        Sleep(sleep);
    }
    else{
        Sleep(sleep);
    }

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

double templateMatching(Mat img, Mat templ, bool object, DWORD sleep, double maximum){
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

    cout << minVal << endl;

    if (object && (minVal < maximum || maximum == -1)){
        cout << "x: " << matchLoc.x << " y: " << matchLoc.y << endl;
        moveMouse(matchLoc.x + templ.cols/2, matchLoc.y + templ.rows/2, 0, sleep, true);
    }

    return minVal;
}