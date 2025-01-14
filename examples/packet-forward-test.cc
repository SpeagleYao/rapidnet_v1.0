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
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
#include <ctime>


#define Design \
"./data/packet-forward/packet-forward.db"

#define Test1 \
"./data/packet-forward/test.db"

#define packet(local, src, dst, data) \
tuple (PacketForward::PACKET, \
attr ("packet_attr1", Ipv4Value, local), \
attr ("packet_attr2", Ipv4Value, src), \
attr ("packet_attr3", Ipv4Value, dst), \
attr ("packet_attr4", StrValue, data) \
)


#define route(local, dst, next) \
tuple (PacketForward::ROUTE, \
attr ("route_attr1", Ipv4Value, local), \
attr ("route_attr2", Ipv4Value, dst), \
attr ("route_attr3", Ipv4Value, next) \
)


#define insertpacket(local, src, dst, data) \
app(local)->Insert(packet(addr(local), addr(src), addr(dst), data))


#define insertroute(local, dst, next) \
app(local)->Insert(route(addr(local), addr(dst), addr(next)))



using namespace std;
using namespace ns3;
using namespace ns3::rapidnet;
using namespace ns3::rapidnet::packetforward;


ApplicationContainer apps;

vector<vector<string> > inputdata;;
int g_i = 0;

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

  /*
  if (predicate=="route") {
    int local = atoi(words[1].c_str());
    int dst = atoi(words[2].c_str());
    int next = atoi(words[3].c_str());
    // cout << "route(" << local << ", " << dst << ", " << next << ")\n";
    // insertroute(local, dst, next);
  }

  else if (predicate=="packet") {
    int local = atoi(words[1].c_str());
    int src = atoi(words[2].c_str());
    int dst = atoi(words[3].c_str());
    string data = words[4];
    clock_t now = clock();
    stringstream ss;
    ss << now;
    data += ss.str();
    // cout << "packet(" << local << ", " << src << ", " << dst << ", " << data << ")\n";
    // insertpacket(local, src, dst, data);
    // usleep(100000);
  }
  */

  inputdata.push_back(splits);

}


void train() {
  ifstream fp(Test1);
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


void inserttuples() {
  vector<string> tupledata = inputdata[g_i];
  if (tupledata[0]=="route") {
    int local = atoi(tupledata[1].c_str());
    int dst = atoi(tupledata[2].c_str());
    int next = atoi(tupledata[3].c_str());
    // cout << local << ' ' << dst << ' ' << next << endl;    
    insertroute(local, dst, next);
  }  
  else if (tupledata[0]=="packet") {
    // cout << "packet" << endl;
    // cout << tupledata.size() << endl;
    int local = atoi(tupledata[1].c_str());
    int src = atoi(tupledata[2].c_str());
    int dst = atoi(tupledata[3].c_str());
    string data = tupledata[4];
    // cout << local << src << dst << data << endl;
    clock_t now = clock();
    // cout << now << endl;
    stringstream ss;
    ss << now;
    data += ss.str();
    // cout << local << ' ' << src << ' ' << dst << ' ' << data << endl;
    insertpacket(local, src, dst, data);
    usleep(10);
  }
  g_i++;
}


void Print() {
  // PrintRelation(apps, PacketForward::ROUTE);
  // PrintRelation(apps, PacketForward::PACKET);
  // PrintRelation(apps, PacketForward::RECV);
  PrintRelation(apps, PacketForward::EDGE);
  // PrintRelation(apps, PacketForward::PROV);
}


int main(int argc, char *argv[]){
	
	train();
	/*
	for (int i=0; i<inputdata.size(); i++) {
	  for (int j=0; j<inputdata[i].size(); j++) {
	    cout << inputdata[i][j] << ' ';
	  }
	  cout << endl;
	}
	*/

	apps = InitRapidNetApps (50, Create<PacketForwardHelper> ());
	SetMaxJitter (apps, 0.000);

	apps.Start (Seconds (0.0));
	apps.Stop (Seconds (10000.0));

	// schedule (1.0, train);


	for (int i=0; i<inputdata.size(); i++) {
	schedule (3.0+i*0.1, inserttuples);
	}
        schedule (9999.0, Print);

	Simulator::Run ();
	Simulator::Destroy ();

	return 0;

}
	






