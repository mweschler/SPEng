#pragma once


#if ASSERTIONS_ENABLED
	void reportAssertion(const char *expression, const char *file, const long line);

	#define debugBreak() __asm { int 3}

	#define ASSERT(expr) \
	if(expr) { } \
	else \
	{ \
	reportAssertion(#expr, __FILE__, __LINE__); \
		debugBreak(); \
	}
#else
#define ASSERT(expr)
#endif