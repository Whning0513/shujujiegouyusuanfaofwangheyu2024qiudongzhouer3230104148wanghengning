# 默认目标：编译并运行
all: run

# 编译并运行主程序
run: evaluator
	./evaluator

# 编译 evaluator 可执行文件
evaluator: main.cpp
	g++ -o evaluator main.cpp -O2

# 编译 LaTeX 报告
report: report.tex
	xelatex report.tex
	xelatex report.tex  # 第二次运行以生成目录和交叉引用
	rm -f *.aux *.log   # 删除中间文件

# 清理生成的所有文件
clean:
	rm -f evaluator *.aux *.log *.pdf *.out
