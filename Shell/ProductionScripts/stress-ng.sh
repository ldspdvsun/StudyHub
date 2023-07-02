echo start: `date`

for ((i=1;i<=10;i++))
do
	echo "The next number is $i"
	pwd
	sleep 1
	ls
	sleep 1
	pwd
	echo $(date +'%Y-%m-%d %H:%M:%S')
	
done

echo end: `date`

