all: main

main: main.o expression_evaluator.o
	g++ -o main main.o expression_evaluator.o

main.o: main.cpp
	g++ -c main.cpp

expression_evaluator.o: expression_evaluator.h
	g++ -c expression_evaluator.h

clean:
	rm -f *.o main *.aux *.log *.pdf

report: report.tex
	xelatex report.tex
