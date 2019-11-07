#include "IAction.h"
#include <IDatabaseHandler.h>

#include <ComponentFactory.h>
#include <iostream>
#include <memory>

typedef std::shared_ptr<IDatabaseHandler> IDBHandlerPtr;
typedef std::shared_ptr<ComponentFactory> ComponentFactoryPtr;
typedef std::shared_ptr<IAction> IActionPtr;

class CreateAction : public IAction
{
 public:
    void execute()
    {
        ComponentFactoryPtr cF(new ComponentFactory());
        IDBHandlerPtr dbh = cF->create<IDatabaseHandler>("../dbhandler/DatabaseHandler");
        dbh->prepareQuery("CREATE TABLE IF NOT EXISTS List (id INTEGER PRIMARY KEY AUTOINCREMENT, task VARCHAR(100))");
        dbh->execute();
    }
    CreateAction(void){}
    virtual ~CreateAction(void){}
 private:
    CreateAction(const CreateAction &a);
    const CreateAction& operator =(const CreateAction &a);
};

extern "C" IActionPtr create(std::string);

IActionPtr create(std::string typeinfo)
{
    return ( typeid(IAction).name() == typeinfo )? std::make_shared<CreateAction>() : nullptr;
}