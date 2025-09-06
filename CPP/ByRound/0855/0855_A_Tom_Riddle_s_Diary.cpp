/*
 * Problem URL : https://codeforces.com/contest/855/problem/A
 * Submit Date : 2025-08-31
 */

/*
 * Problem URL : https://codeforces.com/contest/855/problem/A
 * Submit Date : 2025-08-31
 */



#include <bits/stdc++.h>

typedef long long int ll;

#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, int>
#define mod 1000000007

using namespace std;

int main() {

  int i, j, k;
  int n, m;
  string s;

  scanf("%d%d", &n);

  map<string, int> mp;
  while (n--) {
    cin >> s;

    if (!mp[s])
      cout << "NO" << endl;
    else
      cout << "YES" << endl;

    mp[s]++;
  }

  return 0;
}
