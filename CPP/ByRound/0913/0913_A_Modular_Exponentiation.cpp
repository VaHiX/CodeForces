// Problem: CF 913 A - Modular Exponentiation
// https://codeforces.com/contest/913/problem/A

/*
Algorithm: Modular Exponentiation Reverse
Purpose: Given integers n and m, calculate m % (2^n)
Techniques: Direct computation with early termination optimization

Time Complexity: O(log n)
Space Complexity: O(1)

Approach:
1. Start with x = 2 and y = 1
2. Keep doubling x and incrementing y until y >= n
3. If at any point x > m, output m directly (since m % x = m when m < x)
4. If x == m, output 0 (since m is divisible by 2^n)
5. Otherwise, output m % x

This works because we are checking if 2^n <= m.
If 2^n > m, then m % 2^n = m.
If 2^n = m, then m % 2^n = 0.
If 2^n < m, then we compute m % 2^n directly.
*/
#include <cstdio>
#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define N 150010
#define inf 1000000000
#define pp pair<int, int>
using namespace std;
int main() {
  ll i, j, k;
  ll n, m;
  ll x, y;
  cin >> n >> m;
  x = 2;
  y = 1;
  // Loop until we reach or exceed 2^n
  while (y < n) {
    // Early termination: if 2^y > m, then m % 2^y = m
    if (x > m) {
      cout << m << endl;
      return 0;
    }
    x *= 2; // x becomes 2^(y+1)
    y++;    // increment y
  }
  // If x equals m, then m is divisible by 2^n, so remainder is 0
  if (x == m)
    cout << '0' << endl;
  else
    // Otherwise compute m % 2^n
    cout << (m % x) << endl;
  return 0;
}

// https://github.com/VaHiX/CodeForces/