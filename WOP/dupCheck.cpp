#include "dupCheck.h"

/*
	returns:
		1 if instance running
		0 if no instane
		-1 if error
*/
int CheckProc(const wchar_t* procName, PROCESSENTRY32 *procEntry)
{
	HANDLE hSnap;

	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		printf("invalid handle value %s", hSnap);
		return -1;
	}

	procEntry->dwSize = sizeof(PROCESSENTRY32);
	
	if (!Process32First(hSnap, procEntry))
	{
		printf("process32first failed");
		CloseHandle(hSnap);
		return -1;
	}

	do
	{
		if(wcscmp(procEntry->szExeFile, procName) == 0)
		{
			return 1;
		}
	} while (Process32Next(hSnap, procEntry));

	CloseHandle(hSnap);

	return 0;
}

int TerminateProcess(BOT bot)
{
	PROCESSENTRY32 procEntry;

	switch (CheckProc(bot.procName, &procEntry))
	{
	case -1:
		printf("Error occurred while finding process\n");
		break;
	case 0:
		wprintf(L"Process %s not running\n", bot.procName);
		break;
	case 1:
	{
		printf("Process running...\n");

		HANDLE hProc;
		hProc = OpenProcess(PROCESS_TERMINATE, 0, procEntry.th32ProcessID);
		if (hProc == NULL)
		{
			printf("couldnt open process handle\n");
			return 1;
		}

		BOOL termProc = TerminateProcess(hProc, 0);
		if (termProc == 0)
		{
			printf("failed to terminate process %d\n", procEntry.th32ProcessID);
			return 1;
		}
		printf("terminated process\n");

		CloseHandle(hProc);

		break;
	}
	default:
		printf("Unexpected behaviour, guess ima go back to python now\n");
		return 69;
	}
}