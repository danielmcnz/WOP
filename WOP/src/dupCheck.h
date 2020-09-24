#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <stdio.h>

#include "BotConfig.h"

int CheckProc(const wchar_t* procName, PROCESSENTRY32 *procEntry);
int TerminateProcess(BOT bot);