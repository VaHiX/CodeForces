// Problem: CF 1796 F - Strange Triples
// https://codeforces.com/contest/1796/problem/F

/*
Problem: Count the number of "strange triples" (a, b, n) such that concatenation an / nb = a / b
Algorithms/Techniques: Mathematical analysis of the equation, precomputed powers of 10, divisor enumeration, and use of GCD for optimization.

Time Complexity: O(sqrt(N) * log(N) * MAXLEN^2 * A * B)
Space Complexity: O(A * B)

The approach involves:
1. Iterating over possible lengths of n (1 to 9)
2. For each length, factorizing the value derived from concatenation constraints
3. Using the divisibility and GCD properties to find valid combinations
4. Storing unique valid triples in a set to avoid duplicates
5. Final check of the actual formula to confirm valid triples and sum up the count.
*/

#include <assert.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;
#define sz(a) int((a).size())
using li = long long;
const int MAXLEN = 5;
vector<int> divs(int x) {
  vector<int> res;
  for (int i = 1; i * i <= x; ++i) {
    if (x % i == 0) {
      res.push_back(i);
      if (i * i != x)
        res.push_back(x / i);
    }
  }
  return res;
}
int main() {
  int A, B, N;
  cin >> A >> B >> N;
  vector<int> pw(10);
  pw[0] = 1;
  for (int i = 1; i < 10; ++i)
    pw[i] = pw[i - 1] * 10;
  int PW = pw[MAXLEN];
  set<array<int, 3>> used;  // Store unique valid triples
  vector<int> len(PW);
  for (int i = 0; i < PW; ++i)
    len[i] = sz(to_string(i));
  for (int lenn = 1; lenn <= 9; ++lenn) {
    int x = pw[lenn] - 1;  // Calculate base for concatenation
    for (int k2 : divs(x)) {  // Iterate over divisors of x
      int r = x / k2;
      for (int d = 1; d < PW; ++d) {  // Iterate over all possible values of d
        for (int lenb = len[d]; lenb <= MAXLEN; ++lenb) {  // Iterate over lengths of b
          int bg = pw[lenb] - d * li(r) % pw[lenb];  // Calculate bg based on constraints
          int dd = d / __gcd(d, bg);  // Simplify fraction to avoid duplicate checks
          int lb = (pw[lenb - 1] + bg - 1) / bg;
          int rb = (pw[lenb] - 1) / bg;
          for (int g = (lb + dd - 1) / dd * dd; g <= rb; g += dd) {  // Iterate over valid g values
            int b = bg * g;
            assert(b % d == 0);  // Ensure divisibility check
            if (b >= B || __gcd(b / d, r) != 1)  // Skip invalid b or ensure relative primality
              continue;
            int ag = (d * li(r) + bg) / pw[lenb];  // Derive ag
            li n = b / d * li(k2) * ag;  // Compute n
            if (n < N && ag * g < A && __gcd(ag, bg) == 1 &&  // Check bounds and co-prime conditions
                sz(to_string(n)) == lenn)
              used.insert({ag * g, b, n});  // Insert triple into set if valid
          }
        }
      }
    }
  }
  int res = 0;
  for (auto it : used) {
    li a = it[0], b = it[1], n = it[2];
    int lenn = sz(to_string(n));
    int lenb = sz(to_string(b));
    res += a * b * pw[lenn] + n * b == a * n * pw[lenb] + a * b;  // Final validation of the equation
  }
  cout << res << endl;
}


// https://github.com/VaHiX/CodeForces/