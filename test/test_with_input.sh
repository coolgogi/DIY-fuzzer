echo "test jsondump input : small corpus"

main="../bin/main"
target="../jsmn/jsondump"
input_dir="input/corpus/"
output_dir="output/corpus/"

rm $output_dir*.bcov
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 $main $input_dir $output_dir $target -bcov
