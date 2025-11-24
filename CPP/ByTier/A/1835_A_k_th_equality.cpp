// Problem: CF 1835 A - k-th equality
// https://codeforces.com/contest/1835/problem/A

/*
Problem: Find the k-th lexicographically smallest equality a + b = c,
where a has A digits, b has B digits, and c has C digits.

Algorithms/Techniques:
- Brute-force enumeration of possible values for 'a' (first number)
- For each valid 'a', compute valid range of 'b' such that c = a + b is valid
- Use prefix sums or direct iteration to find the k-th combination

Time Complexity: O(10^(A+B)) in worst case, but due to constraints A,B,C <= 6,
and at most 5 test cases with large values, we can optimize further based on problem specifics.
Space Complexity: O(1) - only constant extra space used.

*/
#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int pw[7] = {1, 10, 100, 1000, 10000, 100000, 1000000};
int t, a, b, c;
ll n;
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d%lld", &a, &b, &c, &n);
    for (int i = pw[a - 1]; i < pw[a]; i++) { // iterate through all valid values of 'a'
      int l = max(pw[b - 1], pw[c - 1] - i), r = min(pw[b], pw[c] - i); // compute valid range for 'b'
      if (r - l < n) {
        n -= max(r - l, 0); // skip this block of possibilities
        continue;
      }
      printf("%d + %lld = %lld\n", i, l + n - 1, i + l + n - 1), n = 0; // print the k-th equality
      break;
    }
    if (n)
      puts("-1"); // no such equality exists
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/