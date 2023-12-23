#pragma once
#include <assert.h>

#ifdef _DEBUG
#define ASSERT(x) assert(x)
#else
#define ASSERT(x) ((void)(x))
#endif