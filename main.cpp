/**
* Copyright (c) 2019 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of CPPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <iostream>
#include <cppset/TestInterface.h>
#include <cppset/TestInterface2.h>
#include <cppset/TestInterface3.h>
#include <cppset/ComponentFactory.h>

typedef std::shared_ptr<TestInterface> ITestPtr;
typedef std::shared_ptr<TestInterface2> ITest2Ptr;
typedef std::shared_ptr<TestInterface3> ITest3Ptr;
typedef std::shared_ptr<ComponentFactory> ComponentFactoryPtr;

int main()
{
    ComponentFactoryPtr cF(new ComponentFactory());
    ITestPtr tCO = cF->create<TestInterface>("./lib/Test");
    tCO->test();
   
    ITest2Ptr tCO2 = cF->create<TestInterface2>("./lib/Test2");
    tCO2->test2();    

    //INCORRECTO:
    // ITestPtr tCO3 = cF->create<TestInterface>("./lib/Test3");
    // tCO3->test();

    //CORRECTO:
    ITest3Ptr tCO3 = cF->create<TestInterface3>("./lib/Test3");
    tCO3->test3();
    return 0;
}