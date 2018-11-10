#include <fstream>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include <algorithm>

using namespace std;

class Protein
{
private:
  int id;
  string gi;
  string ref;
  string name;
  string sequence;

public:
  Protein(int id, string gi, string ref, string name, string sequence)
  {
    this->id = id;
    this->gi = gi;
    this->ref = ref;
    this->name = name;
    this->sequence = sequence;
  };

  friend ostream &operator<<(ostream &os, Protein p){
      return os << "item id: " << p.id << endl
                << "gi id: " << p.gi << endl
                << "ref id: " << p.ref << endl
                << "name: " << p.name;
  };

  string get_id() {
    return id;
  };

  string get_gi() {
    return gi;
  };

  string get_ref() {
    return ref;
  };

  string get_descr

vector<Protein> initDB(string db)
{
  vector<Protein> vector;

  ifstream data;
  data.open(db);
  cout << "Loading database..." << endl;
  string protein;
  // Used to ignore first 'empty' input
  getline(data, protein, '>');
  int id = 1;
  while (getline(data, protein, '>'))
  {
    auto gi = protein.find("|", 3);
    auto ref = protein.find("|", gi + 5);
    auto name = protein.find("\n");
    string sequence = protein.substr(name);
    sequence.erase(remove(sequence.begin(), sequence.end(), '\n'), sequence.end());
    Protein p = Protein(
        id,
        protein.substr(3, gi - 3),
        protein.substr(gi + 5, ref - gi - 5),
        protein.substr(ref + 2, name - ref - 2),
        sequence);
    vector.push_back(p);
    id++;
  }
  if (data.fail())
    {
      cerr << "Error opening file." << endl; //cerr is a cout equivalent for errors
      exit(1);
    }
  else
    cout << "Database loaded." << endl;
  return vector;
}

int fileMenu()
{
  do
  {
    int selection = 0;
    bool badInput = false; //resets bad input
    cout << "Select an option from the menu below:"
         << "1) Load the abridged protein data"
         << "2) Load the completed protein data"
         << "3) Quit database" << endl;
    cin >> selection;
    badInput = cin.fail();
    if (badInput || selection < 1 || selection > 3)
    {
      cin.clear();
      cin.ignore(10, '\n');
      cout << "Invalid input. Please enter a value between 1 and 3.";
    }
  } while (selection < 1 || selection > 3 || badInput);
  
  return selection;
}

int dbMenu()
{
  do
  {
    int selection = 0;
    bool badInput = false; //resets bad input
    cout << "Select an option from the menu below:"
         << "1) Overview of the database"
         << "2) Search by protein"
         << "3) Search by gi #" 
         << "4) Search by ref #"
         << "5) Search by keyword"
         << "6) Quit database" << endl;
    cin >> selection;
    badInput = cin.fail();
    if (badInput || selection < 1 || selection > 3)
    {
      cin.clear();
      cin.ignore(10, '\n');
      cout << "Invalid input. Please enter a value between 1 and 6.";
    }
  } while (selection < 1 || selection > 3 || badInput);
  
  return selection;
}

int main()
{
  cout << "Welcome to the Protein Database" << endl;

  int file = fileMenu();
  switch (file)
  {
  case 1:
    vector<Protein> Proteins = initDB("protein_a.fa");
  case 2:
    vector<Protein> Proteins = initDB("protein_c.fa");
  default:
    return;
  }


/* Keyword searches
  for(Protein p : Proteins) {
    if (p.get_ref()=="XP_005261862.1")  {
      cout << p << endl;
      break;
    }
  }
*/

  return 0;
}
