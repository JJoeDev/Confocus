#include <cctype>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
#define CLS "cls"
#else
#define CLS "clear"
#endif

/*
*
* FEATURES TO IMPLEMENT!
* Set custom time
* Show simple graphics while timer is going (Time left + Progress bar)
* Set + start time as argv
* Show simple graphics + controls when not in timer mode
*
*/

inline void consoleClear() { system(CLS); }

void checkArgs(const char* args);
void printHelp();
bool checkIfNumber(const char* input);

const char* welcomeText = "╦ ╦┌─┐┬  ┌─┐┌─┐┌┬┐┌─┐  ┌┬┐┌─┐  ╔═╗┌─┐┌┐┌┌─┐┌─┐┌─┐┬ ┬┌─┐\n"\
                          "║║║├┤ │  │  │ ││││├┤    │ │ │  ║  │ ││││├┤ │ ││  │ │└─┐\n"\
                          "╚╩╝└─┘┴─┘└─┘└─┘┴ ┴└─┘   ┴ └─┘  ╚═╝└─┘┘└┘└  └─┘└─┘└─┘└─┘";

float timer{0};

int main (int argc, char *argv[]) {
  consoleClear();
  std::cout << welcomeText << std::endl;
  
  if(argc > 1)
    checkArgs(argv[1]);

  std::cout << timer << '\n';

  return 0;
}

bool checkIfNumber(const char* input){
  if(input == nullptr || *input == '\0') return false;

  for(; *input != '\0'; ++input){
    if(!std::isdigit(*input)){
      return false;
    }
  }

  return true;
}

void printHelp(){
  std::cout << "Confocus can be started with no arguments and with arguments\n[ ARG ] -h | This prints this help page\n[ ARG ] [num] This starts a timer at the given time (30 = 30 sec)" << std::endl;
}

void checkArgs(const char* arg){
  if(std::strcmp(arg, "-h") == 0){
    printHelp();
  }
  else{
    if(checkIfNumber(arg)){
      timer = std::strtof(arg, nullptr);
    }
  }
}
