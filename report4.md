# report4
##1.Task1
###仿真拓扑
1、搭建拓扑：两个wifi网络，各有6个sta，1个ap；实现两个wifi网络之间的通信<br>

    设计思路：首先建立两个wifi网络，各包含6个sta和1个ap
              再建立一个wifi网络，将先前建立的两个wifi网络中的ap分别作为该网络的sta和ap
2、场景范围：500m*500m

    设置场景范围
    mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel", "Bounds", RectangleValue (Rectangle (0, 500, 0, 500)));
    mobility.Install (wifi1StaNodes);
    mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel", "Bounds", RectangleValue (Rectangle (0, 500, 0, 500)));
3、传播模型为：ConstantSpeedPropagationDelayModel
    YansWifiChannelHelper channel1 = YansWifiChannelHelper::Default (); 
    channel1.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
4、Mac类型为：NqosWifiMacHelper（没有QoS保障的Mac层机制）
    NqosWifiMacHelper mac1 = NqosWifiMacHelper::Default ();
5、移动模型为随机游走模型，设定初始位置为两个六边形，边长10m，sta在6个顶点上，ap在六边形中间；两个六边形中心相距50m
    //配置移动模型，起始位置 
   MobilityHelper mobility;  
   Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();  
   //设置wifi1网络的sta节点位置 
   positionAlloc->Add (Vector (10.0, 0.0, 0.0));  
   positionAlloc->Add (Vector (5.0, 8.66, 0.0));  
   positionAlloc->Add (Vector (10.0, 17.32, 0.0));  
   positionAlloc->Add (Vector (20.0, 17.32, 0.0));  
   positionAlloc->Add (Vector (25.0, 8.66, 0.0));  
   positionAlloc->Add (Vector (20.0, 0.0, 0.0)); 
   //设置wifi2网络的sta节点位置 
   positionAlloc->Add (Vector (60.0, 0.0, 0.0));  
   positionAlloc->Add (Vector (55.0, 8.66, 0.0));  
   positionAlloc->Add (Vector (60.0, 17.32, 0.0));  
   positionAlloc->Add (Vector (70.0, 17.32, 0.0));  
   positionAlloc->Add (Vector (75.0, 8.66, 0.0));  
   positionAlloc->Add (Vector (70.0, 0.0, 0.0)); 
  //设置wifi1和wifi2的Ap节点的位置 
   positionAlloc->Add (Vector (15.0, 8.66, 0.0));  
   positionAlloc->Add (Vector (65.0, 8.66, 0.0)); 
   mobility.SetPositionAllocator (positionAlloc);  

  
  //配置STA移动方式，RandomWalk2dMobilityModel，随机游走模型
  mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel","Bounds", RectangleValue (Rectangle (0, 500, 0, 500)));
  mobility.Install (wifi1StaNodes);
  mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel","Bounds", RectangleValue (Rectangle (0, 500, 0, 500)));
  mobility.Install (wifi2StaNodes);
6、packet size为512byte，包间隔为100ms
    UdpEchoClientHelper echoClient (interfaces.GetAddress(nWifi2-1),9);
    echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
    echoClient.SetAttribute ("Interval", TimeValue (Seconds (0.1)));
    echoClient.SetAttribute ("PacketSize", UintegerValue (512));

##2.Task2
##3.Task3

##3.Task3
