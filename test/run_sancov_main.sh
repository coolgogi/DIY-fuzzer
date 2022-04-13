echo "test xmllint with sancov"

main="../bin/sancov_main"
target="../libxml2/xmllint"
i_dir="input/issue/"
dir="output/libxml2/"
input_dir=""
output_dir="${dir}"

if [ $1 -eq "350" ];
then
	output_dir="${dir}issue350/"
	input_dir="${i_dir}350/"	
elif [ $1 -eq "243" ];
then
	output_dir="${dir}issue243/"
#	input_dir="${i_dir}243/"	
	input_dir="../libxml2/test/"
elif [ $1 -eq "311" ];
then
	output_dir="${dir}issue311/"
	input_dir="${i_dir}311/"	
fi

ASAN_OPTIONS=coverage=1 $main $input_dir $output_dir $target

