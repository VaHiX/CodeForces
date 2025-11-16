// Problem: CF 1041 B - Buying a TV Set
// https://codeforces.com/contest/1041/problem/B

/*
B. Buying a TV Set
Algorithm: Using GCD to reduce the ratio to its simplest form, then determine how many multiples of that simplified ratio fit within the given dimensions.

Time Complexity: O(log(min(x, y))) - due to GCD computation using Euclidean algorithm
Space Complexity: O(1) - only using a constant amount of extra space

The problem asks to count the number of valid (w, h) pairs such that:
- w <= a
- h <= b
- w/h = x/y
This is equivalent to finding how many multiples of (x/gcd(x,y), y/gcd(x,y)) fit within [1,a] x [1,b].
*/
#include <algorithm>
#include <iostream>

using namespace std;
int main() {
  long long a, b, x, y, g;
  cin >> a >> b >> x >> y;
  g = __gcd(x, y);  // Reduce the ratio to its simplest form
  x /= g;           // Simplified width component
  y /= g;           // Simplified height component
  cout << min(a / x, b / y);  // Count of valid multiples in both dimensions
}


// https://github.com/VaHiX/codeForces/