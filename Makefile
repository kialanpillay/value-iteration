CC=g++         
CCFLAGS= -std=c++11 -Wall -g -fsanitize=address -fno-omit-frame-pointer

driver: driver.o value_iteration.o
	$(CC) $(CCFLAGS) driver.o value_iteration.o -o driver

driver.o: driver.cpp
	$(CC) $(CCFLAGS) -c driver.cpp	

value_iteration.o: value_iteration.cpp value_iteration.h
	$(CC) $(CCFLAGS) -c pca.cpp

clean:
	@rm -f *.o && rm -f driver
   
run:
	@./driver

