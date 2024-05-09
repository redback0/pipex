
if [ $# -lt 4 ]; then
	echo "not enough args"
	exit 0
fi

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m'

rm -f $4
printf "${YELLOW}SHELL PIPES:${NC}\n"
< $1 $2 | $3 > $4
printf "\n${YELLOW}OUTPUT FILE:${NC}\n"
cat -e $4
echo
rm -f $4
printf "${YELLOW}PIPEX:${NC}\n"
./pipex "$1" "$2" "$3" "$4"
printf "\n${YELLOW}OUTPUT FILE:${NC}\n"
cat -e $4
echo
rm -f $4

