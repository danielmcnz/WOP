#include "DataConversion.h"

__int64 BytesToGB(__int64 bytes)
{
	for (int i = 0; i < 3; ++i)
	{
		bytes = bytes / 1024;
	}
	return bytes;
}

__int64 BytesToMB(__int64 bytes)
{
	for (int i = 0; i < 2; ++i)
	{
		bytes = bytes / 1024;
	}
	return bytes;
}

__int64 BytesToKB(__int64 bytes)
{
	return bytes / 1024;
}
