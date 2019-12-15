# MPI-based makefile using mpic++ and mpicc

CC =            mpicc -m64
CPP =           mpic++ -m64
CCFLAGS =       -g -O -I/home/jhunior/mrmpi/src/
LINK =          mpic++
LINKFLAGS =     -g -O
USRLIB =        /home/jhunior/mrmpi/src/libmrmpi_mpicc.a
SYSLIB =

# Targets

all:    mr-matmul

mr-matmul:      mr-matmul.o $(USRLIB)
	$(LINK) $(LINKFLAGS) mr-matmul.o $(USRLIB) $(SYSLIB) -o mr-matmul

mr-matmul2:     mr-matmul2.o $(USRLIB)
	$(LINK) $(LINKFLAGS) mr-matmul2.o $(USRLIB) $(SYSLIB) -o mr-matmul2

mr-fault: 	mr-matfault.o $(USRLIB)
	$(LINK) $(LINKFLAGS) mr-matfault.o $(USRLIB) $(SYSLIB) -o mr-matfault

mr-fault2: 	mr-matfault2.o $(USRLIB)
	$(LINK) $(LINKFLAGS) mr-matfault2.o $(USRLIB) $(SYSLIB) -o mr-matfault2

clean:
	rm *.o mr-matmul

clean2:
	rm *.o mr-matmul2

clean3:
	rm *.o mr-matfault

clean4:
	rm *.o mr-matfault2

%.o:%.c
	$(CC) $(CCFLAGS) -c $<
