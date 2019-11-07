g++ -shared -Wall -std=c++11 -I./ -I../include -I ../dbhandler AddAction.cpp -o "Add.dll"
g++ -Wall -std=c++11 -I./ -I../include TestAdd.cpp -o "TestAdd.exe"