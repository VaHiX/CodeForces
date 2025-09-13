/*
 * Problem URL : https://codeforces.com/problemset/problem/21/A
 * Submit Date : 2025-08-21
 */

#include <iostream>
#include <regex>

using namespace std;

int main() {
  string input;
  cin >> input;
  regex r("^\\w{1,16}@(\\w{1,16}\\.)*\\w{1,16}(\\/\\w{1,16})?$");
  string result = regex_match(input, r) ? "YES" : "NO";
  cout << result << endl;
  return 0;
}
