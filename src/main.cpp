#include <chrono>
#include <thread>
#include <iostream>
using namespace std;

int main() {
    cout << "\033[33mHow many sessions do you need ?\033[0m ";
    int sessions;
    cin >> sessions;

    const int BAR_WIDTH = 60;
    const int WORK_DURATION = 25 * 60;
    const int BREAK_DURATION = 5 * 60;
    const int TOTAL_DURATION = BREAK_DURATION + WORK_DURATION;
    const int BAR_WORK = BAR_WIDTH * WORK_DURATION / TOTAL_DURATION;

    for (int i = 1; i <= sessions; i++) {
        cout << "\033[45m(" << i << "/" << sessions << ")\033[0m [";
        for (int j = 0; j < BAR_WIDTH; j++)
            cout << "\033[31m-\033[0m";
        cout << "]";

        auto start = chrono::steady_clock::now();
        while (true) {
            auto now = chrono::steady_clock::now();
            int elapsed = chrono::duration_cast<chrono::seconds>(now - start).count();
            if (elapsed > TOTAL_DURATION) {
                break;
            }
            float progress = (float)elapsed / TOTAL_DURATION;
            int filled = progress * BAR_WIDTH;

            cout << "\r\033[45m(" << i << "/" << sessions << ")\033[0m [";

            for (int j = 0; j < filled; j++) {
                if (j <= BAR_WORK) cout << "\033[32m=\033[0m";
                else cout << "\033[31m=\033[0m";
            }
            for (int j = filled; j < BAR_WIDTH; j++)
                cout << "\033[36m-\033[0m";

            int remaining = TOTAL_DURATION - elapsed;
            if (elapsed <= WORK_DURATION) remaining = WORK_DURATION - elapsed;
            int minutes = remaining / 60;
            int seconds = remaining % 60;

            cout << "] \033[36m"
                 << (minutes < 10 ? "0" : "") << minutes << ":"
                 << (seconds < 10 ? "0" : "") << seconds
                 << "\033[0m" << flush;

            
                this_thread::sleep_for(chrono::milliseconds(200));
        }
        cout << "\n";
    }

    cout << "\033[33mAll sessions completed!\033[0m\n";

    return 0;
}
