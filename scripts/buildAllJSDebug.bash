./node_modules/.bin/tsc

for f in src/*.js
do
	bash scripts/buildDebugJS.bash $f
	if [ $? != 0 ]; then
		exit 1
	fi
done