/**
* Copyright (c) 2019 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of CPPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <iostream>
#include <memory>
#include <cppset/TestInterface.h>

typedef std::shared_ptr<TestInterface> ITestPtr;

class Test : public TestInterface
{
    public:
        Test(){std::cout << "Se construye Test " << std::endl;}
        virtual ~Test(){std::cout << "Se destruye Test " << std::endl;}
        void test()
        {
            std::cout << "¡Se ejecutó test()!" << std::endl;
        }
};

extern "C" ITestPtr create(std::string);

ITestPtr create(std::string typeinfo)
{
	/*PARA QUE SE ENTIENDA EL IF LÓGICO ES LO MISMO:*/
	// if ( typeid(TestInterface).name() == typeinfo ) return std::make_shared<Test>();
	// return nullptr;

	/*Y TAMBIÉN ES LO MISMO:*/
	// if ( typeid(TestInterface).name() == typeinfo ) 
	// {
	// 	return std::make_shared<Test>();
	// }
	// else
	// {
	// 	return nullptr;
	// }

	return ( typeid(TestInterface).name() == typeinfo )? std::make_shared<Test>() : nullptr;
}
