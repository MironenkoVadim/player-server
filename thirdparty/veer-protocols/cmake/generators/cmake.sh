#!/bin/bash

set -o errexit -o pipefail -o noclobber -o nounset

# Test if getopt exists
command -v getopt >/dev/null 2>&1 || { echo "can't execute getopt";  exit 1; }

# Test if getopt works
! getopt --test 2> /dev/null
[[ ${PIPESTATUS[0]} -ne 4 ]] && { exit 2; }

# List of available options
OPTIONS=g:t:qcfs:b:o:
LONGOPTS=generator:,type:,qtcreator,cmake,force,source-dir:,build-dir:,output-dir:

# Parse options
! PARSED=$(getopt --options=$OPTIONS --longoptions=$LONGOPTS --name "$0" -- "$@")
[[ ${PIPESTATUS[0]} -ne 0 ]] && exit 3

# Read getopt's output to handle the quoting right
eval set -- "$PARSED"

# Default generator
[ -x "$(command -v make)" ] && GENERATOR="Unix Makefiles"
[ -x "$(command -v ninja)" ] && GENERATOR=Ninja

# Build types list separated with comma
TYPES="Release"

# Force destructive actions
FORCE="n"

# Default source directory is two levels upper
SOURCE_DIR="$(dirname -- "$(dirname -- "$(pwd)")")"

# Default build directory is _build
BUILD_DIR="${SOURCE_DIR}/_build"

# Default output directory is _output
OUTPUT_DIR="${SOURCE_DIR}/_output"

while true; do
	case "$1" in
		-g|--generator)
			GENERATOR="$2"
			shift 2
			;;
		-t|--types)
			TYPES="$2"
			shift 2
			;;
		-f|--force)
			FORCE="y"
			shift
			;;
		-s|--source-dir)
			SOURCE_DIR="$2"
			shift 2
			;;
		-b|--build-dir)
			BUILD_DIR="$2"
			shift 2
			;;
		-o|--output-dir)
			OUTPUT_DIR="$2"
			shift 2
			;;
		--)
			shift
			break
			;;
		*)
			echo "Wrong argument is set"
			exit 3
			;;
	esac
done

if [ "x${GENERATOR}" = "x" ]; then
	echo "Build command is not found"
	exit 1
fi

CMAKE_ARGS=""
[ ${#@} -gt 0 ] && CMAKE_ARGS=${@}

[ ! -f "${SOURCE_DIR}/CMakeLists.txt" ] && { echo "Source directory does not contain CMakeLists.txt"; exit 4; }

if grep -i ^"project.*fortran" "${SOURCE_DIR}/CMakeLists.txt" >/dev/null 2>&1 ; then
	if [ -x "$(command -v make)" ]; then
		GENERATOR="Unix Makefiles"
	else
		echo "Projects with Fortran sources need Make to build"
		exit 5
	fi
fi

export GENERATOR
export SOURCE_DIR
export BUILD_DIR
export OUTPUT_DIR
export CMAKE_ARGS
export FORCE

generate_configuration() {
	local BUILD_TYPE="${!#}"
	local BUILD="$BUILD_TYPE"

	case "$BUILD_TYPE" in
		qtNone)
			BUILD="unknown"
			BUILD_TYPE="None"
			;;
		qtDebug)
			BUILD="debug"
			BUILD_TYPE="Debug"
			;;
		qtRelease)
			BUILD="release"
			BUILD_TYPE="Release"
			;;
		qtProfile)
			BUILD="profile"
			BUILD_TYPE="Profile"
			;;
	esac

	GEN_DIR="${BUILD_DIR}/${BUILD}"

	if [ -d "${GEN_DIR}" ]; then
		if [ "x${FORCE}" == "xy" ]; then
			rm -rf "${GEN_DIR}"
		else
			echo "Build directory '${GEN_DIR}' already exists. Use --force to remove this directory or do it manually"
			return
		fi
	fi

	cmake -B"${GEN_DIR}" -H"${SOURCE_DIR}" -G "${GENERATOR}" -DCMAKE_INSTALL_PREFIX="${OUTPUT_DIR}" -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" ${CMAKE_ARGS}
}

export -f generate_configuration
set -f

BUILD_TYPES=(${TYPES//,/ })

for i in "${!BUILD_TYPES[@]}"; do
	case ${BUILD_TYPES[i]} in
		None|Debug|Release|Profile|RelWithDebInfo|MinSizeRel|qtNone|qtDebug|qtRelease|qtProfile)
			true
			;;
		*)
			echo "Wrong CMake build type. Possible value are:"
			echo "None,Debug,Release,Profile,RelWithDebInfo,MinSizeRel,qtNone,qtDebug,qtRelease,qtProfile"
			exit 6
			;;
	esac
done

# Try to work in parallel
if [ -x "$(command -v parallel)" ]; then
	PV=$(parallel --version | head -n 1 | awk '{ print $3; }')
	if [ "$PV" -lt "20131121" ]; then
		parallel --delay 2 -r generate_configuration ::: "${BUILD_TYPES[@]}"
	elif [ "$PV" -lt "20141023" ]; then
		parallel --delay 2 -r --no-notice generate_configuration ::: "${BUILD_TYPES[@]}"
	else
		parallel --delay 2 -r --will-cite generate_configuration ::: "${BUILD_TYPES[@]}"
	fi
else
	for T in "${BUILD_TYPES[@]}"; do generate_configuration "${T}"; done
fi

