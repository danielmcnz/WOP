#include "peripherals.h"

Peripherals::Peripherals()
{
	memset(&in, 0, sizeof(in));
}

Peripherals::~Peripherals()
{}

void Peripherals::SendKey(WORD key, unsigned long milliDelay)
{
	PressKey(key);
	Sleep(milliDelay);
	ReleaseKey();
}

void Peripherals::PressKey(WORD key)
{
	in.type = INPUT_KEYBOARD;
	memset(&in.ki, 0, sizeof(in.ki));
	in.ki.wVk = key;

	SendInput(1, &in, sizeof(INPUT));
}

void Peripherals::ReleaseKey()
{
	in.ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(1, &in, sizeof(INPUT));
}