语义分析

将函数的参数长度+变量长度存入函数表中

参数类型也存进去，之后进行调用时参数类型比对

四元式生成

在函数表中加入label信息，四元式生成查询时已经保证了无错误，需要携带函数名进行查询，计划使用全局变量来控制

在函数调用时，先做现场保护，然后压参数，然后分配变量所需空间，然后跳转

cache Para + Call

error handle

value optimization: another new function to calculate const and numbers in compile time

optimize "mul 1 and add 0" in pcode result
