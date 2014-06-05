#/***************************************************
# File Name:	makefile
# Abstract:
# Author:	zhangzhelucky
# Update History:
#
# 2014-04-08	Start this file
#
#
#****************************************************/

FLAGS		:=	-O -Wall -g  -DNDEBUG
OBJECTS		:=	log.o  raw2data.o moduls.o event.o

raw2data:	$(OBJECTS)
		g++ -o raw2data $(OBJECTS) $(FLAGS)
#		 -mkdir ./log/
		rm -rf *~
		@echo "Done"

raw2data.o:	raw2data.cpp 
		g++ -c -g raw2data.cpp

log.o:		log.cpp log.h
		g++ -c -g log.cpp

event.o:	event.cpp event.h
		g++ -c -g event.cpp

moduls.o:	moduls.cpp moduls.h
		g++ -c -g moduls.cpp



.PHONY:clean
clean:
		rm -fr raw2data $(OBJECTS) *.gch

# run:
# 	./daq

