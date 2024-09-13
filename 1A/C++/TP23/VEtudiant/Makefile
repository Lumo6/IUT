DOX=doxygen
CC=g++
CFLAGS=-std=c++17 -D _DEBUG -g
LDFLAGS=
IntDir=int/
OutDir=out/

.PHONY: directories $(IntDir) $(OutDir) clean clear all default doc

default: test streaming

clean:
	rm -rf $(IntDir)

clear: clean
	rm -rf $(OutDir)
	rm -rf doc-test/
	rm -rf doc-streaming/

all: test streaming doc

doc: doc-test doc-streaming

directories: $(IntDir) $(OutDir)

$(IntDir):
	mkdir -p $(IntDir)

$(OutDir):
	mkdir -p $(OutDir)

test: $(OutDir) $(IntDir)CircularBuffer.o $(IntDir)CircularBufferError.o $(IntDir)prog.o
	$(CC) -o $(OutDir)test $(IntDir)CircularBuffer.o $(IntDir)CircularBufferError.o $(IntDir)prog.o $(LDFLAGS)

$(IntDir)CircularBuffer.o: $(IntDir) TP\ 23/CircularBuffer.cpp TP\ 23/CircularBuffer.h
	$(CC) -o $(IntDir)CircularBuffer.o -c TP\ 23/CircularBuffer.cpp $(CFLAGS)

$(IntDir)CircularBufferError.o: $(IntDir) TP\ 23/CircularBufferError.cpp TP\ 23/CircularBufferError.h
	$(CC) -o $(IntDir)CircularBufferError.o -c TP\ 23/CircularBufferError.cpp $(CFLAGS)

$(IntDir)prog.o: $(IntDir) TP\ 23/prog.cpp
	$(CC) -o $(IntDir)prog.o -c TP\ 23/prog.cpp $(CFLAGS)

streaming: $(OutDir) $(IntDir)CircularBuffer.o $(IntDir)CircularBufferError.o $(IntDir)Sender.o $(IntDir)TP\ 23\ -\ streaming.o
	$(CC) -o $(OutDir)streaming $(IntDir)CircularBuffer.o $(IntDir)CircularBufferError.o $(IntDir)Sender.o $(IntDir)TP\ 23\ -\ streaming.o $(LDFLAGS)

$(IntDir)Sender.o: $(IntDir) TP\ 23\ -\ streaming/Sender.cpp TP\ 23\ -\ streaming/Sender.h
	$(CC) -o $(IntDir)Sender.o -c TP\ 23\ -\ streaming/Sender.cpp $(CFLAGS)

$(IntDir)TP\ 23\ -\ streaming.o: $(IntDir) TP\ 23\ -\ streaming/TP\ 23\ -\ streaming.cpp
	$(CC) -o $(IntDir)TP\ 23\ -\ streaming.o -c TP\ 23\ -\ streaming/TP\ 23\ -\ streaming.cpp $(CFLAGS)

doc-test: Doxyfile-Test.dox TP\ 23/CircularBuffer.cpp TP\ 23/CircularBuffer.h TP\ 23/CircularBufferError.cpp TP\ 23/CircularBufferError.h TP\ 23/prog.cpp TP\ 23/test.h
	$(DOX) Doxyfile-Test.dox

doc-streaming: Doxyfile.dox TP\ 23/CircularBuffer.cpp TP\ 23/CircularBuffer.h TP\ 23/CircularBufferError.cpp TP\ 23/CircularBufferError.h TP\ 23\ -\ streaming/Sender.cpp TP\ 23\ -\ streaming/Sender.h TP\ 23\ -\ streaming/TP\ 23\ -\ streaming.cpp
	$(DOX) Doxyfile.dox
