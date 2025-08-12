#include "game.h"

#ifdef _WIN32
#include <windows.h>
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif
#include <time.h>
#else
#include <time.h>
#endif

void sleep_for(long nanoseconds) {
#ifdef _WIN32
    Sleep((DWORD)(nanoseconds / 1000000L)); // мс
#else
    struct timespec ts;
    ts.tv_sec = nanoseconds / 1000000000L;
    ts.tv_nsec = nanoseconds % 1000000000L;
    nanosleep(&ts, NULL);
#endif
}

long long get_time_ns() {
#ifdef _WIN32
	static LARGE_INTEGER freq;
	static int init = 0;
	if (!init) {
		QueryPerformanceFrequency(&freq);
		init = 1;
	}
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);
	return (long long)(counter.QuadPart * 1000000000LL / freq.QuadPart);
#else
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
#endif
}

// === Main Function ===
int main() {
    const long FRAME_TIME_NS = 120000000L; // 120 ms

    Game* game = create_game();

    while (game->is_running) {
        long long start_time = get_time_ns();

        if (game->is_game_over) {
            game_over_dialog(game);
            continue;
        }

        update(game);

        long long elapsed = get_time_ns() - start_time;

        if (elapsed < FRAME_TIME_NS)
            sleep_for(FRAME_TIME_NS - elapsed);
    }

    end_game(game);
    return 0;
}