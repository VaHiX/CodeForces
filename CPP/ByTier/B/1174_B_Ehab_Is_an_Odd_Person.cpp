// Problem: CF 1174 B - Ehab Is an Odd Person
// https://codeforces.com/contest/1174/problem/B

/*
B. Ehab Is an Odd Person
Time Complexity: O(n log n) - due to sorting when both even and odd numbers are present
Space Complexity: O(n) - for storing the array

Algorithms/Techniques:
- Check if array contains both even and odd numbers
- If yes, sort the array to get lexicographically smallest arrangement
- If not, output original array as no swaps can be made

The key insight is that we can only swap elements if their sum is odd,
which happens when one is even and other is odd.
So if there are both even and odd numbers, we can arrange them in any order.
To get lexicographically smallest, we sort the array.
Otherwise, no swaps possible, so output as-is.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  bool odd(0), even(0); // Track if array has odd and even numbers
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    if (a[p] % 2) { // Check if number is odd
      odd = true;
    } else { // Number is even
      even = true;
    }
  }
  if (even && odd) { // If both even and odd numbers exist, we can sort
    sort(a.begin(), a.end());
  }
  for (long p = 0; p < n; p++) {
    printf("%ld ", a[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/