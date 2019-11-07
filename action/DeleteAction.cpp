#include "IAction.h"
#include "../dbhandler/IDatabaseHandler.h"

#include <ComponentFactory.h>
#include <iostream>
#include <memory>

typedef std::shared_ptr<IDatabaseHandler> IDBHandlerPtr;
typedef std::shared_ptr<ComponentFactory> ComponentFactoryPtr;
typedef std::shared_ptr<IAction> IActionPtr;

class DeleteAction : public IAction
{
 public:
    void execute(void);
    DeleteAction(void);
    ~DeleteAction(void);
 private:
    DeleteAction(const DeleteAction &a);
    const DeleteAction& operator =(const DeleteAction &a);
};

DeleteAction::DeleteAction()
{

}

DeleteAction::~DeleteAction()
{
    
}

void DeleteAction::execute()
{
    ComponentFactoryPtr cF(new ComponentFactory());
    IDBHandlerPtr dbh = cF->create<IDatabaseHandler>("../dbhandler/DatabaseHandler");
    dbh->prepareQuery("DELETE FROM List WHERE id=?");
    dbh->addParameter(1, "1");
    dbh->execute();
}

extern "C" IActionPtr create(std::string);

IActionPtr create(std::string typeinfo)
{
	return ( typeid(IAction).name() == typeinfo )? std::make_shared<DeleteAction>() : nullptr;
}