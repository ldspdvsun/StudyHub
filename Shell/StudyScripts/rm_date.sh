#!/bin/bash

# After the backup is complete, check whether the number of files is correct 

if [ $# -ne 2 ]
then
	echo "Args error! Please input 2 args: "
	exit
fi

# Check whether is a directory
if [ -d $1 ]
then
	echo
else
	echo "1st arg is not a directory!"
fi

TOTAL=$(ls -l $1 |grep ^-|wc -l)
# echo $TOTAL

if [ $TOTAL -ne $2 ];
then
	echo "The number of backup file is error!"
	exit
else
	echo
fi

NOW_DATE=$(date +%y%m%d)
BEF_DATE=$((NOW_DATE-1))

find $1 -type f -name "*$BEF_DATE*" -delete
