#!/bin/bash

print_help(){
	echo "Usage:"
	echo "	$0 base --- make base cbp"
}

check_env(){
    if [ $(id -u) != "0" ]; then
        echo "Error: You must be root to run this script"
        exit 1
    fi
}

make_cbp(){
	PROJECT=$1

	mkdir -p src/cbp
	cd src/cbp
	cmake -DCMAKE_BUILD_TYPE=Debug -B. -H../ -G "CodeBlocks - Unix Makefiles"	
	cd ../../
}

case $1 in
	GxLog)
		make_cbp $1
		;;
	all)
		make_cbp GxLog
		;;
	*)
		print_help
		;;
esac
