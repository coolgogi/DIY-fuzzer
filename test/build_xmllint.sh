echo "build xmllint"

cd ../libxml2

make clean

if [ $1 -eq "350" ];
then
	git checkout 4adb7677635b2c8d764767f6b484de1b26217f5d
	CC='clang' CFLAGS='-g -fsanitize=address -fsanitize-coverage=edge,trace-pc-guard' CPPFLAGS='-g -fsanitize=address -fsanitize-coverage=edge,trace-pc-guard' ./configure --disable-shared --with-icu
	make
elif [ $1 -eq "243" ];
then
	git checkout 5465a8e57fe620ceb8efa534e1d6790f423d6bba
	CC='clang' CFLAGS='-g -fsanitize=address -fsanitize-coverage=edge,trace-pc-guard' ./configure --disable-shared
	make
elif [ $1 -eq "311" ];
then
	git checkout dea91c97debeac7c1aaf9c19f79029809e23a353
	CC='clang' CFLAGS='-g -O0 -fsanitize=address -fsanitize-coverage=edge,trace-pc-guard' CXXFLAGS='-g -O0 -fsanitize=address -fsanitize-coverage=edge,trace-pc-guard' ./configure --disable-shared --prefix=$(pwd)/
	make -j10
fi
