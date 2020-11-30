#
# Author:     Oliver Blaser
#
# Date c:     29.11.2020
# Date e:     29.11.2020
#

titleColor=94
ec=0

{
    echo -e "\033[${titleColor}m-====# cmake #====-\033[39m" &&
    cmake . &&
    echo -e "\033[${titleColor}m-====# make #====-\033[39m" &&
    make
} ||
{
    ec=$?
}

echo -e "\033[${titleColor}m-====# end build #====-\033[39m"

if [ $ec == 0 ]
then
    echo -e "\033[92mdone\033[39m"
else
    echo -e "\033[91mERROR\033[39m code: ${ec}"
fi

exit $ec
