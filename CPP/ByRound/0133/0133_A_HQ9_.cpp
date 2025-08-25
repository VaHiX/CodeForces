/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <iostream>
using namespace std;

int main() {
  string line;
  getline(cin, line);
  string output = "NO";
  for (int k = 0; k < line.size(); ++k) {
    if (line[k] == 'H' || line[k] == 'Q' || line[k] == '9') {
      output = "YES";
      break;
    }
  }
  cout << output << endl;
  return 0;
}
