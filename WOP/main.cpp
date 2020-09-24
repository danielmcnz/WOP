#include "headers.h"

#include "dupCheck.h"
#include "peripherals.h"
#include "hardwareInfo.h"
#include "DataConversion.h"

#include <iostream>


int main()
{
	HardwareInfo hwi;

	ScreenInfo si = hwi.GetDesktopResolution();
	std::cout << si.x << " " << si.y << std::endl;
	
	DiskGeometryEx dse = hwi.GetDriveGeometryInfo();
	std::cout << BytesToGB(dse.diskSize) << std::endl;

	/*DiskSpace ds = av.GetDriveSize();
	std::cout << BytesToGB(ds.avaliableBytes) << " " 
		<< BytesToGB(ds.freeBytes) << " " 
		<< BytesToGB(ds.totalBytes) << " " 
		<< BytesToGB(ds.totalBytes - ds.freeBytes) << std::endl;*/

	/*Peripherals p;
	Sleep(2000);
	p.SendKey(Peripherals::KEY::A);

	BOT bot;
	TerminateProcess(bot);*/

	system("pause");

	return 0;
}