#include "IAction.h"
#include "../dbhandler/IDatabaseHandler.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <ComponentFactory.h>
#include <memory>
#include <iostream>

typedef std::unordered_map< std::string, std::string > Row;
typedef std::vector< Row > Table;
typedef std::shared_ptr<IDatabaseHandler> IDBHandlerPtr;
typedef std::shared_ptr<ComponentFactory> ComponentFactoryPtr;

typedef std::shared_ptr<IAction> IActionPtr;

class ToListAction : public IAction
{
 public:
    void execute(void);
    ToListAction(void);
    ~ToListAction(void);
 private:
    ToListAction(const ToListAction &a);
    const ToListAction& operator =(const ToListAction &a);
};

ToListAction::ToListAction()
{

}

ToListAction::~ToListAction()
{
    
}

void ToListAction::execute()
{
    ComponentFactoryPtr cF(new ComponentFactory());
    IDBHandlerPtr dbh = cF->create<IDatabaseHandler>("../dbhandler/DatabaseHandler");
    dbh->prepareQuery("SELECT * FROM List");
    Table table = dbh->fetchAll();

    std::cout << "Table DATA row 1:" << std::endl;
    std::cout << "id: " << table[0]["id"] << std::endl;
    std::cout << "task: " << table[0]["task"] << std::endl << std::endl;
  
}

extern "C" IActionPtr create(std::string);

IActionPtr create(std::string typeinfo)
{
	return ( typeid(IAction).name() == typeinfo )? std::make_shared<ToListAction>() : nullptr;
}