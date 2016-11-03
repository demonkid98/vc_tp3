#######################################
# Makefile PBM                        #
#                                     #
# E.B.                                #
#######################################


PROG = kmean
OUT = *.out out.ppm

all : $(PROG)

# Variables for file compilation
CC        =  gcc
CFLAGS    =  -g -Wall
CPPFLAGS  =  -DDEBUG
LDFLAGS   =  -g -lm

kmean: kmean.o Util.o

clean :
	@rm -f *.o

cleanall : clean
	@rm -f $(PROG) $(OUT)
