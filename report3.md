#report 3
##1.Task1
###系统日志信息

    首先对记录组件进行定义：
    NS_LOG_COMPONENT_DEFINE ("ThirdScriptExample");
    
    然后设置日志级别为：
    LogComponentEnable("UdpEchoClientApplication",LOG_LEVEL_ALL);
    LogComponentEnable("UdpEchoServerApplication",LOG_LEVEL_INFO);
    
    运行结果如下所示：
![](http://ww4.sinaimg.cn/mw1024/e5334a89gw1f5fubiwnc9j20na0kdwsz.jpg)
![](http://ww4.sinaimg.cn/mw1024/e5334a89gw1f5fubqslxvj20ki06aae5.jpg)


##2.Task2
###Tracing的两种信道文件

    在Simulator::Run()前，添加下面的代码：

    AsciiTraceHelper ascii;
    pointToPoint.EnableAsciiAll (ascii.CreateFileStream ("ns3-lec2-project2-1p2p.tr"));
    csma.EnableAsciiAll (ascii.CreateFileStream ("ns3-lec2-project2-1csma.tr"));

    pointToPoint.EnablePcapAll ("ns3-lec2-project2-1");
    phy.EnablePcap ("ns3-lec2-project2-1", apDevices.Get (0));
    csma.EnablePcap ("ns3-lec2-project2-1", csmaDevices.Get (0), true);

  
    首先声明一个AsciiTraceHelper对象，分别用p2p信道和csma信道对其激活，生成p2p信道的tr文件和csma信道的tr文件。 
    输出三种信道的pcap文件。
![](http://ww3.sinaimg.cn/mw1024/e5334a89gw1f5fv1tbyjaj20dh057aat.jpg)
    

##3.Task3
###PyViz截图

    在所需运行脚本后加 --vis，既可出现PyViz界面，从界面中可以看出，wifi的STA节点时匀速移动，AP节点固定不动。
![](http://ww3.sinaimg.cn/mw1024/e5334a89gw1f5fubyl5ibj20z60dhn5t.jpg)    


##4.Task4
###Wireshark查看文件截图

    在所要查看的pacp文件右击，选择用wireshark打开，可以看到分析结果：

![](http://ww2.sinaimg.cn/mw1024/e5334a89gw1f5fvp45nn8j20kj0g1ah5.jpg)

##5.Task5
###Matlab表格

##6.Task6
###形成安装步骤文档
####PyViz安装步骤
    1）PyViz安装依赖包
    sudo apt-get install python-dev python-pygraphviz python-kiwi python-pygoocanvas python-gnome2 python-rsv
    
    2）PyViz使用前准备
    在程序中包含：
    CommandLine cmd;
    cmd.Prase (argc,argv);
    
    3）PyViz使用
    在运行脚本的语句后面加入参数 –vis

####Wireshark安装步骤


    
