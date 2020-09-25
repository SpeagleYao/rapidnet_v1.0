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
#include "ns3/hyper-text-class-module.h"
#include "ns3/hyper-text-class-query-module.h"
#include "ns3/list-value.h"
#include <fstream>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>


#define HyperTextClassTest1 \
"./data/hyper-text-class/sample4/sample41.db"

#define HyperTextClassTest2 \
"./data/hyper-text-class/sample4/sample42.db"

#define HyperTextClassTest3 \
"./data/hyper-text-class/sample4/sample43.db"

#define HyperTextClassTest4 \
"./data/hyper-text-class/sample4/sample44.db"

#define HyperTextClassTest5 \
"./data/hyper-text-class/sample4/sample45.db"

#define HyperTextClassTest6 \
"./data/hyper-text-class/sample4/sample46.db"

#define HyperTextClassTest7 \
"./data/hyper-text-class/sample4/sample47.db"

#define HyperTextClassTest8 \
"./data/hyper-text-class/sample4/sample48.db"

#define HyperTextClassTest9 \
"./data/hyper-text-class/sample4/sample49.db"

#define HyperTextClassTest10 \
"./data/hyper-text-class/sample4/sample410.db"

#define HyperTextClassTest11 \
"./data/hyper-text-class/sample4/sample411.db"

#define HyperTextClassTest12 \
"./data/hyper-text-class/sample4/sample412.db"

#define HyperTextClassTest13 \
"./data/hyper-text-class/sample4/sample413.db"

#define HyperTextClassTest14 \
"./data/hyper-text-class/sample4/sample414.db"

#define HyperTextClassTest15 \
"./data/hyper-text-class/sample4/sample415.db"

#define HyperTextClassTest16 \
"./data/hyper-text-class/sample4/sample416.db"

#define HyperTextClassTest17 \
"./data/hyper-text-class/sample4/sample417.db"

#define HyperTextClassTest18 \
"./data/hyper-text-class/sample4/sample418.db"

#define HyperTextClassTest19 \
"./data/hyper-text-class/sample4/sample419.db"

#define HyperTextClassTest20 \
"./data/hyper-text-class/sample4/sample420.db"

#define hasword(local, word, address) \
tuple (HyperTextClass::HASWORD, \
attr ("hasword_attr1", Ipv4Value, local), \
attr ("hasword_attr2", StrValue, word), \
attr ("hasword_attr3", Int32Value, address) \
)

#define links(local, address1, address2) \
tuple (HyperTextClass::LINKS, \
attr ("links_attr1", Ipv4Value, local), \
attr ("links_attr2", Int32Value, address1), \
attr ("links_attr3", Int32Value, address2) \
)


#define inserthasword(local, word, address) \
app(local)->Insert(hasword(addr(local), word, address))

#define insertlinks(local, address1, address2) \
app(local)->Insert(links(addr(local), address1, address2))



#define tupleQuery(local, name, attr1, attr2, attr3) \
tuple (HyperTextClassQuery::TUPLE, \
attr ("tuple_attr1", Ipv4Value, local), \
attr ("tuple_attr2", StrValue, name), \
attr ("tuple_attr3", Ipv4Value, attr1), \
attr ("tuple_attr4", StrValue, attr2), \
attr ("tuple_attr5", Int32Value, attr3) \
)

#define inserttuple(local, name, attr1, attr2, attr3) \
queryNode->Insert(tupleQuery(queryNode->GetAddress(), name, addr(attr1), attr2, attr3))




using namespace std;
using namespace ns3;
using namespace ns3::rapidnet;
using namespace ns3::rapidnet::hypertextclass;
using namespace ns3::rapidnet::hypertextclassquery;


ApplicationContainer apps;
ApplicationContainer queryapps;


void initApps()
{
	NodeContainer mainAppNodes;
	mainAppNodes.Create (3);

	NodeContainer queryAppNodes;
	queryAppNodes.Create (1);

  NodeContainer csmaNodes;
  csmaNodes.Add(mainAppNodes);
  csmaNodes.Add(queryAppNodes);

  CsmaHelper csma;

  NetDeviceContainer csmaDevices;
  csmaDevices = csma.Install (csmaNodes);

  InternetStackHelper stack;
  stack.Install (csmaNodes);

  Ipv4AddressHelper address;
  Ipv4Address base = "10.1.1.0";

  address.SetBase (base, "255.255.255.0");
  address.Assign (csmaDevices);

  apps.Add(Create<HyperTextClassHelper>()->Install(mainAppNodes));
  queryapps.Add(Create<HyperTextClassQueryHelper>()->Install(queryAppNodes));

  SetMaxJitter (apps, 0.001);
  SetMaxJitter (queryapps, 0.001);
}


void parseLine(const string& line) {
  vector<string> splits;
  boost::split(splits, line, boost::is_any_of(" "));

  vector<string> words;
  for (int i=0; i<splits.size(); i++) {
    if (splits[i].size()!=0) {
      words.push_back(splits[i]);
    }
  }

  string predicate = words[0];
  // cout << line << endl;
  if (predicate=="//") {
    return;
  }
  else if (predicate=="hasword") {
    int a = atoi(words[2].c_str());
    inserthasword(1, words[1], a);
  }
  else if (predicate=="links") {
    insertlinks(1, atoi(words[1].c_str()), atoi(words[2].c_str()));
  }

}


void train() {
  ifstream fp(HyperTextClassTest8);
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
  // PrintRelation(apps, HyperTextClass::HASWORD);
  // PrintRelation(apps, HyperTextClass::LINKS);
  // PrintRelation(apps, HyperTextClass::TOPIC);
  // PrintRelation(queryapps, HyperTextClassQuery::TUPLE);
  PrintRelation(queryapps, HyperTextClassQuery::RECORDS);
}



const char* args[]= {"Student", "Faculty", "Staff", "ResearchProject", "Course", "Department", "Person"};
vector<string> g_topics (args, args+7);
int g_i = 0;


void TupleToQuery() {
  Ptr<RapidNetApplicationBase> queryNode = queryapps.Get(0)->GetObject<RapidNetApplicationBase>();
  inserttuple(1, "topic", 1, "Student", 2);
}


void TupleToQueryLoop() {
  Ptr<RapidNetApplicationBase> queryNode = queryapps.Get(0)->GetObject<RapidNetApplicationBase>();
  inserttuple(1, "topic", 1, g_topics[g_i], 8);
  g_i++;
}


void TupleToQueryLoopV2() {
  Ptr<RapidNetApplicationBase> queryNode = queryapps.Get(0)->GetObject<RapidNetApplicationBase>();
  inserttuple(1, "topic", 1, "Student", g_i);
  inserttuple(1, "topic", 1, "Faculty", g_i);
  inserttuple(1, "topic", 1, "Staff", g_i);
  inserttuple(1, "topic", 1, "ResearchProject", g_i);
  inserttuple(1, "topic", 1, "Course", g_i);
  inserttuple(1, "topic", 1, "Department", g_i);
  inserttuple(1, "topic", 1, "Person", g_i);
  g_i++;
}


/*
int main(int argc, char *argv[]){
  
  initApps();

  apps.Start (Seconds (0.0));
  apps.Stop (Seconds (10.0));
  queryapps.Start (Seconds (0.0));
  queryapps.Stop (Seconds (10.0));

  schedule (1.0, TupleToQuery);	
  schedule (2.0, train);
  schedule (5.0, Print);

  Simulator::Run ();
  Simulator::Destroy ();
  
  return 0;
}
*/
	


int main(int argc, char *argv[]){
  clock_t t1 = clock();  
  cout << t1 << endl;
  initApps();

  for (int i=0; i<g_topics.size(); i++) {
    cout << g_topics[i] << endl;
  }

  apps.Start (Seconds (0.0));
  apps.Stop (Seconds (1000.0));
  queryapps.Start (Seconds (0.0));
  queryapps.Stop (Seconds (1000.0));

  schedule (1.0, train);

  // for (int i=0; i<g_topics.size(); i++) {
  // schedule (i+2.0, TupleToQueryLoop);
  // }

  for (int i=0; i<500; i++) {
  schedule (i+1.0, TupleToQueryLoopV2);
  }

  // schedule  (g_i*5.0+3, TupleToQueryLoop);
  // schedule  (g_i*5.0+3, TupleToQueryLoop);

  schedule (999.0, Print);

  Simulator::Run ();
  Simulator::Destroy ();
  clock_t t2 = clock();
  cout << "time cost: " << ((double)(t2-t1))/CLOCKS_PER_SEC << " seconds" << endl;
  
  return 0;
}

