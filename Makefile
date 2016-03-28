
CC = g++
CPPFLAGS = -std=c++11 -g -Wall
LIB = -lprotobuf -lprotoc

objects = java_pojo_plugin.o

all:javaPojoPlugin proto

javaPojoPlugin : $(objects)
	    $(CC) $(CPPFLAGS) $(objects) $(LIB) -o javaPojoPlugin 

proto:
	protoc --plugin=protoc-gen-POJO=javaPojoPlugin --POJO_out=./ ./BaseMessage.proto

.PHONY clean:

clean:
	rm javaPojoPlugin *.o

