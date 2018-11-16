./node_modules/.bin/tsc
if [ $? != 0 ]; then
	exit 1
fi

./node_modules/.bin/jest
if [ $? != 0 ]; then
	exit 1
fi