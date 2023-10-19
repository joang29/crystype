#include<iostream>
#include<unistd.h>
#include<cmath>
#include<sys/ioctl.h>

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

	int secondsTest = returnSecondsTest();

	calculateCorrectedErrors();
	int errorsPenalty = errors.size()/(secondsTest/60.0);
	int wpm = (typedWords / (secondsTest/60.0)) - errorsPenalty;
	if(wpm < 0) wpm = 0;

	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

	std::cout<<"\033["<<round(size.ws_row/2.0)-6<<";"<<round(size.ws_col/2.0)-30<<"f"<<"\033[38;5;45mWPM: \033[0m"<<wpm<<"\t\t"<<"\033[38;5;45mAccuracy: \033[0m"<<accuracy<<"%\t\t"<<"\033[38;5;45mTime: \033[0m"<<secondsTest<<"s"<<std::endl;

	sleep(2);

	std::cout<<"\033["<<round(size.ws_row/2.0)+1<<";"<<round(size.ws_col/2.0)-30<<"f"<<"Press \033[38;5;45my\033[0m to do another typing test";
	
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
