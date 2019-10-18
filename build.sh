#!/bin/bash
##Borro el directorio si ya existiera
if [ -d ./bin/ ];
	then rm -r ./bin/;
fi
##Creo los directorios para el Binario y las bibliotecas
mkdir ./bin/
mkdir ./bin/lib/

##compilo el Binario
g++ -Wall -std=c++11 -ldl -I./include/ main.cpp -o ./bin/main.bin

##compilo las bibliotecas
g++ -shared -Wall -std=c++11 -fPIC -I./include/ ./src/Test/Test.cpp -o ./bin/lib/Test.so
g++ -shared -Wall -std=c++11 -fPIC -I./include/ ./src/Test2/Test2.cpp -o ./bin/lib/Test2.so
g++ -shared -Wall -std=c++11 -fPIC -I./include/ ./src/Test3/Test3.cpp -o ./bin/lib/Test3.so

##otorgo permisos de escritura a los ejecutables
chmod +x ./bin/main.bin
