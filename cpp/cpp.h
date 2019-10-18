#pragma once
#define RECURSE(x, ...) x RECURSE(__VA_ARGS__)
#define _RECURSE(x, ...) x RECURSE(__VA_ARGS__)
//#define RECURSE()

#define xstr(x) #x
#define str(x) xstr(x)


