#include "HardwareInfo.h"

#include <iostream>

ScreenInfo& HardwareInfo::GetDesktopResolution()
{
	ScreenInfo si;

	int res = 0;
	RECT desktop;
	HWND hDesktop = GetDesktopWindow();

	res = GetWindowRect(hDesktop, &desktop);
	if (res == 0)
	{
		printf("GetWindowRect failed: %d\n", res);
		exit(1);
	}

	HMONITOR hMonitor = 0;
	UINT dpiX;
	UINT dpiY;
	MONITORINFO info;

	hMonitor = MonitorFromWindow(hDesktop, MONITOR_DEFAULTTONEAREST);
	GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY);
	GetMonitorInfoA(hMonitor, &info);

	si.x = desktop.right * (GetScalePercentage(dpiX) / 100);
	si.y = desktop.bottom * (GetScalePercentage(dpiY) / 100);
	si.xRaw = desktop.right;
	si.yRaw = desktop.bottom;
	si.scalePercentageX = GetScalePercentage(dpiX);
	si.scalePercentageY = GetScalePercentage(dpiY);

	return si;
}

BOOL HardwareInfo::GetDriveGeometry(LPWSTR path, DISK_GEOMETRY* pdg)
{
	HANDLE hDevice = 0;
	BOOL bRes = false;
	DWORD junk = 0;

	hDevice = CreateFileW(path, 0, 
		FILE_SHARE_WRITE | FILE_SHARE_READ,
		0, OPEN_EXISTING, 0, 0);

	if (hDevice == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	bRes = DeviceIoControl(hDevice, IOCTL_DISK_GET_DRIVE_GEOMETRY,
		0, 0, pdg, sizeof(*pdg), &junk, 0);

	CloseHandle(hDevice);

	return bRes;
}

int HardwareInfo::GetScalePercentage(int dpi)
{
	switch (dpi)
	{
	case 96:
		return 100;
	case 120:
		return 125;
	case 144:
		return 150;
	case 192:
		return 200;
	default:
		printf("Unknown dpi\n");
		return 0;
	}
}

DiskGeometryEx& HardwareInfo::GetDriveGeometryInfo()
{
	DiskGeometryEx dge;
	dge.pdg = { 0 };
	dge.diskSize = 0;
	bool res = false;

	res = GetDriveGeometry((LPWSTR)wszDrive, &dge.pdg);
	if (res)
	{
		dge.diskSize = dge.pdg.Cylinders.QuadPart * dge.pdg.TracksPerCylinder
			* dge.pdg.SectorsPerTrack * dge.pdg.BytesPerSector;
		return dge;
	}
	else
	{
		wprintf(L"GetDriveGeometry failed: %ld\n", GetLastError());
		exit(1);
	}

	return dge;
}

DiskSpace& HardwareInfo::GetDriveSize(const wchar_t* drive)
{
	int res = 0;
	DiskSpace ds;

	res = GetDiskFreeSpaceEx(drive,
		(PULARGE_INTEGER)&ds.avaliableBytes, 
		(PULARGE_INTEGER)&ds.totalBytes, 
		(PULARGE_INTEGER)&ds.freeBytes);

	if (res == 0)
	{
		printf("GetDiskFreeSpaceEx failed: %d\n", res);
		exit(1);
	}

	return ds;
}

int* HardwareInfo::GetCpuRegisters()
{
	ZeroMemory(&registers, 0);
	__cpuid(registers, 0);
	return registers;
}

int HardwareInfo::GetCPULogicalProcessorCount()
{
	return std::thread::hardware_concurrency();
}
