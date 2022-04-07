llvm-profdata merge -output=triangle.profdata triangle-*.profraw
llvm-cov show -instr-profile=triangle.profdata ./triangle 
