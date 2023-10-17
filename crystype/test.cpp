#include<iostream>
#include<unistd.h>
#include<thread>

#include "detectType.h"
#include "results.h"

void printWords();
void selectTest();
void startTimer(int);
std::string returnTest();

bool timerIsOn = true;
std::string test;
int secondsTest;
std::string words[100] = {"he", "she", "we", "they", "it", "you" ,"too", "have", "there", "write", "which", "where", "what", "who", "how", "all", "sometimes" ,"word", "world", "old", "can", "must", "might", "would", "make", "about", "know", "will", "as", "people", "like", "because", "tell", "always" ,"say", "find", "through", "life", "while", "person", "answer", "never", "problem", "believe", "point", "thought", "business", "city", "continue", "pay", "car", "however", "allow", "although", "home", "plan", "effect", "suggest", "action", "easy", "work", "between", "same", "program", "take", "high", "number", "custom", "star", "right" , "table", "ability", "character", "left", "expert", "cold", "avoid", "finish", "theory", "improve", "list", "lesson", "package", "range", "best", "style", "discover", "weight", "fly", "production", "impact", "talk", "me", "close", "imagine", "visit", "main", "note", "radio","laugh"};
	
void startTest(){
	std::cout<<"\033[38;5;97m\033[1;0fPress any key to start";
	getchar();
	std::cout<<"\033[1;0f\033[2K";

	std::thread typing(detectType);
	std::thread timerThread(startTimer, secondsTest);
	timerThread.join();
	typing.join();
	calculateWPMAndAccuracy();
}

void selectTest(){
	std::cout<<"\033[5;0f\033[38;5;255m"<<"Press a number to select the test [1] 15s [2] 30s [3] 60s";
	
	secondsTest=0;

	while(secondsTest == 0){
		char number = getchar();
	
		switch(number){
			case '1':
				secondsTest = 15;
			break;
			case '2':
				secondsTest = 30;
			break;
			case '3':
				secondsTest = 60;
		}
	}
	std::cout<<"\033[5;0f\033[2K";
}

void printWords(int line){
	srand(time(NULL));
	std::cout<<"\033["<<line<<";0f";
	test="";
	for(int i = 0; i<50; i++){
		int wordNumber = rand() % 100;
		
		test += words[wordNumber] + " ";

		std::cout<<words[wordNumber]<<" ";
		if(i == 25){
			test.pop_back();
			test+="/";
			std::cout<<"\n\r";
		}
	}

	test.pop_back();
	test+="/";
}

void startTimer(int seconds){
	timerIsOn = true;
	while(seconds!=0){
		seconds--;
		sleep(1);
	}
	timerIsOn = false;
}

bool returnIfTimerIsOn(){
	return timerIsOn;
}

std::string returnTest(){
	return test;
}

int returnSecondsTest(){
	return secondsTest;
}
