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
"./data/hyper-text-class/sample7/sample71.db"

#define HyperTextClassTest2 \
"./data/hyper-text-class/sample7/sample72.db"

#define HyperTextClassTest3 \
"./data/hyper-text-class/sample7/sample73.db"

#define HyperTextClassTest4 \
"./data/hyper-text-class/sample7/sample74.db"

#define HyperTextClassTest5 \
"./data/hyper-text-class/sample7/sample75.db"

#define HyperTextClassTest6 \
"./data/hyper-text-class/sample7/sample76.db"

#define HyperTextClassTest7 \
"./data/hyper-text-class/sample7/sample77.db"

#define HyperTextClassTest8 \
"./data/hyper-text-class/sample7/sample78.db"

#define HyperTextClassTest9 \
"./data/hyper-text-class/sample7/sample79.db"

#define HyperTextClassTest10 \
"./data/hyper-text-class/sample7/sample710.db"

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



using namespace std;
using namespace ns3;
using namespace ns3::rapidnet;
using namespace ns3::rapidnet::hypertextclass;


ApplicationContainer apps;


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
  ifstream fp(HyperTextClassTest10);
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
}



const char* args[]= {"Student", "Faculty", "Staff", "ResearchProject", "Course", "Department", "Person"};
vector<string> g_topics (args, args+7);
int g_i = 0;



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

	apps = InitRapidNetApps (3, Create<HyperTextClassHelper> ());
	SetMaxJitter (apps, 0.001);

	apps.Start (Seconds (0.0));
	apps.Stop (Seconds (10.0));

	schedule (2.0, train);
  schedule (5.0, Print);

	Simulator::Run ();
	Simulator::Destroy ();
	clock_t t2 = clock();

  cout << "time cost: " << ((double)(t2-t1))/CLOCKS_PER_SEC << " seconds" << endl;
	return 0;

}
	



