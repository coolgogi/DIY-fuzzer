echo "test jsondump input : corpus"

main="../bin/sancov_main"
target="../libxml2/xmllint"
input_dir="../libxml2/test/"
output_dir="output/libxml2/"


rm -r $output_dir*
mkdir output/libxml2
mkdir output/libxml2/pass
mkdir output/libxml2/fail
ASAN_OPTIONS=coverage=1 $main $input_dir $output_dir $target

