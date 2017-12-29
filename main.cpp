#include "WRBot.h"

int main() {
    Sleep(3000);
    WRBot bot;
    int max;

    //std::cout << "Enter the amount of times the bot should loop: ";
    //std::cin >> max;

    for(int i=0; i < 1; i++){
        bot.update(i);
    }

    return 0;
}

