#include<iostream>
#include <stdexcept>

#include "test.h"
#include "detectType.h"

int main(){
	system("stty raw");
	while(true){
		system("clear");
		printWords(2);
		selectTest();
		startTest();
	}
	return 0;
}
