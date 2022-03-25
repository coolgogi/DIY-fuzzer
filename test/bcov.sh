echo "bcov test case"
rm output/runner_output
rm ../bin/branch.bcov
rm -r input/bcov/*.bcov
rm -r input/bcov/bcov2/*.bcov
rm -r input/bcov/bcov3/*.bcov
rm -r input/bcov/bcov3/bcov4/*.bcov
../bin/main ../bin/branch input/bcov/ output/runner_output -bcov 
