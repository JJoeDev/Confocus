#include <asm-generic/ioctls.h>
#include <iomanip>
#include <ios>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <sys/ioctl.h>
#include <unistd.h>

#if defined(_WIN32) || defined(_WIN64)
#define CLS "cls"
#else
#define CLS "clear"
#endif

/*
* FEATURES TO IMPLEMENT!
* Set custom time
* Show simple graphics while timer is going (Time left + Progress bar)
* Show simple graphics + controls when not in timer mode
*/

inline void consoleClear() { system(CLS); }

// Get Timer (in app)
void SetTime(const char* message);
std::chrono::seconds durationParse(const std::string& input);

// Start Timer
void StartTimer();

// Terminal size (from sys/ioctl.h)
struct winsize size;

const char* WELCOME_TEXT = R"(
  ╦ ╦┌─┐┬  ┌─┐┌─┐┌┬┐┌─┐  ┌┬┐┌─┐  ╔═╗┌─┐┌┐┌┌─┐┌─┐┌─┐┬ ┬┌─┐
  ║║║├┤ │  │  │ ││││├┤    │ │ │  ║  │ ││││├┤ │ ││  │ │└─┐
  ╚╩╝└─┘┴─┘└─┘└─┘┴ ┴└─┘   ┴ └─┘  ╚═╝└─┘┘└┘└  └─┘└─┘└─┘└─┘
  )";

const char* BREAK_TEXT = R"(
 _____     _                  _                    _    _ 
|_   _|   | |                | |                  | |  | |
  | | __ _| | _____    __ _  | |__  _ __ ___  __ _| | _| |
  | |/ _` | |/ / _ \  / _` | | '_ \| '__/ _ \/ _` | |/ / |
  | | (_| |   <  __/ | (_| | | |_) | | |  __/ (_| |   <|_|
  \_/\__,_|_|\_\___|  \__,_| |_.__/|_|  \___|\__,_|_|\_(_)
)";

std::chrono::seconds timer{0};

int main () {
  consoleClear();

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

  std::cout << WELCOME_TEXT << std::endl;
  std::cout << "\nTime format list\nSeconds: 10s\nMinutes: 7m\nHours: 12h\nCurrently no chaining time (1m 15s)\n\n";
  
  SetTime("How long would you like to work?");
  std::cout << timer.count() << " seconds\n";

  StartTimer();

  return 0;
}

void StartTimer(){
  auto deltaStart = std::chrono::steady_clock::now();
  auto end = deltaStart + timer;

  consoleClear();

  while(std::chrono::steady_clock::now() < end){
    auto now = std::chrono::steady_clock::now();
    auto elapsedSecs = std::chrono::duration_cast<std::chrono::seconds>(now - deltaStart).count();

    float progress = static_cast<float>(elapsedSecs) / static_cast<float>(timer.count());

    int progressWidth = static_cast<int>(progress * size.ws_row);

    // Progress Bar
    std::cout << "\r[";
    for(int i = 0; i < progressWidth; ++i){
      std::cout << "=";
    }
    for(int i = progressWidth; i < size.ws_row; ++i){
      std::cout << " ";
    }
    std::cout << "] " << std::fixed << std::setprecision(1) << (progress * 100.0f) << "%";
    std::cout.flush();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

  std::cout << "\n\n\n" << BREAK_TEXT << std::endl;
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

void SetTime(const char* message = ""){
  //consoleClear();
  std::cout << message << '\n';
  std::string input;
  std::cin >> input;

  try{
    timer = durationParse(input);
  } catch (const std::invalid_argument& e){
    std::cerr << "[ ERROR ]: " << e.what() << std::endl;
  }
}
