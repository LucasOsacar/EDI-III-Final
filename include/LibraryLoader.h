/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of CPPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef LIBRARY_LOADER_H
#define LIBRARY_LOADER_H

#ifdef __unix__
    #define RTLD_LAZY   1
    #define RTLD_NOW    2
    #define RTLD_GLOBAL 4
    #include <vendors/dlfcn.h>
#elif __APPLE__
    #include <vendors/dlfcnMac.h>
#elif defined(_WIN32) || defined(WIN32)
    #include <windows.h>
#endif // defined

#include <string>
#include <iostream>

class LibraryLoader
{
    public:
        LibraryLoader();
        virtual ~LibraryLoader();
        static LibraryLoader* getInstance();

        void* loadLibrary(std::string name);
        void* getExternalFunction(std::string name);
        bool freeLibrary();

    private:
        static LibraryLoader* instance;
        void* library;
        void* method;
        bool freedom;
};

LibraryLoader::LibraryLoader()
{
    //ctor
    std::cout << "Se construye LibraryLoader" << std::endl;
}

LibraryLoader::~LibraryLoader()
{
    //dtor
    std::cout << "Se destruye LibraryLoader" << std::endl;
}

void* LibraryLoader::loadLibrary(std::string name)
{
    #ifdef __unix__
        name += ".so";
        library = dlopen(name.c_str(), RTLD_NOW);
    #elif __APPLE__
        name += ".dylib";
        library = dlopen(name.c_str(), RTLD_LOCAL|RTLD_LAZY);
    #elif defined(_WIN32) || defined(WIN32)
        name += ".dll";
        library = (void*) LoadLibrary(name.c_str());
    #endif // defined

    return library;
}

void* LibraryLoader::getExternalFunction(std::string name)
{
    #ifdef __unix__
        method = dlsym(library, name.c_str());
    #elif __APPLE__
        method = dlsym(library, name.c_str());
    #elif defined(_WIN32) || defined(WIN32)
        method = (void*) GetProcAddress((HINSTANCE)library, name.c_str());
    #endif // defined

    return method;
}

bool LibraryLoader::freeLibrary()
{
    #ifdef __unix__
        freedom = dlclose(library);
    #elif __APPLE__
        freedom = dlclose(library);
    #elif defined(_WIN32) || defined(WIN32)
        freedom = FreeLibrary((HINSTANCE)library);
    #endif // defined

    return freedom;
}

#endif // LIBRARY_LOADER_H

