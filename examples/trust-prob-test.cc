#include "ns3/core-module.h"
#include "ns3/simulator-module.h"
#include "ns3/node-module.h"
#include "ns3/rapidnet-module.h"
#include "ns3/values-module.h"
#include "ns3/helper-module.h"
#include "ns3/trust-prob-module.h"
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <boost/algorithm/string.hpp>
#include <stdlib.h>

#define TrustTrain_10 \
"./data/trust-new/sample_10_new.csv"

#define TrustTrain_20 \
"./data/trust-new/sample_20_new.csv"

#define TrustTrain_30 \
"./data/trust-new/sample_30_new.csv"

#define TrustTrain_40 \
"./data/trust-new/sample_40_new.csv"

#define TrustTrain_50 \
"./data/trust-new/sample_50_new.csv"

#define TrustTrain_60 \
"./data/trust-new/sample_60_new.csv"

#define TrustTrain_70 \
"./data/trust-new/sample_70_new.csv"

#define TrustTrain_80 \
"./data/trust-new/sample_80_new.csv"

#define TrustTrain_90 \
"./data/trust-new/sample_90_new.csv"

#define TrustTrain_100 \
"./data/trust-new/sample_100_new.csv"

#define trust(local, person1, person2, round) \
tuple (TrustProb::TRUST, \
attr ("trust_attr1", Ipv4Value, local), \
attr ("trust_attr2", Int32Value, person1), \
attr ("trust_attr3", Int32Value, person2), \
attr ("trust_attr4", Int32Value, round) \
)

#define inserttrust(local, person1, person2, round) \
app(local)->Insert(trust(addr(local), person1, person2, round));

using namespace std;
using namespace ns3;
using namespace ns3::rapidnet;
using namespace ns3::rapidnet::trustprob;

ApplicationContainer apps;

vector<vector<string> > trusts;
int t_i = 0;

int max_rounds = 1;
int r = 0;
	
int stringToInt(string s){
  stringstream ss(s);
  int x = 0;
  ss >> x;
  return x;
}

double stringToDouble(string s){
  stringstream ss(s);
  double x = 0.0;
  ss >> x;
  return x;
}


void parseLine(const string& line)
{	
  vector<string> splits;
  boost::split(splits, line, boost::is_any_of("(), "));

  trusts.push_back(splits);
}

void train() {
  ifstream fp(TrustTrain_50);
  string line;

  int count = 0;
  while (getline(fp, line)) {
    if (!line.empty()&&count>0) {
      int i = 0;
      while (i<line.size() && line[i]==' ') {
        i++;
      }
      if (i!=0) {
        line = line.substr(i, line.size()-i);
      }
      parseLine(line);
    }
    count++;
  }

}

void Print(){
	// PrintRelation(apps, TrustProb::TRUST);
  // PrintRelation(apps, Trust::TRUSTPATH);
  // PrintRelation(apps, Trust::MUTUALTRUSTPATH);


 //  PrintRelation (apps, Trust::PROV);
  PrintRelation(apps, TrustProb::PROVEDGE);
  PrintRelation(apps, TrustProb::RULEEDGE);
}


void inserttrusttuple() {
   vector<string> trustdata = trusts[t_i%trusts.size()];
   int local = 1;
   int person1 = atoi(trustdata[0].c_str());
   int person2 = atoi(trustdata[1].c_str());
   double prob = atof(trustdata[2].c_str());
   int round = t_i/trusts.size();
   double sample = rand()*1.0/RAND_MAX;
   if (sample<prob) {
     // cout << local << ' ' << person1 << ' ' << person2 << ' ' << round << endl;
     inserttrust(local, person1, person2, round);
   }
   t_i++;
}

int main(int argc, char *argv[]){

	
  // LogComponentEnable("Trust", LOG_LEVEL_INFO);
  // LogComponentEnable("TrustQuery", LOG_LEVEL_INFO);
  // LogComponentEnable("RapidNetApplicationBase", LOG_LEVEL_INFO);
  // for (int i=0; i<2; i++){
  //
  clock_t t1 = clock();
	train();    
	apps = InitRapidNetApps (1, Create<TrustProbHelper> ());
	SetMaxJitter (apps, 0.000);

    apps.Start (Seconds (0.0));
    apps.Stop (Seconds (10000.0));


    for (r=0; r<max_rounds; r++) {
      for (int i=0; i<trusts.size(); i++) {
        schedule (3.0+0.1*(trusts.size()*r+i), inserttrusttuple);
      }
    }

    schedule (9999.9, Print);

    Simulator::Run ();
    Simulator::Destroy ();

   clock_t t2 = clock();
   cout << 1.0*(t2-t1)/CLOCKS_PER_SEC << endl;

  // }
  return 0;
}
