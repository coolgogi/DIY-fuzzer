echo "build xmllint"

cd ../libxml2
make distclean
CFLAGS='-O3 -g -fsanitize=address' CC='clang' ./configure --with-icu

#CFLAGS='-O3 -g -fsanitize=address -fsanitize-coverage=trace-pc-guard' CC='clang'  make
CFLAGS='-ftest-coverage' make
