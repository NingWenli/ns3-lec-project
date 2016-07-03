# report4
##1.Task1
###仿真拓扑
1、搭建拓扑：两个wifi网络，各有6个sta，1个ap；实现两个wifi网络之间的通信<br>

    设计思路：首先建立两个wifi网络，各包含6个sta和1个ap
              再建立一个wifi网络，将先前建立的两个wifi网络中的ap分别作为该网络的sta和ap
2、场景范围：500m*500m

    设置场景范围
    mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel","Bounds", RectangleValue (Rectangle (0, 500, 0, 500)));
    mobility.Install (wifi1StaNodes);
    mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel","Bounds", RectangleValue (Rectangle (0, 500, 0, 500)));
3、传播模型为：ConstantSpeedPropagationDelayMode

    YansWifiChannelHelper channel1 = YansWifiChannelHelper::Default (); 
    channel1.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
4、Mac类型为：NqosWifiMacHelper（没有QoS保障的Mac层机制）

    NqosWifiMacHelper mac1 = NqosWifiMacHelper::Default ();
5、移动模型为随机游走模型，设定初始位置为两个六边形，边长10m，sta在6个顶点上，ap在六边形中间；两个六边形中心相距50m
![](http://ww4.sinaimg.cn/mw1024/e5334a89gw1f5gv9nfx3uj20er0c3gqs.jpg)
![](http://ww3.sinaimg.cn/mw1024/e5334a89gw1f5gv9lbqa8j20jq04yq4z.jpg)
  
6、packet size为512byte，包间隔为100ms
![](http://ww3.sinaimg.cn/mw1024/e5334a89gw1f5gv9mjcxqj20gu01wdh0.jpg)
##2.Task2
###PyViz截图
![](http://ww1.sinaimg.cn/mw1024/e5334a89gw1f5gv9l7yz2j20i30eiwfy.jpg)
![](http://ww3.sinaimg.cn/mw1024/e5334a89gw1f5gv9m8k8rj20hy0eyabu.jpg)
##3.Task3
###Tracing的两种信道文件

##3.Task3
###Matlab处理后的图表
