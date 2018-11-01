#include <sys/stat.h>

#include "fileExists.hpp"

bool PanCake::fileExists(const char*path)
{
    struct ::stat buffer;
    return (::stat(path,&buffer) == 0);
}
