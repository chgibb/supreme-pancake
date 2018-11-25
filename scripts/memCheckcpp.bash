#From https://stackoverflow.com/questions/5947742/how-to-change-the-output-color-of-echo-in-linux
Color_Off='\033[0m'   
Yellow='\033[0;33m'
Green='\033[0;32m'

echo -e "\n"
for f in tests/*.out
do
	echo -e "$Yellow$f$Color_Off"
	valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=definite,possible --error-exitcode=1 $f
    echo -e "$Green===============================================================================$Color_Off"
    echo -e "$Green$f Successfully Memchecked$Color_Off"
    echo -e ""
	if [ $? != 0 ]; then
		exit 1
	fi
done