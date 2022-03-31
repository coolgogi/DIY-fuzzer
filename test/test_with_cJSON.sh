echo "test jsondump input : cJSON"

main="../bin/main"
target="../jsmn/jsondump"
input_dir="../cJSON/fuzzing/inputs/"
output_dir="output/cJSON/"

rm $output_dir*.bcov
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 $main $input_dir $output_dir $target -bcov
