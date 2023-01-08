parametrosCompilacao=-Wall #-Wshadow
nomePrograma=calendario

$(nomePrograma): main.o calendario.o
	gcc -o $(nomePrograma) main.o calendario.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

calendario.o: calendario.h calendario.c
	gcc -c calendario.c $(parametrosCompilacao)

clean:
	rm -f *.o ${nomePrograma}