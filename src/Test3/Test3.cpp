/**
* Copyright (c) 2019 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of CPPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <iostream>
#include <memory>
#include <cppset/TestInterface3.h>

typedef std::shared_ptr<TestInterface3> ITest3Ptr;

class Test3 : public TestInterface3
{
    public:
        Test3(){std::cout << "Se construye Test3 " << std::endl;}
        virtual ~Test3(){std::cout << "Se destruye Test3 " << std::endl;}
        void test3()
        {
            std::cout << "¡Se ejecutó test3()!" << std::endl;
        }
};

extern "C" ITest3Ptr create(std::string);

ITest3Ptr create(std::string typeinfo)
{
	return ( typeid(TestInterface3).name() == typeinfo ) ? std::make_shared<Test3>() : nullptr;
}
