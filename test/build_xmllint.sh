echo "build xmllint"

cd ../libxml2

make clean

if [ $1 -eq "350" ];
then
	git checkout 4adb7677635b2c8d764767f6b484de1b26217f5d
	CC='clang' CFLAGS='-g -O2 -fprofile-instr-generate -fcoverage-mapping -Wall -fsanitize=address -fsanitize-coverage=edge,trace-pc-guard' CPPFLAGS='-g -O0 -fprofile-instr-generate -fcoverage-mapping -fsanitize=address -fsanitize-coverage=edge,trace-pc-guard' ./configure --with-icu
	make
elif [ $1 -eq "243" ];
then
	git checkout 5465a8e57fe620ceb8efa534e1d6790f423d6bba
	CC='clang' CFLAGS='-g -fsanitize=address' ./configure
	make
elif [ $1 -eq "311" ];
then
	git checkout dea91c97debeac7c1aaf9c19f79029809e23a353
	CC='clang' CFLAGS='-g -O0 -fsanitize=address' CXXFLAGS='-g -O0 -fsanitize=address' ./configure --prefix=$(pwd)/
	make -j10
fi
