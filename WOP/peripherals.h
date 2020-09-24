#pragma once

#include <Windows.h>

class Peripherals
{
public:
	enum KEY
	{
		A = 0x41,
		B = 0x42,
		C = 0x43,
		D = 0x44,
		E = 0x45,
		F = 0x46,
		G = 0x47,
		H = 0x48,
		I = 0x49,
		J = 0x50,
		K = 0x51,
		L = 0x52,
		M = 0x53,
		N = 0x54,
		O = 0x55,
		P = 0x56,
		Q = 0x57,
		R = 0x58,
		S = 0x59,
		T = 0x60,
		U = 0x61,
		V = 0x62,
		W = 0x63,
		X = 0x64,
		Y = 0x65,
		Z = 0x66
	};
public:
	Peripherals();
	~Peripherals();

	void SendKey(WORD key, unsigned long milliDelay = 0);
	void PressKey(WORD key);
	void ReleaseKey();
private:
	INPUT in;
};

