echo start: `date`

for ((i=1;i<=10;i++))
do
	echo "The next number is $i"
	sleep 1
	echo $(date)
done

echo end: `date`

