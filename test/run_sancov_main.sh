echo "test xmllint with sancov"

main="../bin/sancov_main"
target="../libxml2/xmllint"
input_dir="../libxml2/test/"
dir="output/libxml2/"
output_dir="${dir}"

if [ $1 -eq "350" ];
then
	output_dir="${dir}issue350/"
elif [ $1 -eq "243" ];
then
	output_dir="${dir}issue243/"
elif [ $1 -eq "311" ];
then
	output_dir="${dir}issue311/"
fi

rm -rf $output_dir*
mkdir ${output_dir}pass
mkdir ${output_dir}fail
mkdir ${output_dir}tout

ASAN_OPTIONS=coverage=1 $main $input_dir $output_dir $target

