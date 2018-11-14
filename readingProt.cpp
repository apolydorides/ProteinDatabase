#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

class Protein
{
private:
  int id;
  string gi;
  string ref;
  string descr;
  string sequence;

public:
  Protein(int id, string gi, string ref, string descr, string sequence)
  {
    this->id = id;
    this->gi = gi;
    this->ref = ref;
    this->descr = descr;
    this->sequence = sequence;
  };

  friend ostream &operator<<(ostream &os, Protein p)
  {
    return os << "Item #: " << p.id << endl
              << "GI #: " << p.gi << endl
              << "Ref #: " << p.ref << endl
              << "Description: " << p.descr;
  };

  int get_id()
  {
    return id;
  };

  string get_gi()
  {
    return gi;
  };

  string get_ref()
  {
    return ref;
  };

  string get_descr()
  {
    return descr;
  };

  string get_sequence()
  {
    return sequence;
  };

  bool keywordMatch(string str)
  {
    if (descr.find(str) != string::npos)
    { //.find function returns npos when there is no match
      return true;
    }
    return false;
  };
};


void fileMenu();
void dbMenu(vector<Protein> proteins);
void protMenu(Protein p);


/*Tokenizing the proteins by finding the ">" character
Then separating the first line using the "|" character
Finally, values (gi, ref etc.) are added as a vector*/
vector<Protein> initDB(string db)
{
  vector<Protein> proteins;

  ifstream data;
  data.open(db);
  cout << endl << "Loading database..." << endl;
  if (data.fail())
  {
    cerr << "Error opening file." << endl; //cerr is a cout equivalent for errors
    exit(1);
  }
  else
  {
    string protein;
    // Used to ignore first 'empty' input
    getline(data, protein, '>');
    int id = 1;
    while (getline(data, protein, '>'))
    {
      auto gi = protein.find("|", 3);
      auto ref = protein.find("|", gi + 5);
      auto name = protein.find("\n");
      string sequence = protein.substr(name);                                         //no length variable as end of sequence is also end of data for each protein
      sequence.erase(remove(sequence.begin(), sequence.end(), '\n'), sequence.end()); //removes the new-line characters within the sequence
      Protein p = Protein(
          id,
          protein.substr(3, gi - 3),
          protein.substr(gi + 5, ref - gi - 5),
          protein.substr(ref + 2, name - ref - 2),
          sequence);
      proteins.push_back(p); //adds protein with its details to vector
      id++;                  //adds one to id counter (will be used to output total proteins at the end)
    }
    cout << "Database loaded." << endl << endl;
  }
  return proteins;
}

void fileMenu() //File-selection Menu
{
  int selection = 0;
  bool badInput = false;
  while ((selection < 1) || selection > 3 || badInput)
  {                   //will keep asking for user input until valid
                      //same error handling method used for all menus
    badInput = false; //resets bad input boolean value
    cout << endl
         << "Select an option from the menu below:" << endl
         << "1) Load the abridged protein data" << endl
         << "2) Load the completed protein data" << endl 
         << "3) Quit database" << endl ;
    cin >> selection;
    badInput = cin.fail(); //cin.fail() evaluates to true if input type is not as expected
    if (badInput || selection < 1 || selection > 3)
    {
      cin.clear(); //clears user-input
      cin.ignore(10, '\n');
      cout << endl << "Invalid input. Please enter a value between 1 and 3." << endl;
    }
  }
  vector<Protein> proteins;
  switch (selection)
  {
  case 1:
    proteins = initDB("protein_a.fa");
    dbMenu(proteins);
    break;
  case 2:
    proteins = initDB("protein_c.fa");
    dbMenu(proteins);
    break;
  default:
    cout << "Exiting database";
    exit(0); //since I am only allowing values 1,2,3 to be handled by the switch statement, default (i.e. 3) will exit the database
    break;
  }
}

void dbMenu(vector<Protein> proteins) //Database Menu
{
  int selection = 0;
  bool badInput = false;
  while (selection < 1 || selection > 6 || badInput)
  {
    badInput = false; //resets bad input
    cout << endl
         << "Select an option from the menu below:" << endl
         << "1) Overview of the database" << endl
         << "2) Search by protein #" << endl
         << "3) Search by gi #" << endl
         << "4) Search by ref #" << endl
         << "5) Search by keyword" << endl
         << "6) Quit database" << endl;
    cin >> selection;
    badInput = cin.fail();
    if (badInput || selection < 1 || selection > 6)
    {
      cin.clear();
      cin.ignore(10, '\n');
      cout << "Invalid input. Please enter a value between 1 and 6.";
    }
  }

  int idSearch;
  string search;
  int i = 0;
  switch (selection) {
    case 1:
      cout << endl
          << "The proteins in the database are from GenBank(R)." << endl
          << "Total number of proteins in this database: " << proteins.size() << endl//Add proteins.size()?
          << "Amino acids are represented by the following characters:" << endl
          << "A  alanine                P  proline" << endl
          << "B  aspartate/asparagine   Q  glutamine" << endl
          << "C  cystine                R  arginine" << endl
          << "D  aspartate              S  serine" << endl
          << "E  glutamate              T  threonine" << endl
          << "F  phenylalanine          U  selenocysteine" << endl
          << "G  glycine                V  valine" << endl
          << "H  histidine              W  tryptophan" << endl
          << "I  isoleucine             Y  tyrosine" << endl
          << "K  lysine                 Z  glutamate/glutamine" << endl
          << "L  leucine                X  any" << endl
          << "M  methionine             *  translation stop" << endl
          << "N  asparagine             -  gap of indeterminate length" << endl ;
      dbMenu(proteins);
      break;
    case 2:
      cout << "Enter a protein number:" << endl;
      cin >> idSearch;
      for (Protein p : proteins)
      {
        if (p.get_id() == idSearch)
        {
          cout << endl << "You selected:" << endl;
          cout << p.get_descr() << endl;
          protMenu(p);
          break;
        }
        else if (p.get_id() == proteins.size())
        {
          cout << "Your search yielded no results. Please check your input is correct and try again." << endl;
          dbMenu(proteins);
        }
      }
      break;
    case 3:
      cout << "Enter a GI number:" << endl;
      cin >> search;
      for (Protein p : proteins)
      {
        if (p.get_gi() == search)
        {
          cout << endl << "You selected:" << endl;
          cout << p.get_descr() << endl;
          protMenu(p);
          break;
        }
        else
        {
          cout << "Your search yielded no results. Please check your input is correct and try again." << endl;
          dbMenu(proteins);
        }
      }
      break;
    case 4:
      cout << "Enter a reference number:" << endl;
      cin >> search;
      for (Protein p : proteins)
      {
        if (p.get_ref() == search)
        {
          cout << endl << "You selected:" << endl;
          cout << p.get_descr() << endl;
          protMenu(p);
          break; //since ref,gi,id are specific to 1 protein we break to reduce run-time
        }
        else
        {
          cout << "Your search yielded no results. Please check your input is correct and try again." << endl;
          dbMenu(proteins);
        }
      }
      break;
    case 5:
      cout << "Enter a keyword to search for:" << endl;
      cin >> search;
      for(Protein p : proteins) {
        if(p.keywordMatch(search)) {
          cout << ++i << ") " << p << endl << endl;
        }
        else if (p.get_id()==proteins.size() && (i == 0)) {
          cout << "Your search yielded no results. Please check your input is correct and try again." << endl;
          dbMenu(proteins);
        }
      }
      break;
    default:
      cout << "Exiting database";
      exit(0); //since I am only allowing values 1-6 to be handled by the switch statement, default (i.e. 6) will exit the database
      break;
  }
}

void protMenu(Protein p) {
  int selection = 0;
  bool badInput = false;
  while (selection < 1 || selection > 5 || badInput)
  {
    badInput = false; //resets bad input
    cout << endl
         << "Select an option from the menu below:" << endl
         << "1) Description of the protein" << endl
         << "2) Protein sequence" << endl
         << "3) Protein statistics" << endl
         << "4) Record protein to file" << endl
         << "5) Return to main menu" << endl;
    cin >> selection;
    badInput = cin.fail();
    if (badInput || selection < 1 || selection > 5)
    {
      cin.clear();
      cin.ignore(10, '\n');
      cout << "Invalid input. Please enter a value between 1 and 6.";
    }
  }

  int counters[26] = {};
  ofstream outFile;
  switch (selection) {
    case 1:
      cout << endl << p << endl;
      protMenu(p);
      break;
    case 2:
      cout << endl << "Protein sequence:" << endl;
      cout << p.get_sequence() << endl;
      protMenu(p);
      break;
    case 3:
      for (char& c : p.get_sequence()) {
        if ((c-int('A')) <= 9) {
          counters[c - int('A')]++;
        }
        else if (((c-int('A')) > 9) && ((c-int('A')) <= 14)) {
          counters[c - int('A') - 1]++;
        }
        else if (((c-int('A')) > 14) && ((c-int('A')) < 26)) {
          counters[c - int('A') - 2]++;
        }
        else if (int(c) == 42) {
          counters[24]++;
        }
        else if (int(c) == 45) {
          counters[25]++;
        }
      }
      cout << endl << "Protein statistics:" << endl;
      for (int j = 0 ; j < 13 ; j++) {
        if (j < 9) { //for printing the two columns A-I and P-Y
        cout << char(int('A')+j) << ((counters[j] > 9) ? "  " : "   ") << counters[j] << "    " << char(int('P')+j) << ((counters[j+13] > 9) ? "  " : "   ") << counters[j+13] << endl;
        }
        else {//prints the remainders of the two columns
        cout << char(int('A')+j+1) << ((counters[j] > 9) ? "  " : "   ") << counters[j] << "    " << ((j < 11) ? char(int('P')+j) : char(42+3*(j-11))) << ((counters[j+13] > 9) ? "  " : "   ") << counters[j+13] << endl;
        }
      }
      protMenu(p);
      break;
    case 4:
      outFile.open("selected_proteins.txt", std::ios::app);
      outFile << p << endl
              << "Sequence is:" << endl
              << p.get_sequence() << endl << endl;
      outFile.close();
      cout << endl << "Protein successfully written to file." << endl;
      protMenu(p);
      break;
    default:
      cout << "Not available yet.";
      break;
  }
}

int main()
{
  system("CLS");
  cout << endl << "Welcome to the Protein Database" << endl;

  fileMenu();

  return 0;
}