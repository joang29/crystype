#include<iostream>

#include "test.h"
#include "detectType.h"

int main(){
	system("stty raw");
	std::cout<<"\e[5 q";
	while(true){
		system("clear");
		printWords(40);
		startTest();
	}
	return 0;
}
