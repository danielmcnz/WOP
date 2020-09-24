#pragma once

#include <Windows.h>
#include <winioctl.h>
#include <stdio.h>
#include <shellscalingapi.h>
#include <cstdint>
#include <intrin.h>
#include <thread>

#pragma comment(lib, "SHCore")

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
	ULONGLONG diskSize;
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
private:
	BOOL GetDriveGeometry(LPWSTR path, DISK_GEOMETRY* pdg);
	int GetScalePercentage(int dpi);
private:
	int registers[4];
};

