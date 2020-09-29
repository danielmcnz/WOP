#pragma once

//#include <Windows.h>
#include <stdio.h>
#include <cstdint>
#include <thread>

#ifdef _WIN32

#include <Windows.h>
#include <winioctl.h>
#include <shellscalingapi.h>
#include <intrin.h>

#pragma comment(lib, "SHCore")

#elif __linux__

#include <cpuid.h>

#else

printf("Unsupported operating system\n");

#endif

#define wszDrive L"\\\\.\\PhysicalDrive1"

struct DiskSpace
{
	int64_t avaliableBytes;
	int64_t totalBytes;
	int64_t freeBytes;
};

struct DiskGeometryEx
{
	DISK_GEOMETRY pdg;
	unsigned long long diskSize;
};

struct ScreenInfo
{
	int x;
	int y;
	int xRaw;
	int yRaw;
	int scalePercentageX;
	int scalePercentageY;
};

class HardwareInfo
{
public:
	ScreenInfo& GetDesktopResolution();
	DiskGeometryEx& GetDriveGeometryInfo();
	DiskSpace& GetDriveSize(const wchar_t* drive = 0);
	int* GetCpuRegisters();
	int GetCPULogicalProcessorCount();
	int CPUClock();
private:
	BOOL GetDriveGeometry(LPWSTR path, DISK_GEOMETRY* pdg);
	int GetScalePercentage(int dpi);
private:
	int registers[4];
};

