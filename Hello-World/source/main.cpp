#include <3ds.h>
#include <stdio.h>
#include <cstring>

constexpr const int NUM_COLORS = 6;

void printRainbowText(const char* text, int offset) {
	constexpr const char* COLORS[NUM_COLORS] = {
		"\x1b[31m", "\x1b[33m", "\x1b[32m", "\x1b[36m", "\x1b[34m", "\x1b[35m"
	};

	constexpr const char* DEFAULT_TEXT = "\x1b[0m";

	constexpr const char* PRINT_POSITION = "\x1b[16;20H";

    const size_t STRING_LENGTH = strlen(text);

	printf(PRINT_POSITION);
    for (size_t i = 0; i < STRING_LENGTH; i++) {
        printf("%s%c", COLORS[(i + offset) % NUM_COLORS], text[i]);
    }
    printf(DEFAULT_TEXT);
}

int main(int argc, char **argv)
{
	constexpr const char* EXIT_MESSAGE = "\x1b[16;11HPress START to exit.";

	constexpr const char* PRINT_MESSAGE = "Hello World!";

	constexpr const long DELAY = 66666666L;

	int colorOffset = 0;
	
	gfxInitDefault();

	PrintConsole topScreen, bottomScreen;
    consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &bottomScreen);
	
	consoleSelect(&bottomScreen);
    printf("%s", EXIT_MESSAGE);

	consoleSelect(&topScreen);

	while (aptMainLoop())
	{
		gspWaitForVBlank();
        hidScanInput();

		if (hidKeysDown() & KEY_START) {
			break;
		}
		
		colorOffset = (colorOffset + 1) % NUM_COLORS;
		
        consoleClear();
		
        printRainbowText(PRINT_MESSAGE, colorOffset);
		
		gfxFlushBuffers();
		gfxSwapBuffers();
		
		svcSleepThread(DELAY);
	}
	
	gfxExit();
	return 0;
}