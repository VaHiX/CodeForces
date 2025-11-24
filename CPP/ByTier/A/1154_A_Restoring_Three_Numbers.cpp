// Problem: CF 1154 A - Restoring Three Numbers
// https://codeforces.com/contest/1154/problem/A

/*
Algorithm: 
The problem gives us four values which are pairwise sums of three unknown positive integers a, b, c and their total sum (a+b+c).
We can deduce the individual values using the fact that:
- If we sort the four numbers, the largest one is a+b+c.
- The other three are a+b, a+c, b+c.
- By subtracting each of these three from the total sum a+b+c, we get the individual values.

Steps:
1. Read the four numbers into an array.
2. Sort the array.
3. The last element is the total sum (a+b+c).
4. Subtract the first three elements from the last to get a, b, c.

Time Complexity: O(1) - sorting 4 elements is constant time.
Space Complexity: O(1) - only using a fixed-size vector.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  const long n = 4;
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end()); // Sort the four numbers
  printf("%ld %ld %ld\n", a[n - 1] - a[0], a[n - 1] - a[1], a[n - 1] - a[2]);
  // a[n-1] is the total sum a+b+c
  // a[0], a[1], a[2] are the pairwise sums a+b, a+c, b+c (in sorted order)
  // Subtract them to get individual values
  return 0;
}


// https://github.com/VaHiX/CodeForces/