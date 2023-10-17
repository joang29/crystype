#include<iostream>
#include<unistd.h>
#include<cmath>

#include "detectType.h"
#include "test.h"

void calculateWPMAndAccuracy();
void calculateCorrectedErrors();

void calculateWPMAndAccuracy(){

	int amountOfPressedKeysWithoutSpaces = returnAmountOfPressedKeysWithoutSpaces();
	std::vector<int> errors = returnErrors();
	
	//accuracy
	int accuracy;
	if(errors.empty()) accuracy = 100;
	accuracy = (amountOfPressedKeysWithoutSpaces-errors.size())*100/amountOfPressedKeysWithoutSpaces;
	
	//wpm
	int typedWords = std::round(amountOfPressedKeysWithoutSpaces / 5);

	calculateCorrectedErrors();
	int errorsPenalty = errors.size()/(returnSecondsTest()/60.0);
	int wpm = (typedWords / (returnSecondsTest()/60.0)) - errorsPenalty;
	if(wpm < 0) wpm = 0;

	std::cout<<"\033[1;0f"<<"\033[38;5;97mWPM: \033[0m"<<wpm<<"\t\t"<<"\033[38;5;97mAccuracy: \033[0m"<<accuracy<<"%"<<std::endl;

	sleep(2);

	std::cout<<"\033[1;0f\t\t\t\tPress y to do another typing test";
	
	if(getchar()!='y') exit(0);
}

void calculateCorrectedErrors(){
	std::vector<int> errors = returnErrors();
	std::string typingTest = returnTest();
	std::string finalTest = returnFinalTest();

	for(int i = 0; i<errors.size(); i++){
		if(finalTest[errors[i]] == typingTest[errors[i]]) errors.erase(errors.begin());
	}
}
