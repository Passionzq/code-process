# Steiner Tree

## Introduce
This project is to solve steiner tree problem by using Heuristic Algorithms. In the project, there are two solutions: *GA* and *RandomSlack*.

## Data Fromat
-	The first line is “33D32945 STP File, STP Format Version 1.0” which could be ignored
-	Section comment, section graph and section terminals are following. 
-	Section comment could be ignored. 
-	Section graph describe the undirected graph. The first two lines in this section show the number of nodes and number of edges. And then there are several lines. “E a b c” (a, b, c are integers) means that there is an edge between vertex a and vertex b with distance c 
-	Section terminals describe the set S. The first line shows the number of vertices in S. “T a” (a is an integer) means that a is in set S.


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

