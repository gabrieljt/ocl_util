all:
	g++ main.cpp oclutil.cpp `pkg-config --libs opencv` -lamdocl64 -o oclutil
clean:
	rm oclutil
