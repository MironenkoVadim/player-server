#!/bin/bash

PROJECT=$(grep -i "^Project" "$(dirname -- "$(dirname -- "$(pwd)")")/CMakeLists.txt" | awk -F'[( )]' '{print $2}')

"$(dirname $0)/cmake.sh" -f -t qtDebug

