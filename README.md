# cMIPS
这是课程高级计算机体系结构的project，要求使用C语言完成mips指令功能，并且指令条数不少于50。


# 模块功能介绍
- register模块，主要定义35个寄存器和1KB"内存"。  
- instruction模块，包含所有完成mips指令功能的函数。  
- compiler模块，主要有两个函数：CompileMIPS和Instruction2Binary。CompileMIPS读取mips代码文件，将指令解析为若干参数，通过Instruction2Binary函数将指令编译为二进制，并将二进制写入"内存"。  
- decode模块，通过PC从"内存"中读取32位mips指令码，解析指令并执行相关函数。  
- util模块，包含常用函数。  
- test模块，测试工程功能

