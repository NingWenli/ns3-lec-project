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

// Default Network Topology
//默认网络拓扑
// Number of wifi or csma nodes can be increased up to 250
//                          |
//                 Rank 0   |   Rank 1
// -------------------------|----------------------------
//   LAN 10.1.3.0
//                            AP
// =====================
// |    |    |    |    |       10.1.1.0
// n5   n6   n7   n8   n0 ------------------ n1   n2   n3   n4
//                         point-to-point    |    |    |    |
//                                           ================
//                                              LAN 10.1.2.0

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("ThirdScriptExample");		//定义记录组件

int 
main (int argc, char *argv[])
{
  bool verbose = true;
  uint32_t nCsma1 = 3;			//csma1节点数量
  uint32_t nCsma2 = 4;			//csma2节点数量
   bool tracing = false;


  CommandLine cmd;
  cmd.AddValue ("nCsma1", "Number of \"extra\" CSMA1 nodes/devices", nCsma1);
  cmd.AddValue ("nCsma2", "Number of \"extra\" CSMA2 nodes/devices", nCsma2);
  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);
  cmd.AddValue ("tracing", "Enable pcap tracing", tracing);

  cmd.Parse (argc,argv);

  // Check for valid number of csma or wifi nodes
  // 250 should be enough, otherwise IP addresses 
  // soon become an issue		//判断是否超过了250个，超过报错 , 原因？
  if ( nCsma1> 250 || nCsma2 > 250)
    {
      std::cout << "Too many wifi or csma nodes, no more than 250 each." << std::endl;
      return 1;
    }

  if (verbose)
    {
      LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);	//启动记录组件
    }


  //创建2个节点，p2p链路两端
  NodeContainer p2pNodes;
  p2pNodes.Create (2);

  //创建信道，设置信道参数，在设备安装到节点上
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer p2pDevices;
  p2pDevices = pointToPoint.Install (p2pNodes);

  //创建csma1节点，包含一个p2p节点

  NodeContainer csma1Nodes;
  csma1Nodes.Add (p2pNodes.Get (1));  //n1 node
  csma1Nodes.Create (nCsma1);
  
  //创建csma2节点，包含一个p2p节点

  NodeContainer csma2Nodes;
  csma2Nodes.Add (p2pNodes.Get (0));  //n1 node
  csma2Nodes.Create (nCsma2);

  //创建信道，设置信道参数，在设备安装到节点上
  CsmaHelper csma1;
  csma1.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma1.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

  NetDeviceContainer csma1Devices;
  csma1Devices = csma1.Install (csma1Nodes);

  CsmaHelper csma2;
  csma2.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma2.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

  NetDeviceContainer csma2Devices;
  csma2Devices = csma2.Install (csma2Nodes);



  //已经创建了节点，设备，信道和移动模型，接下来配置协议栈
  InternetStackHelper stack;
  stack.Install (csma1Nodes);
  stack.Install (csma2Nodes);
  
  //分配IP地址
  Ipv4AddressHelper address;
 //P2P信道
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces;
  p2pInterfaces = address.Assign (p2pDevices);
 //csma1信道
  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer csma1Interfaces;
  csma1Interfaces = address.Assign (csma1Devices);
 //csma2信道
  address.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer csma2Interfaces;
  csma2Interfaces = address.Assign (csma2Devices);

  //放置echo服务端程序在最右边的csma节点,端口为9
  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (csma1Nodes.Get (nCsma1));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  //回显客户端放在最后的STA节点，指向CSMA网络的服务器，上面的节点地址，端口为9
  UdpEchoClientHelper echoClient (csma1Interfaces.GetAddress (nCsma1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  //安装其他节点应用程序
  //clientApps1
  ApplicationContainer clientApps1 = 
    echoClient.Install (csma2Nodes.Get (nCsma2));
  clientApps1.Start (Seconds (2.0));
  clientApps1.Stop (Seconds (10.0));
  //clientApps2
  ApplicationContainer clientApps2 = 
    echoClient.Install (csma2Nodes.Get (nCsma2-1));
  clientApps2.Start (Seconds (2.2));
  clientApps2.Stop (Seconds (10.0));
  //clientApps3
  ApplicationContainer clientApps3 = 
   echoClient.Install (csma2Nodes.Get (nCsma2-2));
  clientApps3.Start (Seconds (2.4));
  clientApps3.Stop (Seconds (10.0));
  //clientApps4
  ApplicationContainer clientApps4 = 
    echoClient.Install (csma2Nodes.Get (nCsma2-3));
  clientApps4.Start (Seconds (2.6));
  clientApps4.Stop (Seconds (10.0));

  //启动互联网络路由
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  Simulator::Stop (Seconds (10.0));

  if (tracing == true)
    {
      pointToPoint.EnablePcapAll ("ns3-lec2-project2-2");
     // phy.EnablePcap ("ns3-lec2-project2-2", apDevices.Get (0));
      csma1.EnablePcap ("ns3-lec2-project2-2", csma1Devices.Get (0), true);
      csma2.EnablePcap ("ns3-lec2-project2-2", csma2Devices.Get (0), true); 
    }

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
