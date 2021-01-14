/* _*_ Mode:C++; c_file_style:"gnu"; indent_tabs_mode:nil; _*_ */
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111_1307  USA
 */

#include "ns3/core-module.h"
#include "ns3/simulator-module.h"
#include "ns3/node-module.h"
#include "ns3/rapidnet-module.h"
#include "ns3/values-module.h"
#include "ns3/helper-module.h"
#include "ns3/packet-forward-module.h"
#include "ns3/list-value.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>


#define Train \
"./data/packet-forward/packet-forward.db"

#define packet(local, src, dst, data) \
tuple (PacketForward::PACKET, \
attr ("packet_attr1", Ipv4Value, local), \
attr ("packet_attr2", Int32Value, src), \
attr ("packet_attr3", Int32Value, dst), \
attr ("packet_attr4", StrValue, data) \
)


#define route(local, dst, next) \
tuple (PacketForward::ROUTE, \
attr ("route_attr1", Int32Value, local), \
attr ("route_attr2", Int32Value, dst), \
attr ("route_attr3", Ipv4Value, next) \
)


#define insertpacket(local, src, dst, data) \
app(local)->Insert(packet(addr(local), src, dst, data))


#define insertroute(local, dst, next) \
app(local)->Insert(route(addr(local), dst, next))



using namespace std;
using namespace ns3;
using namespace ns3::rapidnet;
using namespace ns3::rapidnet::packetforward;


ApplicationContainer apps;



void parseLine(const string& line) {
  vector<string> splits;
  boost::split(splits, line, boost::is_any_of("(), "));

  vector<string> words;
  for (int i=0; i<splits.size(); i++) {
    if (splits[i].size()!=0) {
      words.push_back(splits[i]);
    }
  }
  string predicate = words[0];
  if (predicate=="//") {
    return;
  }
  if (predicate=="route") {
    int local = std::stoi(words[1], nullptr);
    int dst = std::stoi(words[2], nullptr);
    int next = std::stoi(words[3], nullptr);
    cout << "route(" << local << ", " << dst << ", " << next << ")\n";
    insertroute(local, dst, next);
  }
  else if (predicate=="packet") {
    int local = std::stoi(words[1], nullptr);
    int src = std::stoi(words[2], nullptr);
    int dst = std::stoi(words[3], nullptr);
    string data = words[4];
    cout << "packet(" << local << ", " << src << ", " << dst << ", " << data << ")\n";
    insertpacket(local, src, dst, data);
  }
}


void train() {
  ifstream fp(Train);
  string line;

  while (getline(fp, line)) {
    if (!line.empty()) {
      int i = 0;
      while (i<line.size() && line[i]==' ') {
        i++;
      }
      if (i!=0) {
        line = line.substr(i, line.size()-i);
      }
      parseLine(line);
    }
  }

}



void Print() {
  PrintRelation(apps, PacketForward::ROUTE);
  PrintRelation(apps, PacketForward::PACKET);
  PrintRelation(apps, PacketForward::RECV);
}


int main(int argc, char *argv[]){

	apps = InitRapidNetApps (3, Create<PacketForwardHelper> ());
	SetMaxJitter (apps, 0.001);

	apps.Start (Seconds (0.0));
	apps.Stop (Seconds (10.0));

	schedule (2.0, train);
  schedule (5.0, Print);

	Simulator::Run ();
	Simulator::Destroy ();

	return 0;

}
	






