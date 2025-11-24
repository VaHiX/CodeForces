// Problem: CF 749 A - Bachgold Problem
// https://codeforces.com/contest/749/problem/A

/*
Algorithm: Bachgold Problem
Techniques: Greedy approach, Prime number properties
Time Complexity: O(1) - The algorithm performs a constant number of operations regardless of input size.
Space Complexity: O(1) - Only a constant amount of extra space is used.

The problem asks to represent a given integer n as a sum of the maximum possible number of prime numbers.
Key observations:
- The smallest prime is 2, so to maximize the count of primes, we should use as many 2s as possible.
- If n is even, we can write it as sum of n/2 twos.
- If n is odd, we can write it as (n-3)/2 twos and one 3.
This greedy approach ensures the maximum number of primes.
*/

#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in");
#define NL printf("\n");
#define inf 1000000000000
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j, k;
  ll n, w, q;
  cin >> n;
  if (n % 2) { // If n is odd
    if (n == 3) { // Special case: n = 3, use only one prime (3)
      cout << "1" << endl << "3";
    } else { // For odd n > 3
      n -= 3; // Subtract 3 to make it even
      cout << (n / 2) + 1 << endl; // Print count of primes (n/2 twos + one 3)
      for (i = 0; i < n / 2; i++) // Print (n/2) twos
        cout << "2 ";
      cout << "3"; // Print one 3
    }
  } else { // If n is even
    cout << n / 2 << endl; // Print count of primes (n/2 twos)
    for (i = 0; i < n / 2; i++) // Print n/2 twos
      cout << "2 ";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/