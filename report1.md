# ns3-lec-project
##1.task1
    以Hello-simulator.cc为示例，并在新的要求下完成任务用命令行读入的自己的学号和姓名参数以及输出频率，周期性输出姓名和学号，
    不能使用硬编码。
    
![](http://ww3.sinaimg.cn/mw1024/e5334a89gw1f57qmcwbkzj20gv0bq0v6.jpg)
![](http://ww4.sinaimg.cn/mw1024/e5334a89gw1f57qp3nkcgj20i9063dio.jpg)

    在所给Hello-simulator.cc程序基础上，修改输出函数的传递参数，即一个name字符串，一个id字符串；在一个周期内调用两次类cmd的传
    值函数，输出name和id信息。
    设置输出周期为1s。
    设置输出次数为5。
    
    运行结果如图所示，0s、1s、2s、3s、4s时程序在终端分别输出name和id信息，周期为1s,次数为5。
    

##2.task2
    利用unix实用工具wc(word count)统计输出的总次数。
    
    
![](http://ww2.sinaimg.cn/mw1024/e5334a89gw1f57qmeassbj20gs0243za.jpg)
![](http://ww1.sinaimg.cn/mw1024/e5334a89gw1f57qtdmb9xj20bz0cp75b.jpg)

    首先用"| grep ningwenli"命令筛选出含有终端输出信息的行，并将其写入file.txt文件。
    然后用"wc -l file.txt"命令读出file.txt文件里的行数，并在终端打印显示，如上图所示。
    
    
##3.task3
    利用unix实用工具grep筛选特定信息。
    
![](http://ww1.sinaimg.cn/mw1024/e5334a89gw1f57qmdk8jrj20gy01rjrz.jpg)

    用| grep"+2"命令筛选出在+2s时刻的信息，在终端打印输出，如上图所示。
