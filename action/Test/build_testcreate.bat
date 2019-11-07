g++ -shared -Wall -std=c++11 -I./ -I../include -I ../dbhandler CreateAction.cpp -o "Create.dll"
g++ -Wall -std=c++11 -I./ -I../include TestCreate.cpp -o "Test.exe"