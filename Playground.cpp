#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Protein
{
  private:
  int itemNum = 0;
  int giID;
  string refID;
  string description;
  string proteinSeq;

  public:
  readThrough();
};

class Proteins
{
  private:
  vector<Protein> prots;

  add_protein(Protein p){
    prots.push_back(p);
  }

  public:
  find_name(string name) {
    for(Protein prot : prots){
      if(prot.name == name) {
        return prot
        }
    }   
  }
};


