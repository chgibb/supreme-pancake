./node_modules/.bin/tsc

for f in src/*.js
do
	bash scripts/buildReleaseJS.bash $f
	if [ $? != 0 ]; then
		exit 1
	fi
done