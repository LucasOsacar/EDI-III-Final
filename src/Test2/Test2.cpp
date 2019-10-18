/**
* Copyright (c) 2019 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of CPPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <iostream>
#include <memory>
#include <cppset/TestInterface2.h>

typedef std::shared_ptr<TestInterface2> ITest2Ptr;

class Test2 : public TestInterface2
{
    public:
        Test2(){std::cout << "Se construye Test2 " << std::endl;}
        virtual ~Test2(){std::cout << "Se destruye Test2 " << std::endl;}
        void test2()
        {
            std::cout << "¡Se ejecutó test2()!" << std::endl;
        }
};

extern "C" ITest2Ptr create(std::string);

ITest2Ptr create(std::string typeinfo)
{
	return ( typeid(TestInterface2).name() == typeinfo ) ? std::make_shared<Test2>() : nullptr;
}
