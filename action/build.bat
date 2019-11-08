g++ -shared -Wall -std=c++11 -I./ -I../include -I ../dbhandler AddAction.cpp -o "Add.dll"
g++ -shared -Wall -std=c++11 -I./ -I../include -I ../dbhandler CreateAction.cpp -o "Create.dll"
g++ -shared -Wall -std=c++11 -I./ -I../include -I ../dbhandler DeleteAction.cpp -o "Delete.dll"
g++ -shared -Wall -std=c++11 -I./ -I../include -I ../dbhandler ToListAction.cpp -o "ToList.dll"