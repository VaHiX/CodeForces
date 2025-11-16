// Problem: CF 787 B - Not Afraid
// https://codeforces.com/contest/787/problem/B

/*
 * Purpose: Determine if there's a scenario where all members of at least one group are traitors.
 * Algorithm: For each group, count how many Ricks and Mortys joined. If for any universe,
 *            both a Rick and a Morty joined the same group, then it's possible to assign
 *            traitors such that all members of that group are traitors.
 * Time Complexity: O(m * k) where m is number of groups and k is total number of members across all groups
 * Space Complexity: O(n) where n is number of universes
 */
#include <string.h>
#include <iostream>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, ll>
#define inf 1000000000
using namespace std;
int main() {
  int i, j, k;
  int n, m, x;
  cin >> n >> m;
  int pos[n + 1], neg[n + 1];  // pos[i] counts Mortys from universe i, neg[i] counts Ricks from universe i
  for (i = 0; i < m; i++) {
    cin >> k;
    memset(pos, 0, sizeof(pos));  // Reset counters for each group
    memset(neg, 0, sizeof(neg));
    for (j = 0; j < k; j++) {
      cin >> x;
      if (x > 0)
        pos[x]++;  // Morty from universe x joined this group
      else
        neg[x * -1]++;  // Rick from universe -x joined this group
    }
    bool f = 0;
    for (j = 1; j <= n; j++) {
      if (pos[j] && neg[j]) {  // If both Rick and Morty from same universe joined this group
        f = 1;
        break;
      }
    }
    if (!f) {  // No universe has both Rick and Morty in this group, so possibility exists to make all traitors
      cout << "YES";
      return 0;
    }
  }
  cout << "NO";  // For all groups, there exists at least one universe where only one type of person joined
  return 0;
}


// https://github.com/VaHiX/CodeForces/