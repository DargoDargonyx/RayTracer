#include <stdio.h>

#include "util/windowManager.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800


int main() {
    printf("Successfully started the executable\n");
    return runWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
}
