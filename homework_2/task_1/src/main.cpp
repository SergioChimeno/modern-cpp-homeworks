#include <iostream>
#include <random>
#include <cstdlib>
#include <sstream> 

const std::string INVALID_NUMBER_MSG = "[WARNING] : Number must be between 0 and 99"; 
const std::string INPUT_FAIL_MSG = "Error encountered, exiting..."; 

int main(int argc, char* argv[]){

    int programOutcome = EXIT_FAILURE; 

    std::random_device randomDevice;
    std::uniform_int_distribution<int> dist(0,99);

    const int randomNumber = dist(randomDevice);

    bool guessing = true;
    while(guessing){
        int guess = 0;
        //Take a guess
        std::cin >> guess;
        std::cin >> std::ws;

        if(std::cin.fail()){
            guessing = false;
            programOutcome = EXIT_FAILURE;
        }else{

            if(guess > 99 || guess <0){
                std::cerr << INVALID_NUMBER_MSG << std::endl;
            }else if(guess == randomNumber){
                guessing = false;
                programOutcome = EXIT_SUCCESS;
            }else if(guess > randomNumber){
                std::cout << "The number is smaller\n";
            }else if(guess < randomNumber){
                std::cout << "The number is larger\n";
            }
        }
    }

    if (programOutcome == EXIT_SUCCESS){
        std::cout << "You have won! The number is: " << randomNumber << std::endl;
    }else if(programOutcome == EXIT_FAILURE){
        std::cerr << INPUT_FAIL_MSG << std::endl;
        std::cout << "The number is: " << randomNumber << std::endl;
    }

    return programOutcome;
}