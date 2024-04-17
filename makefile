EXEC = main

main: main.cc
	g++ main.cc -o ${EXEC}
clean: 
	rm ${EXEC}