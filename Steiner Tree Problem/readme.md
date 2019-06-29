# Steiner Tree

## Introduce
This project is to solve steiner tree problem by using Heuristic Algorithms. In the project, there are two solutions: *GA* and *RandomSlack*.

## Compiling and Running Environment
- Ubuntu 18.04
- g++ version 7.4.0

## Directory
+-- build   
|&nbsp; &nbsp; &nbsp; &nbsp; +--main &nbsp; &nbsp; &nbsp; &nbsp;//Executable file  
+-- data   
|&nbsp; &nbsp; &nbsp; &nbsp; +-- *.stp   
+-- include    
|&nbsp; &nbsp; &nbsp; &nbsp;+-- Graph.hpp   
|&nbsp; &nbsp; &nbsp; &nbsp;+-- GA.hpp   
|&nbsp; &nbsp; &nbsp; &nbsp;+-- RandomSlack.hpp   
+-- src   
|&nbsp; &nbsp; &nbsp; &nbsp;+-- GA.cpp   
|&nbsp; &nbsp; &nbsp; &nbsp;+-- Graph.cpp   
|&nbsp; &nbsp; &nbsp; &nbsp;+-- main.cpp    
|&nbsp; &nbsp; &nbsp; &nbsp;+-- RandomSlack.cpp   
+-- Makefile   
+-- readme.md   
+-- Report.pdf   
+-- result_GA.md&nbsp; &nbsp; &nbsp; &nbsp;//The result of Algorithm GA  
+-- result_RS.md&nbsp; &nbsp; &nbsp; &nbsp;//The result of Algorithm RandomSlack     
+-- result.xlsx         

## How to run
```shell
$ cd demo
$ make
$ cd bulid
$ ./main
```

## Attention
- Please don't change the directory.
- You'll be asked to enter the filename of the data **without format**.

## Thanks to 
- [GA Introduce](https://www.jianshu.com/p/ae5157c26af9)
- [GA Example](https://www.cnblogs.com/bnuvincent/p/5265637.html)
- [Climbing Introduce](https://blog.csdn.net/shaguabufadai/article/details/71717436)

