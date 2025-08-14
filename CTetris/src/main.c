
// #define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif
#include <time.h>
#else
#include <time.h>
#endif

#include "tetris.h"

TetBlock tet_templates[] = {
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,

    0, 0, 0, 0,
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,

    0, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 1, 0,

    0, 0, 1, 0,
    0, 0, 1, 0,
    0, 0, 1, 0,
    0, 1, 1, 0,

    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};

void clearScreen() {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    SetConsoleCursorPosition(hConsole, coord);
#else
    printf("\033[H\033[J");
#endif
}

void sleepFor(long nanoseconds) {
#ifdef _WIN32
    Sleep((DWORD)(nanoseconds / 1000000L));
#else
    struct timespec ts;
    ts.tv_sec = nanoseconds / 1000000000L;
    ts.tv_nsec = nanoseconds % 1000000000L;
    nanosleep(&ts, NULL);
#endif
}

void printTetGame(TetGame* tetg) {
    TetField* tf = tetg->field;
    TetFigure* t = tetg->figure;
    for (int i = 0; i < tf->height; i++) {
        for (int j = 0; j < tf->width; j++) {
            int sym = BACKROUND_PIXEL;
            if (tf->blocks[i * tf->width + j].b != 0)
                sym = BLOCK_PIXEL;
            else {
                int x = j - t->x;
                int y = i - t->y;
                if (x >= 0 && x < t->size && y >= 0 && y < t->size)
                    if (t->blocks[y * t->size + x].b != 0)
                        sym = BLOCK_PIXEL;
            }
            printf("%c", sym);
        }
    }
    fflush(stdout);
}

int main() {
    const int defaultCP = GetConsoleOutputCP(); // 866
    SetConsoleOutputCP(437);

    struct timespec sp_start, sp_end;

    TetGame* tetg = createTetGame(48, 20, 4, 7, tet_templates);
    TetPlayer player;
    player.action = TET_PLAYER_NOP;
    tetg->player = &player;
    dropNewFigure(tetg);

    const long frame_time = 120000000L; // 120 мс

    while (tetg->playing != TET_GAMEOVER) {
        clock_gettime(CLOCK_MONOTONIC, &sp_start);

        calculateTet(tetg);

        clearScreen();
        printTetGame(tetg);

        clock_gettime(CLOCK_MONOTONIC, &sp_end);

        long diff = (sp_end.tv_sec - sp_start.tv_sec) * 1000000000L +
                    (sp_end.tv_nsec - sp_start.tv_nsec);

        if (diff < frame_time) {
            sleepFor(frame_time - diff);
        }
    }

    printf("Your score: %d\n", tetg->score);
    freeTetGame(tetg);

    // for (int i = 0; i < 255; i++) {
    //     printf("%d: %c\n", i, i);
    // }

    SetConsoleOutputCP(defaultCP);

    return 0;
}