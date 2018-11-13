#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main() {

string str;
str = "MAVASTSTSDGMLTLDLIQEEDPSPEEPTSCAESFRVDLDKSVAQLAGSRRRADSDRIQPSADRASSLSRPWEKTDKGATYTPQAPKKLTPTEKGRCASLEEILSQRDAASARTLQLRAEEPPTPALPNPGQLSRIQDLVARKLEETQELLAEVQGLGDGKRKAKDPPRSPPDSESEQLLLETERLLGEASSNWSQAKRVLQEVRELRDLYRQMDLQTPDSHLRQTTPHSQYRKSLM";
int counters[26] = {};
for (char& c : str) {
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

for (int j = 0 ; j < 13 ; j++) {
  if (j < 9) { //for printing the two columns A-I and P-Y
  cout << char(int('A')+j) << ((counters[j] > 9) ? "  " : "   ") << counters[j] << "    " << char(int('P')+j) << ((counters[j+13] > 9) ? "  " : "   ") << counters[j+13] << endl;
  }
  else {
  cout << char(int('A')+j+1) << ((counters[j] > 9) ? "  " : "   ") << counters[j] << "    " << ((j < 11) ? char(int('P')+j) : char(42+3*(j-11))) << ((counters[j+13] > 9) ? "  " : "   ") << counters[j+13] << endl;
  }
}


return 0;
}