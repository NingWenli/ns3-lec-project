/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("ThirdScriptExample");		//定义记录组件


int 
main (int argc, char *argv[])
{
  bool verbose = true;
  uint32_t nWifi1= 6;			//wifi1节点数量
  uint32_t nWifi2= 6;			//wifi2节点数量
   bool tracing = true;


  CommandLine cmd;
  cmd.AddValue ("nWifi1", "Number of wifi1 STA devices", nWifi1);
  cmd.AddValue ("nWifi2", "Number of wifi2 STA devices", nWifi2);
  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);
  cmd.AddValue ("tracing", "Enable pcap tracing", tracing);

  cmd.Parse (argc,argv);

  // Check for valid number of csma or wifi nodes
  // 250 should be enough, otherwise IP addresses 
  // soon become an issue		//判断是否超过了250个，超过报错 
  if (nWifi1 > 250 || nWifi2 > 250)
    {
      std::cout << "Too many wifi  nodes, no more than 250 each." << std::endl;
      return 1;
    }

  if (verbose)
    {
      LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);	//启动记录组件
    }
 

  //创建wifi1sta无线终端，AP1接入点
  NodeContainer wifi1StaNodes;
  wifi1StaNodes.Create (nWifi1);
  NodeContainer wifi1ApNode;
  wifi1ApNode.Create (1);

  //创建wifi2sta无线终端，AP2接入点
  NodeContainer wifi2StaNodes;
  wifi2StaNodes.Create (nWifi2);
  NodeContainer wifi2ApNode;
  wifi2ApNode.Create (1);

  //创建无线设备于无线节点之间的互联通道，并将通道对象与物理层对象关联
  //确保所有物理层对象使用相同的底层信道，即无线信道
  YansWifiChannelHelper channel1 = YansWifiChannelHelper::Default (); 
  YansWifiPhyHelper phy1 = YansWifiPhyHelper::Default ();
  phy1.SetChannel (channel1.Create ());
  channel1.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
  
  YansWifiChannelHelper channel2 = YansWifiChannelHelper::Default (); 
  YansWifiPhyHelper phy2 = YansWifiPhyHelper::Default ();
  phy2.SetChannel (channel2.Create ());
  channel2.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");

  YansWifiChannelHelper channel3 = YansWifiChannelHelper::Default (); 
  YansWifiPhyHelper phy3 = YansWifiPhyHelper::Default ();
  phy3.SetChannel (channel3.Create ());
  channel3.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
  //配置速率控制算法，AARF算法
  WifiHelper wifi1 = WifiHelper::Default ();
  wifi1.SetRemoteStationManager ("ns3::AarfWifiManager");
  NqosWifiMacHelper mac1 = NqosWifiMacHelper::Default ();

  WifiHelper wifi2 = WifiHelper::Default ();
  wifi2.SetRemoteStationManager ("ns3::AarfWifiManager");
  NqosWifiMacHelper mac2 = NqosWifiMacHelper::Default ();

  WifiHelper wifi3= WifiHelper::Default ();
  wifi3.SetRemoteStationManager ("ns3::AarfWifiManager");
  NqosWifiMacHelper mac3 = NqosWifiMacHelper::Default ();

  //配置mac类型为sta模式，不发送探测请求
  Ssid ssid1= Ssid ("ns-3-ssid");
  mac1.SetType ("ns3::StaWifiMac",
               "Ssid", SsidValue (ssid1),
               "ActiveProbing", BooleanValue (false));

  Ssid ssid2 = Ssid ("ns-3-ssid");
  mac2.SetType ("ns3::StaWifiMac",
               "Ssid", SsidValue (ssid2),
               "ActiveProbing", BooleanValue (false));
  Ssid ssid3 = Ssid ("ns-3-ssid");
  mac3.SetType ("ns3::StaWifiMac",
               "Ssid", SsidValue (ssid3),
               "ActiveProbing", BooleanValue (false));
  //创建无线设备1，将mac1层和phy1层安装到设备上
  NetDeviceContainer sta1Devices;
  sta1Devices = wifi1.Install (phy1, mac1, wifi1StaNodes);

  //创建无线设备2，将mac2层和phy2层安装到设备上
  NetDeviceContainer sta2Devices;
  sta2Devices = wifi2.Install (phy2, mac2, wifi2StaNodes);

  //创建无线设备3，将mac3层和phy3层安装到设备上
  NetDeviceContainer sta3Devices;
  sta3Devices = wifi3.Install (phy3, mac3, wifi1ApNode);
 

  //配置AP节点的mac层为AP模式，创建AP设备1
  mac1.SetType ("ns3::ApWifiMac",
               "Ssid", SsidValue (ssid1));
  NetDeviceContainer ap1Devices;
  ap1Devices = wifi1.Install (phy1, mac1, wifi1ApNode);
 

  //创建AP设备2
 mac2.SetType ("ns3::ApWifiMac",
               "Ssid", SsidValue (ssid2));
  NetDeviceContainer ap2Devices;
  ap2Devices = wifi2.Install (phy2, mac2, wifi2ApNode);

  //创建AP设备3
  mac3.SetType ("ns3::ApWifiMac",
               "Ssid", SsidValue (ssid3));
  NetDeviceContainer ap3Devices;
  ap3Devices = wifi3.Install (phy3, mac3, wifi2ApNode);


  //配置移动模型，起始位置 
   MobilityHelper mobility;  
   Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();  
   //wifi1网络的sta节点位置 
   positionAlloc->Add (Vector (10.0, 0.0, 0.0));  
   positionAlloc->Add (Vector (5.0, 8.66, 0.0));  
   positionAlloc->Add (Vector (10.0, 17.32, 0.0));  
   positionAlloc->Add (Vector (20.0, 17.32, 0.0));  
   positionAlloc->Add (Vector (25.0, 8.66, 0.0));  
   positionAlloc->Add (Vector (20.0, 0.0, 0.0)); 
   //wifi2网络的sta节点位置 
   positionAlloc->Add (Vector (60.0, 0.0, 0.0));  
   positionAlloc->Add (Vector (55.0, 8.66, 0.0));  
   positionAlloc->Add (Vector (60.0, 17.32, 0.0));  
   positionAlloc->Add (Vector (70.0, 17.32, 0.0));  
   positionAlloc->Add (Vector (75.0, 8.66, 0.0));  
   positionAlloc->Add (Vector (70.0, 0.0, 0.0)); 
  //wifi1,wifi2Ap节点的位置 
   positionAlloc->Add (Vector (15.0, 8.66, 0.0));  
   positionAlloc->Add (Vector (65.0, 8.66, 0.0)); 
   mobility.SetPositionAllocator (positionAlloc);  

  
  //配置STA移动方式，RandomWalk2dMobilityModel，随机游走模型
  mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (0, 500, 0, 500)));
  mobility.Install (wifi1StaNodes);
  mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (0, 500, 0, 500)));
  mobility.Install (wifi2StaNodes);
  //配置AP移动方式，ConstantPositionMobilityModel，固定位置模型
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (wifi1ApNode);
  mobility.Install (wifi2ApNode);


  //已经创建了节点，设备，信道和移动模型，接下来配置协议栈
  InternetStackHelper stack;
  stack.Install (wifi1ApNode);
  stack.Install (wifi1StaNodes);
  stack.Install (wifi2ApNode);
  stack.Install (wifi2StaNodes);
 

  //分配IP地址
  Ipv4AddressHelper address;

 //wifi1信道
  address.SetBase ("10.1.1.0", "255.255.255.0");
  address.Assign (sta1Devices);
  address.Assign (ap1Devices);
 
 //wifi2信道
  address.SetBase ("10.1.2.0", "255.255.255.0");
  address.Assign (ap2Devices);
  Ipv4InterfaceContainer interfaces=address.Assign (sta2Devices);
  

  //wifi3信道
  address.SetBase ("10.1.3.0", "255.255.255.0");
  address.Assign (sta3Devices);
  address.Assign (ap3Devices);


  //放置echo服务端程序在wifi2的STA节点,端口为9
  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (wifi2StaNodes.Get(nWifi2-1));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  //回显客户端放在wifi2的STA节点，指向wifi2网络的服务器上面的节点地址，端口为9
  UdpEchoClientHelper echoClient (interfaces.GetAddress(nWifi2-1),9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (0.1)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (512));

  //安装其他节点应用程序
  //clientApps1
  ApplicationContainer clientApps1 = 
    echoClient.Install (wifi1StaNodes.Get (nWifi1 - 1));
  clientApps1.Start (Seconds (2.0));
  clientApps1.Stop (Seconds (10.0));
  //clientApps2
  ApplicationContainer clientApps2 = 
    echoClient.Install (wifi1StaNodes.Get (nWifi1 - 2));
  clientApps2.Start (Seconds (2.2));
  clientApps2.Stop (Seconds (10.0));
  //clientApps3
  ApplicationContainer clientApps3 = 
    echoClient.Install (wifi1StaNodes.Get (nWifi1 - 3));
  clientApps3.Start (Seconds (2.4));
  clientApps3.Stop (Seconds (10.0));
  //clientApps4
  ApplicationContainer clientApps4 = 
    echoClient.Install (wifi1StaNodes.Get (nWifi1 - 4));
  clientApps4.Start (Seconds (2.6));
  clientApps4.Stop (Seconds (10.0));
   


  //启动互联网络路由
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  Simulator::Stop (Seconds (10.0));

  if (tracing == true)
    {
      AsciiTraceHelper ascii;
      phy1.EnableAsciiAll (ascii.CreateFileStream ("ns3-lec4-project4.tr"));
      phy2.EnablePcap ("ns3-lec4-project4", ap1Devices.Get (0));
    
    }
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;

}
