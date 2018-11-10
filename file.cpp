#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

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
      cout << "Invalid input. Please enter a value 1-3.";
    }
  } while (selection < 1 || selection > 3 || badInput);
  
  return selection;
}

int main()
{

  cout << "Welcome to the Protein Database" << endl;

  int file = fileMenu();
  ifstream readData;

  switch (file)
  {
  case 1:
    readData.open("protein_a.fa");
    if (readData.fail())
    {
      cerr << "Error opening file" << endl; //cerr is a cout equivalent for errors
      exit(1);
  case 2:
    readData.open("protein_c.fa");
    if (readData.fail())
    {
      cerr << "Error opening file" << endl; //cerr is a cout equivalent for errors
      exit(1);
  default:
    return;
  }


  string readData;
  int count = 0;
  //Read a file until you've reached the end
  while (!readFile.eof()) {
    
  }

  
  readFile.close();

  return 0;
}