
if [ $# -lt 4 ]; then
	echo "not enough args"
	exit 0
fi

< $1 $2 | $3 > $4
./pipex $1 $2 $3 $4

