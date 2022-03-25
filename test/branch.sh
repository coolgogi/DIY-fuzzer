rm branch.*.sancov
ASAN_OPTIONS=coverage=1 ../bin/branch
ASAN_OPTIONS=coverage=1 ../bin/branch
ASAN_OPTIONS=coverage=1 ../bin/branch
ASAN_OPTIONS=coverage=1 ../bin/branch
sancov -symbolize branch.*.sancov ../bin/branch
