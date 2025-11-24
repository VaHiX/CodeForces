// Problem: CF 2029 E - Common Generator
// https://codeforces.com/contest/2029/problem/E

/*
Algorithm/Techniques: 
- Sieve of Eratosthenes to precompute smallest prime factor (SPF) for all numbers up to 4*10^5.
- For each test case, we sort the array and use the SPF to check if there exists a common generator x.
- A number x is a generator of y if we can reach y from x by repeatedly adding divisors of x.
- Key insight: If the smallest prime factor of a number is known, we can simulate operations efficiently.
- Time Complexity: O(n log n + MAXN log log MAXN) where MAXN = 4*10^5.
  - Sorting: O(n log n)
  - Sieve preprocessing: O(MAXN log log MAXN)
  - Each test case: O(n)
- Space Complexity: O(MAXN) for storing sieve array.

The sieve array stores the smallest prime factor (SPF) of each number up to 4*10^5.
This allows us to efficiently determine divisors and simulate operations.
*/
#include <algorithm>
#include <iostream>

#define MAXN 400069
#define enl '\n'
using namespace std;
int sieve[MAXN];

void testcase() {
  int n;
  cin >> n;
  int a[n];
  for (int i = 0; i < n; i++)
    cin >> a[i];
  sort(a, a + n);
  int p = 2;
  // If the smallest prime factor of the first element equals the element itself,
  // then it's a prime number. In that case, set p to be that prime.
  if (sieve[a[0]] == a[0])
    p = a[0];
  // Iterate through the sorted array to check if a valid generator x exists.
  for (int i = 1; i < n; i++)
    // If the difference between a[i] and its smallest prime factor is less than 2*p,
    // and a[i] is not equal to 2*p, then no common generator exists.
    if (a[i] - sieve[a[i]] < 2 * p && a[i] != 2 * p) {
      cout << -1 << enl;
      return;
    }
  cout << p << enl;
}

signed main() {
  cin.tie(0)->sync_with_stdio(false);
  int t;
  cin >> t;
  // Precompute smallest prime factors using sieve of Eratosthenes
  for (int i = 2; i <= (int)4e5; i++)
    if (!sieve[i])
      for (int j = i; j <= (int)4e5; j += i)
        if (!sieve[j])
          sieve[j] = i;
  while (t--)
    testcase();
  return 0;
}


// https://github.com/VaHiX/CodeForces/