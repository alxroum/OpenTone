#include "player.h"
#include <iostream>

int main() {
    AudioPlayer player;

    if (player.play("76_Inside the Stronghold (Action).wav") == MA_SUCCESS) {
        std::cout << "Press P to pause, R to resume, +/- to change volume, Q to quit\n";

        while (true) {
            char c = std::tolower(std::cin.get());
            if (c == 'p') player.pause();
            else if (c == 'r') player.resume();
            else if (c == '+') player.setVolume(player.getVolume() + 0.1f);
            else if (c == '-') player.setVolume(player.getVolume() - 0.1f);
            else if (c == 'q') break;
        }

        player.stop();
    } else {
        std::cerr << "❌ Failed to play audio.\n";
    }

    return 0;
}
