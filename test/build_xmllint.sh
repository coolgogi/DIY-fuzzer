echo "build xmllint"

cd ../libxml2

CC='clang' CFLAGS='-g -O2 -fprofile-instr-generate -fcoverage-mapping -Wall -fsanitize=address' CPPFLAGS='-g -O0 -fprofile-instr-generate -fcoverage-mapping -fsanitize=address' ./configure --with-icu
