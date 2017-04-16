#include "sleep.h"

#if defined _WIN32 || _WIN64

#include <windows.h>

void _sleep(int period) {
	Sleep(period * 1000);
}

#elif defined __APPLE__ || __MACH__ || __linux__ || linux || __linux

#include <unistd.h>

void _sleep(unsigned int period) {
	usleep(period);
}

#endif