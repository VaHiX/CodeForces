/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <iostream>
using namespace std;

int main() {
  const string greeting = "hello";
  string line;
  getline(cin, line);
  int a = 0, b = 0;
  string output = "NO";
  while (b < line.size()) {
    if (line[b++] == greeting[a]) {
      a++;
    }
    if (a >= greeting.size()) {
      output = "YES";
      break;
    }
  }
  cout << output << endl;
  return 0;
}
