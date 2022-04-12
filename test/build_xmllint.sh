echo "build xmllint"

cd ../libxml2

#CC='clang' CFLAGS='-g -O2 -fprofile-instr-generate -fcoverage-mapping -Wall -fsanitize=address -fsanitize-coverage=edge,trace-pc-guard' CPPFLAGS='-g -O0 -fprofile-instr-generate -fcoverage-mapping -fsanitize=address -fsanitize-coverage=edge,trace-pc-guard' ./configure --with-icu

CC='clang' CFLAGS='-g -fsanitize=address -fsanitize-coverage=edge,trace-pc-guard' ./configure --enable-static --disable-shared --with-icu
