phase2: main.o utility.o shmmgr.o
	gcc -o phase2 main.o utility.o shmmgr.o

main.o: main.c
	gcc -c main.c

utility.o: utility.c
	gcc -c utility.c

shmmgr.o: shmmgr.c
	gcc -c shmmgr.c

prn:
	pr -n main.c > main.prn
	pr -n utility.c > utilityc.prn
	pr -n utility.h > utilityh.prn
	pr -n shmmgr.c > shmmgrc.prn
	pr -n shmmgr.h > shmmgrh.prn
	pr -n structures.h > structuresh.prn

clean:
	rm *.o
