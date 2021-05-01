trap ctrl_c INT
function ctrl_c()
{
	pkill -9 -P $$
}


#  USAGE cores, input_file, compiled_program 

cores=$1
input=$2
who=$3
for((i=0;i<$cores;i++)); do
	./$who $i < $input &
done
wait
