// Problem: CF 818 D - Multicolored Cars
// https://codeforces.com/contest/818/problem/D

/*
Algorithm/Technique: Simulation with Map
Time Complexity: O(n log n) - due to map operations (insertion and iteration)
Space Complexity: O(n) - for storing counts in map and array

The problem requires finding a color B such that Bob wins the game against Alice's color A.
For Bob to win, at every step i, count of B must be greater than or equal to count of A.
This means that for every prefix of the array, the number of occurrences of B should be at least as much as A.
We simulate the process and track for each color, the maximum count of B that can be achieved,
while ensuring B's count remains at least equal to A's count at all times.
*/

#include <iostream>
#include <map>
#include <utility>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in\n");
#define NL printf("\n");
#define inf 1000000000000
using namespace std;

int main() {
  ll i, j, k;
  ll n, m, aa;
  cin >> n >> aa;
  ll a[n];
  map<ll, ll> mp; // map to store count of each color seen so far
  for (i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] == aa) {
      mp[aa]++; // increment count for Alice's color
      continue;
    }
    if (mp[a[i]] != -1) { // if color not marked as invalid
      if (mp[aa] <= mp[a[i]])
        mp[a[i]]++; // increment the count for this color
      else
        mp[a[i]] = -1; // mark this color as invalid (can't win)
    }
  }
  j = -1;
  map<ll, ll>::iterator p = mp.begin();
  while (p != mp.end()) {
    if (p->second != -1 && p->first != aa && p->second >= mp[aa]) {
      j = p->first; // first valid winning color found
      break;
    }
    p++;
  }
  cout << j;
  return 0;
}


// https://github.com/VaHiX/CodeForces/