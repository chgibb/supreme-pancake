Color_Off='\033[0m'   
Yellow='\033[0;33m'

echo -e "\n"
for f in tests/*.out
do
	echo -e "$Yellow$f$Color_Off"
	./$f
	if [ $? != 0 ]; then
		exit 1
	fi
done