#include<unistd.h>
#include<vector>
#include<sys/ioctl.h>
#include<cmath>

#include "test.h"

int amountOfPressedKeysWithoutSpaces = 0, amountOfPressedKeys = 0, cursorPositionX = 1, currentLine = 2;
std::string typingTest, finalTest;
std::vector<int> errors;

void detectType();

void detectType(){
	typingTest = returnTest();
	finalTest="";
	errors.erase(errors.begin(), errors.end());
		
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

	amountOfPressedKeysWithoutSpaces = 0, amountOfPressedKeys = 0;

	int lines = round(size.ws_row/2.0)-2;
	int cols = round(size.ws_col/2.0)-30;
	
	currentLine = lines;
	cursorPositionX = cols;	

	while(true){
		std::cout<<"\033["<<currentLine<<";"<<cursorPositionX<<"f";
		char pressedKey = getchar();
		
		if(pressedKey==127 && cursorPositionX>cols){
			std::cout<<"\b\b\b"<<typingTest[amountOfPressedKeys-1]<<typingTest[amountOfPressedKeys]<<typingTest[amountOfPressedKeys+1];
			std::cout<<"\033["<<currentLine<<";"<<amountOfPressedKeys<<"f";
			amountOfPressedKeys--;
			cursorPositionX--;
			finalTest.pop_back();
			continue;
		}

		if(pressedKey==typingTest[amountOfPressedKeys]){
			std::cout<<"\b\033[38;5;177m"<<pressedKey<<"\033[0m";
		}else{
			errors.push_back(amountOfPressedKeys);
			typingTest[amountOfPressedKeys] == ' ' ? std::cout<<"\b\033[38;5;1m"<<pressedKey<<"\033[0m" : 
				                                 std::cout<<"\b\033[38;5;1m"<<typingTest[amountOfPressedKeys]<<"\033[0m";
		}
		if(pressedKey != ' ') amountOfPressedKeysWithoutSpaces++;
		
		finalTest+=pressedKey;
		
		if(typingTest[amountOfPressedKeys]=='/'){
			std::cout<<"\b ";
			errors.pop_back();
			
			currentLine++;
			cursorPositionX=cols-1;	

			finalTest.pop_back();
			finalTest+="/";
		}else if(typingTest[amountOfPressedKeys]=='*'){
			std::cout<<"\b ";
			errors.pop_back();
			return;
		}
		amountOfPressedKeys++;
		cursorPositionX++;
	}
}

std::vector<int> returnErrors(){
	return errors;
}

std::string returnFinalTest(){
	return finalTest;
}

int returnAmountOfPressedKeysWithoutSpaces(){
	return amountOfPressedKeysWithoutSpaces;
}
