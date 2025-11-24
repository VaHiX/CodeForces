// Problem: CF 1698 G - Long Binary String
// https://codeforces.com/contest/1698/problem/G

/*
Algorithm: The problem is about finding the lexicographically largest binary string t with exactly two 1-bits after applying XOR operations with string s. 
We simulate operations and track state transitions using a bitmask approach.
The key is to detect cycles in the state transitions (since we only have 35 bits, the number of states is manageable).

Time Complexity: O(N * 2^N) where N is the length of string s (at most 35).
Space Complexity: O(2^N) - storing the mapping of states to indices.

Techniques:
- Bit manipulation
- State cycle detection using hash map
- Simulation of bit operations on a large binary string
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <string>

using namespace std;
typedef long long LL;
const int N = 2e5;
int n, m;
string s;
LL p[N + 5];
map<LL, int> mp;
int main() {
  cin >> s;
  int cnt = 1;
  // Skip leading zeros to find the first '1'
  while (s.size() && s[0] == '0')
    s = s.substr(1), cnt++;
  if (!s.size()) {
    puts("-1");
    return 0;
  }
  n = s.size();
  LL w = 0;
  // Convert string s to a bitmask w for XOR operations
  for (int i = 0; i < n; i++)
    w |= ((LL)(s[i] - '0') << i);
  LL t = 1;
  // Precompute powers of 2 and simulate their XOR behavior
  for (int i = 0; i < N; i++) {
    mp[t] = i;
    if (t & 1)
      t ^= w;
    t >>= 1;
    p[i + 1] = t;
  }
  w = 1;
  // Simulate until we reach a state that was seen before (cycle detection)
  for (int i = 1; i <= N; i++) {
    t = 0;
    // Compute the new state by XORing with the relevant precomputed values
    for (int j = 0; j < n; j++)
      if (w & (1ll << j))
        t ^= p[N - j];
    w = t;
    // If current state was seen before, a cycle is detected
    if (mp.count(w)) {
      cout << cnt << " " << (LL)i * N + cnt - mp[w] << endl;
      return 0;
    }
  }
  puts("-1");
  return 0;
}


// https://github.com/VaHiX/CodeForces/