echo "test xmllint with sancov"

main="../bin/sancov_main"
target="../libxml2/xmllint"
input_dir="../libxml2/test/"
dir="output/libxml2/"
output=${dir}
if [ $1 -eq "350" ];
then
	output="${dir}issue350/"
elif [ $1 -eq "243" ];
then
	output="${dir}issue243/"
elif [ $1 -eq "311" ];
then
	output="${dir}issue311/"
fi


rm -r $output*
mkdir ${output}pass
mkdir ${output}fail
mkdir ${output}tout
ASAN_OPTIONS=coverage=1 $main $input_dir $output_dir $target

