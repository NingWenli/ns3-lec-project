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
#include <iostream>
using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("Student Message");
static void printHello(std::string name,std::string id) {


	std::cout<<Simulator::Now()<<"  Name:"<<name;
        std::cout<<"  ID:"<<id<<std::endl;
	Simulator::Schedule(Seconds(1),&printHello,name,id);
}
int
main (int argc, char *argv[])
{
	CommandLine cmd;
	std::string name;
        std::string id;
	cmd.AddValue ("name", "my name", name);
        cmd.AddValue ("id", "my name", id);
	cmd.Parse(argc,argv);

	std::cout<<"Student Message"<<std::endl;
        printHello(name,id);

	Simulator::Stop(Seconds(5));
	Simulator::Run ();
	Simulator::Destroy ();
}
