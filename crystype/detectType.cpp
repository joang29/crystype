#include <cmath>
#include <cstdio>
#include<unistd.h>
#include<vector>
#include "test.h"

int amountOfPressedKeysWithoutSpaces = 0, amountOfPressedKeys = 0, cursorPositionX = 1, currentLine = 2;
std::string typingTest, finalTest;
std::vector<int> errors;

void detectType();
void startTimer(int);
void calculateWPMAndAccuracy();
void calculateCorrectedErrors();

void detectType(){
	currentLine = 2;
	typingTest = returnTest();
	
	bool timerIsOn = true;

	amountOfPressedKeysWithoutSpaces = 0, amountOfPressedKeys = 0, cursorPositionX = 1;

	while(timerIsOn){
		timerIsOn = returnIfTimerIsOn();
		
		std::cout<<"\033["<<currentLine<<";"<<cursorPositionX<<"f";
		char pressedKey = getchar();
		
		if(pressedKey==127 && cursorPositionX>1){
			std::cout<<"\b\b\b"<<typingTest[amountOfPressedKeys-1]<<typingTest[amountOfPressedKeys]<<typingTest[amountOfPressedKeys+1];
			std::cout<<"\033["<<currentLine<<";"<<amountOfPressedKeys<<"f";
			amountOfPressedKeys--;
			cursorPositionX--;
			continue;
		}

		if(pressedKey==typingTest[amountOfPressedKeys]){
			std::cout<<"\b\033[38;5;177m"<<pressedKey<<"\033[0m";
		}else{
			errors.push_back(amountOfPressedKeys);
			std::cout<<"\b\033[38;5;1m"<<typingTest[amountOfPressedKeys]<<"\033[0m";
		}
		if(pressedKey != ' ') amountOfPressedKeysWithoutSpaces++;
		
		finalTest+=pressedKey;
		
		if(typingTest[amountOfPressedKeys]=='/'){
			std::cout<<"\b ";
			errors.pop_back();
			
			currentLine++;
			cursorPositionX=0;	

			if(currentLine % 2!=0) printWords(currentLine+1);
			else {
				typingTest = returnTest();
				amountOfPressedKeys = -1;
				cursorPositionX=0;
			}
			finalTest.pop_back();
			finalTest+="/";
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
