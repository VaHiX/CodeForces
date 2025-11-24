// Problem: CF 1702 F - Equate Multisets
// https://codeforces.com/contest/1702/problem/F

/*
Purpose: 
This code determines whether two multisets can be made equal by transforming elements of the second multiset using allowed operations (doubling or halving). 
The approach is to reduce all numbers in both multisets to their "irreducible" form (by repeatedly dividing by 2 until odd), then check if they can be matched.

Algorithms/Techniques:
- Use a map to count occurrences of each irreducible number from multiset 'a'.
- For each number in multiset 'b', reduce it to its irreducible form by dividing by 2 until odd.
- Try to match the reduced numbers from 'b' with counts in the map.
- If any number in 'b' cannot be matched, return "NO"; otherwise "YES".

Time Complexity: O(n * log(max_value)) due to division operations and map operations.
Space Complexity: O(n) for storing the map.
*/

#include <iostream>
#include <map>

#define N 200010
using namespace std;
int t, n, a, b;
map<int, int> mp;
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    mp.clear(); // Clear map for new test case
    for (int i = 1; i <= n; i++) {
      cin >> a;
      // Reduce 'a' to its odd root by dividing by 2 until odd
      while (a % 2 == 0)
        a /= 2;
      mp[a]++; // Count occurrences of this irreducible number
    }
    int fl = 0; // Flag to indicate if matching failed
    for (int i = 1; i <= n; i++) {
      cin >> b;
      // Try to find a match for 'b' in the map by halving it
      while (b && mp[b] == 0)
        b /= 2;
      if (b) {
        mp[b]--; // Use one occurrence of the matched number
      } else {
        fl = 1; // If no match found, set failure flag
      }
    }
    if (fl)
      cout << "NO\n";
    else
      cout << "YES\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/