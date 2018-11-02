#pragma once

#include <sys/stat.h>

namespace PanCake
{
    int makeDir(const char*,::mode_t);
    int makePath(char*,::mode_t);
}
