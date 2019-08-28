#include <assert.h>
#include <dlfcn.h>
#include <iostream>
#include "dolib.h"

namespace lilingshui
{
    H_LIBRARY LoadLibrary(const std::string strPath, std::string & strerro)
    {
        H_LIBRARY hlib = dlopen(strPath.c_str(), RTLD_LAZY);

        if (!hlib)
        {
            std::cout << "Cannot load library: " << dlerror() <<std::endl;
        }
        else
        {
            std::cout << "Load library successfully" << std::endl;
        }

        return hlib;
    }

    void UnloadLibrary(H_LIBRARY hlib)
    {
        if (!hlib)
        {
            std::cout << "The hlib is empty" << <<std::endl;
            return;
        }

        dlclose(handle);
    }

    FUNC_LIBRARY GetLibraryFunction(H_LIBRARY hlib, std::string strName)
    {
        FUNC_LIBRARY function = (FUNC_LIBRARY)dlsym(hlib,strName.c_str());
        const char *dlsym_error = dlerror();
        if (dlsym_error) 
        {
            std::cout << "Cannot load symbol " << dlsym_error << std::endl;
            return NULL;
        }
        return function;
    }
}