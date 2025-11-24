// Problem: CF 675 A - Infinite Sequence
// https://codeforces.com/contest/675/problem/A

/*
Purpose: Determine if a given number b appears in an infinite arithmetic sequence starting with a and having a common difference c.

Algorithms/Techniques: 
- Arithmetic sequence analysis
- Modular arithmetic to check if b is a term in the sequence
- Special case handling for c = 0

Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - only using a fixed number of variables

Approach:
1. If c == 0, check if a == b (sequence is constant)
2. If c != 0, check if (b - a) is divisible by c and the quotient is non-negative
   - This ensures b is a valid term in the sequence s_i = a + (i-1)*c
*/

#include <iostream>

typedef long long int ll;
#define pp pair<ll, string>
#define inf 1000000007
#define dbg cout << "tttt" << endl;
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j, k;
  ll a, b, c;
  cin >> a >> b >> c;
  if (c == 0) {
    if (a == b)
      cout << "YES";
    else
      cout << "NO";
  } else {
    // Check if (b - a) is divisible by c and the result is non-negative
    // This means b is a term in the sequence: b = a + (i-1)*c => (b-a)/c = i-1 >= 0
    if ((b - a) % c == 0 && (b - a) / c >= 0)
      cout << "YES";
    else
      cout << "NO";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/