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

BINARY_PATH='/csproj/bin/Release/netcoreapp1.1/project2.dll'

ARR=''
META_FILE=''
KEY_FILE=''
PRIMARY_USER=''

function usage() {
	echo -e "USAGE: ${0} -u USERNAME -k KEY_FILE [-m META_FILE] [-d | -h] [COMMAND] [FILE]"
	echo -e "Commands: "
	echo -e "\tgen"
	echo -e "\tup"
	echo -e "\tdown"
	echo -e "\tup"
}

function fileExists() {
	if [[ ! -e "${1}" ]]; then
		echo -e "${RED}File ${1} does not exist${END}"
		exit 1
	fi
}

function debug() {
	echo -e "${YELLOW}[DEBUG] $1${END}"
}

function error() {
	echo -e "${RED}[ERROR] $1${END}"
}

function split() {
	TEXT=$1
	SEPARATOR=$2

	if [[ $DEBUG -eq $TRUE ]]; then
		debug $TEXT
		debug $SEPARATOR
	fi

	IFS=$SEPARATOR read -ra ARR <<< "${TEXT}"
}

DEPS=('dotnet' 'jq' 'cat' 'less' 'git' 'sed' 'drive')

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

drive about > /dev/null 2>&1
if [[ $? -ne 0 ]]; then
	error "Something is wrong with your Drive configuration"
	drive about
fi

while getopts "hds:k:m:u:" O; do
	case "${O}" in
		h)
			usage
			exit 0
			;;
		d)
			DEBUG=$TRUE
			;;
		u)
			PRIMARY_USER=$OPTARG
			;;
		k)
			KEY_FILE=$OPTARG
			;;
		m)
			META_FILE=$OPTARG
			;;
		s)
			split $OPTARG ','
			SHARED_USERS=("${ARR[@]}")
			;;
		*)
			usage
			exit 1
			;;
	esac
done
shift $((OPTIND - 1))

COMMAND=$1
FILE=$2

if [[ -z $COMMAND || -z $FILE ]]; then
	error "A command and file are required"
	usage
	exit 1
fi

if [[ -z $PRIMARY_USER ]]; then
	error "user must be provided with the u flag"
	usage
	exit 1
fi

if [[ -z $KEY_FILE ]]; then
	error "A key file must be provided with the k flag"
	usage
	exit 1
fi

fileExists $FILE

if [[ $COMMAND == 'upload' ]]; then
	SHARE_FLAG=""

	if [[ "${#SHARED_USERS[@]}" -ne 0 ]];then
		for USER in "${SHARED_USERS[@]}"; do
			SHARE_FLAG="${SHARE_FLAG} -r ${USER}"
		done
	fi

	dotnet "${BINARY_PATH}" -i "${FILE}" -o "${FILE}.enc" -u $PRIMARY_USER -k "${KEY_FILE}" $SHARE_FLAG

	fileExists "${FILE}.enc.meta"
	fileExists "${FILE}.enc"

	drive push "${FILE}.enc" "${FILE}.enc.meta"

	if [[ -n $SHARE_FLAG ]]; then
		drive share -with-link "${FILE}.enc" "${FILE}.enc.meta" > /dev/null 2>&1

		echo "File URL:"
		drive url "${FILE}.enc"

		echo "Meta URL:"
		drive url "${FILE}.enc.meta"
	fi
elif [[ $COMMAND == 'decrypt' ]]; then
	DECRYPTED_FILE=$(basename $FILE .enc)
	dotnet $BINARY_PATH -i $FILE -o $DECRYPTED_FILE -u $PRIMARY_USER -m $META_FILE -k "${KEY_FILE}"
else
	error "Command is not valid"
	usage
	exit 1
fi
