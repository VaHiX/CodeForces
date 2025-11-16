// Problem: CF 1744 E1 - Divisible Numbers (easy version)
// https://codeforces.com/contest/1744/problem/E1

/*
Algorithm: 
- For each x in range (a, c], calculate the gcd of (a*b) and x.
- Use the gcd to compute k = (a*b) / gcd.
- Check if there exists a valid y in range (b, d] such that x*y is divisible by a*b.
- If such a y exists, output x and y, else continue searching.
- If no valid pair is found after checking all x, output -1 -1.

Time Complexity: O((c - a) * log(a*b)) where log(a*b) is for GCD computation.
Space Complexity: O(1) - only using a few variables.
*/

#include <algorithm>
#include <iostream>

typedef long long ll;
using namespace std;

int main() {
  int n;
  cin >> n;
  while (n--) {
    ll a, b, c, d, k, h = 1, m;
    cin >> a >> b >> c >> d;
    
    // Iterate through all possible values of x in range (a, c]
    for (ll x = a + 1; x <= c; x++) {
      m = __gcd(a * b, x); // Compute GCD of (a*b) and x
      k = a * b / m;       // Calculate k = (a*b) / gcd(a*b, x)
      
      // If b/k != d/k, there exists a valid y in range (b, d]
      // We compute y as (b/k + 1) * k which ensures that x*y is divisible by a*b
      if (b / k != d / k) {
        cout << x << " " << (b / k + 1) * k << endl;
        h = 0;
        break;
      }
    }
    
    // If no valid pair was found, output -1 -1
    if (h == 1) {
      cout << -1 << " " << -1 << endl;
    }
  }
}


// https://github.com/VaHiX/CodeForces/