#include "headers.h"

#include "dupCheck.h"
#include "peripherals.h"
#include "hardwareInfo.h"
#include "DataConversion.h"

#include <iostream>
#include <string>

int main()
{
	HardwareInfo hwi;

	std::cout << "CPU Threads: " << hwi.GetCPULogicalProcessorCount() 
		<< std::endl;

	int* regs = hwi.GetCpuRegisters();
	std::cout 
		<< "reg1: " << regs[0] 
		<< " reg2: " << regs[1] 
		<< std::endl;

	std::string vendor;
	vendor += regs[0];
	vendor += regs[1];
	vendor += regs[2];
	vendor += regs[3];
	std::cout << vendor << std::endl;

	ScreenInfo si = hwi.GetDesktopResolution();
	std::cout << "Desktop Resolution: " 
		<< "X: " << si.x << " Y: " << si.y << std::endl;
	
	DiskGeometryEx dse = hwi.GetDriveGeometryInfo();
	std::cout << "Disk Size: " << BytesToGB(dse.diskSize) << std::endl;

	DiskSpace ds = hwi.GetDriveSize();
	std::cout
		<< "Avaliable Storage: " << BytesToGB(ds.avaliableBytes) << "\n" 
		<< "Free Storage: " << BytesToGB(ds.freeBytes) << "\n" 
		<< "Directory Size: " << BytesToGB(ds.totalBytes) << "\n" 
		<< "Used Storage: " << BytesToGB(ds.totalBytes - ds.freeBytes) 
		<< std::endl;

	/*Peripherals p;
	Sleep(2000);
	p.SendKey(Peripherals::KEY::A);

	BOT bot;
	TerminateProcess(bot);*/

	system("pause");

	return 0;
}