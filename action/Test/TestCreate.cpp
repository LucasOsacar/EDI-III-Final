#include <iostream>
#include "IAction.h"
#include <ComponentFactory.h>

#include <memory>

typedef std::shared_ptr<IAction> IActionPtr;
typedef std::shared_ptr<ComponentFactory> ComponentFactoryPtr;

int main()
{
    ComponentFactoryPtr cF(new ComponentFactory());
    IActionPtr tCO = cF->create<IAction>("./Create");
    tCO->execute();

    return 0;
}
