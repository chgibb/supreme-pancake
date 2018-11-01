for f in tests/*.out
do
	./$f
	if [ $? != 0 ]; then
		exit 1
	fi
done