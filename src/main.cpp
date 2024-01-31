#include <cctype>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <stdexcept>

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

// Arguments 
void checkArgs(const char* args);
void printHelp();
bool checkIfNumber(const char* input);

// Get Timer (in app)
void SetTime();
std::chrono::seconds durationParse(const std::string& input);

const char* welcomeText = "╦ ╦┌─┐┬  ┌─┐┌─┐┌┬┐┌─┐  ┌┬┐┌─┐  ╔═╗┌─┐┌┐┌┌─┐┌─┐┌─┐┬ ┬┌─┐\n"\
                          "║║║├┤ │  │  │ ││││├┤    │ │ │  ║  │ ││││├┤ │ ││  │ │└─┐\n"\
                          "╚╩╝└─┘┴─┘└─┘└─┘┴ ┴└─┘   ┴ └─┘  ╚═╝└─┘┘└┘└  └─┘└─┘└─┘└─┘";

float timer{0};

int main (int argc, char *argv[]) {
  consoleClear();
  std::cout << welcomeText << std::endl;
  
  if(argc > 1)
    checkArgs(argv[1]);
  else
    SetTime();

  std::cout << timer << '\n';

  return 0;
}

std::chrono::seconds durationParse(const std::string& input){
  std::istringstream iss(input);
  int value;
  char unit;

  if(!(iss >> value >> unit)){
    throw std::invalid_argument("Invalid input format. Allowed uses are s, h, m");
  }
  switch (unit) {
  case 's':
    return std::chrono::seconds(value);
    break;
  case 'm':
    return std::chrono::minutes(value);
    break;
  case 'h':
    return std::chrono::hours(value);
    break;
  default:
    return std::chrono::seconds(30);
    break;
  }
}

void SetTime(){
  consoleClear();
  std::cout << "How long would you like to work focused? (10s = 10sec 1m = 1min)\n";
  std::string input;
  std::cin >> input;

  try{
    auto duration = durationParse(input);
    std::cout << "Duration: " << duration.count() << std::endl;
  } catch (const std::invalid_argument& e){
    std::cerr << "[ ERROR ]: " << e.what() << std::endl;
  }
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
