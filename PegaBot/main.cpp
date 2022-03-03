#include <windows.h>
#include <thread>
#include <chrono>
#include <iostream>
#include "offsets.h"

#define printfln(format, ...) printf(format "\n", __VA_ARGS__)


using namespace std;

void click() {
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &Input, sizeof(INPUT));
	ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &Input, sizeof(INPUT));
	ZeroMemory(&Input, sizeof(INPUT));
	return;
}

int get_Bitmap(int x, int y, HDC& hdcMemory, int width, int height) {
	HDC hdcSource = GetDC(NULL); // the entire screen
	hdcMemory = CreateCompatibleDC(hdcSource);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdcSource, width, height);
	HBITMAP hBitmapOld = (HBITMAP)SelectObject(hdcMemory, hBitmap);

	if (!BitBlt(hdcMemory, 0, 0, width, height, hdcSource, x, y, CAPTUREBLT | SRCCOPY)) {
		cout << "BitBlt failed!" << endl;
	}

	//clean up
	DeleteObject(hBitmapOld);
	DeleteObject(hBitmap);
	ReleaseDC(NULL, hdcSource);

	return 0;
}


bool isValidEnergy(int en) {
	if (en > 20 || en < 0) {
		return false;
	}
	return true;
}

void scan_final(int targetX, int targetY, int targetColor, const char* buttonName) {
	Sleep(50);
	chrono::steady_clock sc;
	auto start = sc.now();
	while (true) {
		Sleep(400);
		printfln("Scanning for %s Button...", buttonName);
		HDC hdcMemory = NULL;
		COLORREF aPixel = NULL;
		get_Bitmap(targetX, targetY, hdcMemory, SCAN_H, SCAN_W);

		int ctry = 0;
		int ctrx = 0;
		bool found = false;
		if (hdcMemory == NULL) {
			printf("Critical Error, please restart the bot!\n");
			continue;
		}

		for (int y = 1; ctry <= SCAN_H; y++) {
			for (int x = 1;ctrx <= SCAN_W; x++) {
				if (hdcMemory != 0) {
					aPixel = GetPixel(hdcMemory, x, y);
					//printfln("aPixel %d", aPixel);
					if (aPixel == 0)
						continue;
					if (aPixel == targetColor) {
						found = true;
						printfln("Found %s Button! at:", buttonName);
						cout << "X: " << x << " Y: " << y << " Color: " << aPixel << endl;
						SetCursorPos(targetX + x, targetY + y);
						click();
						break;
					}
				}
				ctrx++;
			}
			ctrx = 0;
			ctry++;

			if (found == true) {
				break;
			}
		}

		if (found == true) {
			break;
		}

		if (std::chrono::steady_clock::now() - start > std::chrono::seconds(5)) {
			printfln("Failed to find any buttons, restart the bot and process!");
			break;
		}
	}
}


void scan(int targetX, int targetY, int targetColor, const char* buttonName) {
	Sleep(50);
	while (true) {
		Sleep(400);
		printfln("Scanning for %s Button...", buttonName);
		HDC hdcMemory = NULL;
		COLORREF aPixel = NULL;
		get_Bitmap(targetX, targetY, hdcMemory, SCAN_H, SCAN_W);

		int ctry = 0;
		int ctrx = 0;
		bool found = false;
		if (hdcMemory == NULL) {
			printf("Critical Error, please restart the bot!\n");
			continue;
		}

		for (int y = 1; ctry <= SCAN_H; y++) {
			for (int x = 1;ctrx <= SCAN_W; x++) {
				if (hdcMemory != 0) {
					aPixel = GetPixel(hdcMemory, x, y);
					//printfln("aPixel %d", aPixel);
					if (aPixel == 0)
						continue;
					if (aPixel == targetColor) {
						found = true;
						printfln("Found %s Button! at:", buttonName);
						cout << "X: " << x << " Y: " << y << " Color: " << aPixel << endl;
						SetCursorPos(targetX + x, targetY + y);
						click();
						break;
					}
				}
				ctrx++;
			}
			ctrx = 0;
			ctry++;

			if (found == true) {
				break;
			}
		}

		if (found == true) {
			break;
		}
	}
}


void scan_start() {
	scan(START_X, START_Y, START_COLOR, "Start");
	/*
	while (true) {
		Sleep(500);
		printfln("Scanning for Start Button...");
		HDC hdcMemory = NULL;
		COLORREF aPixel = NULL;
		get_Bitmap(START_X, START_Y, hdcMemory, SCAN_H, SCAN_W);
		int ctry = 0;
		int ctrx = 0;
		bool found = false;

		if (hdcMemory == NULL) {
			printf("Critical Error, please restart the bot!\n");
			continue;
		}

		for (int y = 1; ctry <= SCAN_H; y++) {
			for (int x = 1;ctrx <= SCAN_W; x++) { 
				if (hdcMemory != 0) {
					aPixel = GetPixel(hdcMemory, x, y);	
					printfln("aPixel %d", aPixel);
					if (aPixel == 0)
						continue;
					if (aPixel == 13314739) {
						found = true;
						printfln("Found Start Button! at:");
						cout << "X: " << x << " Y: " << y << " Color: " << aPixel << endl;
						SetCursorPos(START_X + x, START_Y + y);	
						click();
						break;
					}
				}
				ctrx++;
			}
			ctrx = 0;
			ctry++;

			if (found == true) {
				break;
			}
		}
		if (found == true) {
			break;
		}
	}
	*/
}

void scan_nextWrapper(int targetX, int targetY, int targetColor, const char* buttonName, bool* founds) {
	Sleep(50);
	chrono::steady_clock sc;
	auto start = sc.now();

	while (true) {
		Sleep(400);
		printfln("Scanning for %s Button...", buttonName);
		HDC hdcMemory = NULL;
		COLORREF aPixel = NULL;
		get_Bitmap(targetX, targetY, hdcMemory, SCAN_H, SCAN_W);

		int ctry = 0;
		int ctrx = 0;
		bool found = false;
		if (hdcMemory == NULL) {
			printf("Critical Error, please restart the bot!\n");
			continue;
		}

		for (int y = 1; ctry <= SCAN_H; y++) {
			for (int x = 1;ctrx <= SCAN_W; x++) {
				if (hdcMemory != 0) {
					aPixel = GetPixel(hdcMemory, x, y);
					//printfln("aPixel %d", aPixel);
					if (aPixel == 0)
						continue;
					if (aPixel == targetColor) {
						found = true;
						printfln("Found %s Button! at:", buttonName);
						cout << "X: " << x << " Y: " << y << " Color: " << aPixel << endl;
						SetCursorPos(targetX + x, targetY + y);
						click();
						break;
					}
				}
				ctrx++;
			}
			ctrx = 0;
			ctry++;

			if (found == true) {
				break;
			}
		}

		if (found == true) {
			*founds = true;
			break;
		}

		if (std::chrono::steady_clock::now() - start > std::chrono::seconds(7)) {
			break;
			//scan_final(AMATCH_X, AMATCH_Y, AMATCH_COLOR, "Find Another Match");
		}
	}
}



void scan_sign() {
	scan(SIGN_X, SIGN_Y, SIGN_COLOR, "Sign Metamask");
}

void scan_nextmatch() {
	scan(NMATCH_X, NMATCH_Y, NMATCH_COLOR, "Next Match");
}

void scan_amatch() {
	//scan_nextWrapper(AMATCH_X, AMATCH_Y, AMATCH_COLOR, "Find Another Match");
}



int main() {
	int energy = 0;

	while (true) {
		printf("Input your energy to burn: ");
		scanf_s("%d", &energy);

		if (!isValidEnergy(energy))
			continue;

		break;
	}

	bool Afound = false;
	while (energy != 0) {
		Sleep(2000);
		scan_start();
		
		while (true) {
			Sleep(2500);
			scan_sign();
			scan_amatch();
			Sleep(1000);
			scan_nextWrapper(AMATCH_X, AMATCH_Y, AMATCH_COLOR, "Find Another Match", &Afound);
			if (!Afound)
				continue;
			break;
		}

		Sleep(83000);
		scan_nextmatch();
		energy--;
		printfln("Burned energy! energy count: %d", energy);
	}

	while (true) {

	}


	return 0;
}