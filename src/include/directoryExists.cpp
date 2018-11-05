#include <sys/types.h>
#include <sys/stat.h>

#include "directoryExists.hpp"

bool PanCake::directoryExists(const char*path)
{
    struct stat info;

    if(stat(path,&info) != 0)
        return false;
    else if(info.st_mode & S_IFDIR)
        return true;
    else
        return false;
}