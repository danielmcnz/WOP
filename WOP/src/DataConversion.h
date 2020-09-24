#pragma once

#define DATA_CONVERSION
#define DATA_BYTES

#ifdef DATA_CONVERSION

#ifdef DATA_BYTES

__int64 BytesToGB(__int64 bytes);
__int64 BytesToMB(__int64 bytes);
__int64 BytesToKB(__int64 bytes);

#endif

#endif