# 自适应Huffman编码压缩
## 运行环境
    Linux g++
## 如何运行
- 进入对应文件夹   
- 编译   
`g++ Huffman.cpp main.cpp -o main`   
- 运行:   
    1.压缩:   
    `./main -c <filename>`   
    2.解压:   
    `./main -d <filename>`

## 注意
应先使用本程序进行压缩,得到 `filename.bin` ,之后再对其进行解压缩,得到 `filename.restore`
