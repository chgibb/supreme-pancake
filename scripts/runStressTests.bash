for f in tests/stress/*.js
do
	echo -e "$Yellow$f$Color_Off"
    node $f
    if [ $? != 0 ]; then
		exit 1
	fi
done