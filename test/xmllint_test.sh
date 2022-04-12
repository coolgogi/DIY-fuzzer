echo "test xmllint, input : libxml2/test/"

main="../bin/main"
target="../libxml2/xmllint"
input_dir="../libxml2/test/"
output_dir="output/libxml2/"

rm $output_dir*.bcov

#$main $input_dir $output_dir $target -bcov

