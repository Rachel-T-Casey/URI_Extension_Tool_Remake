
CC = gcc
CXX = g++
RM = rm -f
OutputName = Output
# Root-config requires root framework
CPPFLAGS = -Wall -g $(shell root-config --cflags)
LDFLAGS = -g $(shell root-config --ldflags)
LDLIBS = $(shell root-config --libs)

SourceFiles = Main.cpp Request.cpp RequestExtender.cpp
Objects = $(subst .cpp,.o,$(SourceFiles))

all: Output

Output: $(Objects)
	$(CXX) $(LDFlags) -o  $(OutputName) $(Objects) $(LDLIBS)

depend: .depend

.depend: $(SourceFiles)
	$(RM) ./.depend	
	$(CXX) $(CPPFlags) -M $^>>./.depend;

clean:
	$(RM) *$(Objects)

cleanAll:
	$(RM) *$(Objects) Output
include .depend
