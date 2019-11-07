g++ -shared -Wall -std=c++11 -I./ -I../include -I ../dbhandler DeleteAction.cpp -o "Delete.dll"
g++ -Wall -std=c++11 -I./ -I../include TestDelete.cpp -o "TestDelete.exe"