#include<iostream>

#include "test.h"
#include "detectType.h"

int main(){
	system("stty raw");
	while(true){
		system("clear");
		printWords();
		startTest();
	}
	return 0;
}
