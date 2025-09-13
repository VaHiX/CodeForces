/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <iostream>
using namespace std;

int main() {
  string first;
  getline(cin, first);
  string second;
  getline(cin, second);
  int comparison = 0;
  for (int k = 0; k < first.size(); ++k) {
    if (tolower(first[k]) < tolower(second[k])) {
      comparison = -1;
      break;
    }
    if (tolower(first[k]) > tolower(second[k])) {
      comparison = 1;
      break;
    }
  }
  printf("%d\n", comparison);
  return 0;
}
