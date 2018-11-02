#include <cstring>
#include <errno.h>

#include "makePath.hpp"

int PanCake::makeDir(const char*path,::mode_t mode = S_IRWXU)
{
    return ::mkdir(path,mode);
}

//Adapted from answer by Yaroslav Stavnichiy
//http://stackoverflow.com/questions/2336242/recursive-mkdir-system-call-on-unix
int PanCake::makePath(char*filePath,::mode_t mode = S_IRWXU)
{
    char* p;
    for(p = ::strchr(filePath + 1,'/'); p; p = ::strchr(p + 1,'/'))
    {
        *p='\0';
        int res = PanCake::makeDir(filePath,mode);
        if(res != 0)
        {
            *p='/';
            if(errno != 17)
                return errno; 
        }
        *p='/';
    }
    return 0; 
}
