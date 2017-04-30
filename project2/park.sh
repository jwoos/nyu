#!/usr/bin/env bash

END="\033[0m"
BLACK="\033[0;30m"
WHITE="\033[0;37m"
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
BLUE="\033[0;34m"

TRUE=1
FALSE=0

DEBUG=$FALSE
VERBOSE=$FALSE
DRY_RUN=$FALSE

function usage() {
	echo -e "USAGE: ${0} [COMMAND] [FILE]"
	echo -e "Commands: "
	echo -e "\tgen"
	echo -e "\tup"
	echo -e "\tdown"
	echo -e "\tup"
}

DEPS=('jq' 'cat' 'less' 'git' 'sed' 'drive')

for DEP in "${DEPS[@]}"; do
	type $DEP > /dev/null 2>&1

	if [[ $? -ne 0 ]]; then
		echo -e "${RED}MISSING DEPENDENCY: ${DEP}${END}"
		echo -e "Please install ${DEP} and try again"
		exit 1
	fi
done

if [[ $# -eq 0 ]]; then
	usage
	exit 1
fi

while getopts "hdxvs:" O; do
	case "${O}" in
		h)
			usage
			exit 0
			;;
		x)
			DRY_RUN=$TRUE
			;;
		v)
			VERBOSE=$TRUE
			;;
		d)
			DEBUG=$TRUE
			;;
		s)
			IFS=',' read -ra SHARE_USERNAMES <<< "${OPTARG}"
			for USER in "${SHARE_USERNAMES[@]}"; do
				echo $USER
			done
			;;
		*)
			usage
			exit 0
			;;
	esac
done
shift $((OPTIND - 1))

COMMAND=$1
FILE=$2

if [[ -z $COMMAND || -z $FILE ]]; then
	usage
	exit 1
fi
