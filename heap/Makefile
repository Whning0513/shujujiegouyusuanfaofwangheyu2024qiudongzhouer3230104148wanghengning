# 编译C++代码并加入-O2优化
all: heapsort
	./heapsort

heapsort: test.cpp
	g++ -o heapsort test.cpp -O2

# 使用XeLaTeX编译report.tex
report: report.tex
	xelatex report.tex

# 清理生成的文件
clean:
	rm -f heapsort *.aux *.log *.pdf