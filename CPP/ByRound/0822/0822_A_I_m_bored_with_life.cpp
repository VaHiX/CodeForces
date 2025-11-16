// Problem: CF 822 A - I'm bored with life
// https://codeforces.com/contest/822/problem/A

/*
Purpose: This program calculates the greatest common divisor (GCD) of two factorials A! and B!.
         Since one factorial is always a multiple of the smaller one (if A >= B, then B! divides A!),
         the GCD of A! and B! is simply the smaller factorial.
         
Algorithm: 
- Read two integers A and B.
- Find the minimum of A and B.
- Compute the factorial of the minimum value.
- Output the result.

Time Complexity: O(min(A, B)) - We compute the factorial of the smaller number.
Space Complexity: O(1) - Only a few variables are used, no extra space.

*/
#include <algorithm>
#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in\n");
#define NL printf("\n");
#define inf 1000000000000
using namespace std;

int main() {
  ll i, j, k;
  ll n, m, x;
  cin >> n >> m;
  x = min(n, m);  // Find the smaller of the two numbers
  k = 1;
  while (x > 0) {
    k *= x;   // Compute factorial of x
    x--;
  }
  cout << k;
  return 0;
}


// https://github.com/VaHiX/CodeForces/