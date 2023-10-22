#include <chrono>
#include <cmath>
#include<iostream>
#include<unistd.h>
#include<sys/ioctl.h>

#include "detectType.h"
#include "results.h"

void startTest();
void selectTest();
void printWords(int);
std::string returnTest();

std::chrono::duration<double> duration;
std::string test;
int testNumber = 40;
std::string words[150] = {"he", "she", "we", "they", "it", "you" ,"too", "have", "there", "write", "even", "which", "where", "what", "who", "by", "how", "all", "sometimes" ,"word", "world", "old", "can", "must", "might", "house", "with", "without", "would", "make", "about", "know", "will", "as", "people", "like", "because", "tell", "always" ,"say", "find", "through", "life", "while", "person", "answer", "never", "problem", "believe", "point", "thought", "business", "city", "continue", "pay", "car", "however", "allow", "although", "home", "plan", "effect", "suggest", "action", "easy", "work", "between", "same", "program", "take", "high", "number", "custom", "star", "right" , "table", "ability", "character", "left", "expert", "cold", "avoid", "finish", "theory", "improve", "list", "lesson", "package", "range", "best", "style", "discover", "weight", "fly", "production", "impact", "talk", "me", "close", "imagine", "visit", "main", "note", "radio", "nation","forget","laugh", "beach", "bed", "block", "chapter", "ever", "everything", "instead", "look", "loud", "depend", "date", "weather", "bank", "probably", "reply", "smile", "total", "yesterday", "today", "week", "weekend", "weekly", "test", "text", "teach", "think", "stuff", "sport", "someone", "some", "resolve", "principal", "is", "be", "understand", "tradition", "title", "than", "successful", "return", "quick", "ask", "publish"};
	
void startTest(){
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	
	std::cout<<"\033[38;5;14m\033["<<round(size.ws_row/2.0)+5<<";"<<round(size.ws_col/2.0)-15<<"f\033[38;5;255m20\t\033[38;5;255m30\t\033[38;5;39m40";

	selectTest();

	std::cout<<"\033["<<round(size.ws_row/2.0)-3<<";"<<round(size.ws_col/2.0)-30<<"f\033[2K";

	std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();

	detectType();
		
	std::chrono::high_resolution_clock::time_point finalTime = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::duration<double>>(finalTime - time);

	calculateWPMAndAccuracy();
}

void selectTest(){
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	
	char key=1;
	
	while(true){	
		std::cout<<"\033[38;5;14m\033["<<round(size.ws_row/2.0)-3<<";"<<round(size.ws_col/2.0)-30<<"fPress any key to start";
	
		key = getchar();

		if(key=='1'){
			testNumber = 20;
			std::cout<<"\033[38;5;14m\033["<<round(size.ws_row/2.0)+5<<";"<<round(size.ws_col/2.0)-15<<"f\033[38;5;39m20\t\033[38;5;255m30\t\033[38;5;255m40";
		}
		else if(key=='2'){
			testNumber = 30;
			std::cout<<"\033[38;5;14m\033["<<round(size.ws_row/2.0)+5<<";"<<round(size.ws_col/2.0)-15<<"f\033[38;5;255m20\t\033[38;5;39m30\t\033[38;5;255m40";
		}
		else if(key=='3'){
			testNumber = 40;
			std::cout<<"\033[38;5;14m\033["<<round(size.ws_row/2.0)+5<<";"<<round(size.ws_col/2.0)-15<<"f\033[38;5;255m20\t\033[38;5;255m30\t\033[38;5;39m40";
		}
		else return;

		printWords(testNumber);
	}
}
void printWords(int amountOfWords){
	system("clear");

	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	
	int previousNumber = -1;

	std::cout<<"\033["<<round(size.ws_row/2.0)-2<<";"<<round(size.ws_col/2.0)-30<<"f";

	srand(time(NULL));
	
	test="";
	for(int i = 1; i<=amountOfWords; i++){
		int wordNumber = rand() % 150;
		
		if(wordNumber==previousNumber){
			i--; 
			continue;
		}else previousNumber = wordNumber;

		test += words[wordNumber] + " ";

		std::cout<<"\033[38;5;248m"<<words[wordNumber]<<" ";
		if(i % 10 == 0){
			test.pop_back();
			test+="/";

			std::cout<<"\033["<<round(size.ws_row/2.0)+i/10-2<<";"<<round(size.ws_col/2.0)-30<<"f";
		}
	}

	test.pop_back();
	test+="*";
}

std::string returnTest(){
	return test;
}

int returnSecondsTest(){
	return duration.count();
}
