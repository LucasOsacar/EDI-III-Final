g++ -shared -Wall -std=c++11 -I./ -I../include -I ../dbhandler ToListAction.cpp -o "ToList.dll"
g++ -Wall -std=c++11 -I./ -I../include TestToList.cpp -o "TestToList.exe"