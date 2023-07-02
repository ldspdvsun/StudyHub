#!/bin/bash

# echo $1
echo "--------"
now=$(date +%y-%m-%d_%H-%M-%S)
echo${now:0:10}
echo "--------"
# get now date,such as 23030912
NOW_DATE_TWELVE=$(date +%y%m%d)
NOW_DATE_TWENTY_THREE=$(date +%y%m%d%H)

# if now is 12am, delete yesterday 23`s backup
BEF_DATE_TWELVE=$((NOW_DATE_TWELVE-1))

NOW_HOUR=$(date +%H)
echo $NOW_HOUR
echo $BEF_DATE_TWELVE

# if now is 11pm, delete toady 12`s backup
BEF_DATE_TWENTY_THREE=$((NOW_DATE_TWENTY_THREE-11))

if [NOW_HOUR -eq 12];
then
	find $1 -type f -name "*$BEF_DATE_TWELVE*" -delete
fi

if [NOW_HOUR -eq 23];
then
	find $1 -type f -name "*$BEF_DATE_TWENTY_THREE*" -delete
fi
