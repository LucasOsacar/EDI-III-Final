#include "IAction.h"
#include "../dbhandler/IDatabaseHandler.h"

#include <ComponentFactory.h>
#include <iostream>
#include <memory>

typedef std::shared_ptr<IDatabaseHandler> IDBHandlerPtr;
typedef std::shared_ptr<ComponentFactory> ComponentFactoryPtr;
typedef std::shared_ptr<IAction> IActionPtr;

class AddAction : public IAction
{
 public:
    void execute(void);
    AddAction(void);
    ~AddAction(void);
 private:
    AddAction(const AddAction &a);
    const AddAction& operator =(const AddAction &a);
};

AddAction::AddAction()
{

}

AddAction::~AddAction()
{
    
}

void AddAction::execute()
{
    ComponentFactoryPtr cF(new ComponentFactory());
    IDBHandlerPtr dbh = cF->create<IDatabaseHandler>("../dbhandler/DatabaseHandler");
    dbh->prepareQuery("INSERT INTO List(task) VALUES(?)");
    dbh->addParameter(1, "JuanSON");
    dbh->execute();
}

extern "C" IActionPtr create(std::string);

IActionPtr create(std::string typeinfo)
{
	return ( typeid(IAction).name() == typeinfo )? std::make_shared<AddAction>() : nullptr;
}