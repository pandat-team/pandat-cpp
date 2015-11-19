build:
	g++ -Ilib -I/usr/local/include -L/usr/local/lib src/main.cpp lib/pirf/*.cc -lprotobuf -o main

encoder:
	cd proto && protoc *.proto --cpp_out=../lib/pirf
run:
	./main
