/*
 * Problem URL : https://codeforces.com/contest/556/problem/A
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/556/problem/A
 * Submit Date : 2025-09-02
 */



#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int i, j, k;
  int n;
  int z = 0, o = 0;

  cin >> n;
  char s[n];
  cin >> s;

  for (i = 0; i < strlen(s); i++) {
    if (s[i] == '0')
      z++;
    else
      o++;
  }

  cout << abs(o - z) << endl;

  return 0;
}
