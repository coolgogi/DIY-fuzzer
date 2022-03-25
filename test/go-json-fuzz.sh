echo "go-json-fuzz test case"
rm output/go-json-fuzz_output
rm ../bin/branch.bcov
rm -r ../go-json-fuzz/fuzz/corpus/*.bcov
../bin/main ../jsmn/jsondump ../go-json-fuzz/fuzz/corpus/ output/go-json-fuzz_output -bcov 
