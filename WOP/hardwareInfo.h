#pragma once

#include <Windows.h>
#include <winioctl.h>
#include <stdio.h>
#include <shellscalingapi.h>
#include <intrin.h>

#pragma comment(lib, "SHCore")

#define wszDrive L"\\\\.\\PhysicalDrive0"

struct DiskSpace
{
	std::int64_t avaliableBytes;
	std::int64_t totalBytes;
	std::int64_t freeBytes;
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
	DiskSpace& GetDriveSize(wchar_t* drive = 0);
	int GetCpuInfo();
private:
	BOOL GetDriveGeometry(LPWSTR path, DISK_GEOMETRY* pdg);
	int GetScalePercentage(int dpi);
};

