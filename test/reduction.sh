echo "test case reduction"

target="../bin/test-case_reduction"
input_dir="../go-json-fuzz/fuzz/corpus/"
output_dir="output/corpus/"
N=178

rm output/corpus/SA/*

$target $input_dir $output_dir $N
