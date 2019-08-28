#ifndef NH_DOLIB_H
#define NH_DOLIB_H

namespace lilingshui
{
    typedef void* H_LIBRARY;
    typedef void* FUNC_LIBRARY;

    H_LIBRARY LoadLibrary(const std::string strPath, std::string & strerro);
    void UnloadLibrary(H_LIBRARY hlib);
    FUNC_LIBRARY GetLibraryFunction(H_LIBRARY hlib, std::string strName);
}

#endif //NH_DOLIB_H