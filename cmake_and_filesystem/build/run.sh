titleColor=94
ec=0

./build.sh
ec=$?

if [ $ec == 0 ]
then
    echo -e "\033[${titleColor}m-====# run \"\033[37m./cmakeTestPrjExe ${@}\033[${titleColor}m\" #====-\033[39m"
    ./cmakeTestPrjExe "$@"
    ec=$?
    
    if [ $ec != 0 ]
    then
        echo -e "\033[91m-====# ERROR #====-\033[39m"
        echo -e "code: ${ec}"
    fi
fi

exit $ec
