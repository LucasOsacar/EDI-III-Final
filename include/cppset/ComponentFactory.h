/**
* Copyright (c) 2016-2019 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef COPONENT_FACTORY_H
#define COPONENT_FACTORY_H

#include <iostream>
#include <stdlib.h>
#include <memory>
#include <typeinfo>
#include <cppset/LibraryLoader.h>

typedef std::shared_ptr<LibraryLoader> LoaderPtr;
class ComponentFactory
{
    public:
        ComponentFactory()
        { 
            std::cout << "Se construye ComponentFactory" << std::endl;
            //THE LOADER:
            _loader = std::make_shared<LibraryLoader>();
        }
        virtual ~ComponentFactory()
        {
            std::cout << "Se destruye ComponentFactory" << std::endl;
            _loader->freeLibrary();
        }
        
        template<typename InterfaceType> std::shared_ptr<InterfaceType> create(std::string path)
        {
            typedef std::shared_ptr<InterfaceType> InterfaceTypePtr;

            //LOAD:
            void* load = _loader->loadLibrary(path);

            //NULL COMPONENT OBJECT:
            InterfaceTypePtr componentObject = nullptr;
            if(load)
            {
                //CREATE:
                typedef InterfaceTypePtr ( *Factory ) (std::string);
                Factory factory = ( Factory ) _loader->getExternalFunction( "create" );

                if(factory)
                {

                    InterfaceTypePtr createdComponent = factory(typeid(InterfaceType).name());//construyo una sola vez
                    if( std::dynamic_pointer_cast<InterfaceType> (createdComponent) != nullptr )
                    //if( dynamic_cast<InterfaceType*> (createdComponent.get()) != nullptr )
                    {
                        componentObject = createdComponent;
                    }
                    else
                    {
                        _loader->freeLibrary();
                        std::cout << "Error: The component doesn't implement the interface: " << typeid(InterfaceType).name() << std::endl;
                        exit(-1);
                    }
                }
                else
                {
                    _loader->freeLibrary();
                    std::cout << "Error:  Failed creating a component from "
                            << path << ", there is no external function \"create(void)\"." << std::endl;
                    exit(-1);
                }
            }
            else
            {
                _loader->freeLibrary();
                std::cout << "Error: Failed to load the component: " << path << std::endl;
                exit(-1);
            }
            return componentObject;
        }
    private:
         LoaderPtr _loader;
};
#endif // COPONENT_FACTORY_H