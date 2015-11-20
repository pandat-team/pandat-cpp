build:
	g++ -std=gnu++0x -Ilib -I/usr/local/include -L/usr/local/lib src/main.cpp lib/pirf/*.cc -lprotobuf -o main

encoder:
	cd proto && protoc *.proto --cpp_out=../lib/pirf

benchmark:
	yes "$(cat test/sample.json)" | ./main | pv -lri60 > /dev/null


run:
	./main
