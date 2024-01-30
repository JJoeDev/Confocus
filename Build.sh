#!/bin/bash

configVal="Debug"

# Loop through args
for arg in "$@"; do
  if [[ $arg == "build="* ]]; then
    configVal="${arg#*=}" # Gets value after =
  elif [[ $arg == "help" ]]; then
    configVal="help"
  else
    configVal=""
  fi
done

if [[ "$configVal" == "help" ]]; then
  echo "=== HELP PAGE ==="
  echo "DBuild.sh can take some arguments"
  echo "[ ARGUMENT ]               | Giving no arguments makes it build the application in debug mode"
  echo "[ ARGUMENT ] build=Release | This arg makes it build in release mode for more speed and no debug symbols"
  echo "[ ARGUMENT ] help          | This is the help page you are looking at"
  exit
fi

folders=("bin" "obj")

for f in "${folders[@]}"; do
  if [ -d "$f" ]; then
    rm -r "$f"
  fi
done

premake5 gmake2

if [[ "$configVal" == "Release" ]]; then
  make -C build/ config=release
else
  echo "===== Remember you can always run ./DBuild.sh help to get help ====="
  make -C build/
fi

read -p "===> BUILD Complete. Run application? [Y/n] " inp
case "$inp" in
  y|Y|"" )
    ./bin/$configVal/Confocus
    ;;
  n|N )
    echo "Executable can be found in ./bin/$configVal/"
    ;;
  * )
    echo "Invalid input. Interperating as N"
    ;;
  esac
