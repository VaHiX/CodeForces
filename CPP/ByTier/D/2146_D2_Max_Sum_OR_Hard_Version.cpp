// Problem: CF 2146 D2 - Max Sum OR (Hard Version)
// https://codeforces.com/contest/2146/problem/D2

/*
D2. Max Sum OR (Hard Version)
Algorithm: Recursive divide-and-conquer approach to reorder array elements to maximize bitwise OR sum
Time Complexity: O(30 * n) where n = r - l + 1, since we process at most 30 bits
Space Complexity: O(n) for the map storing the reordering

The algorithm works by recursively dividing the range [l, r] based on the most significant bit,
and swapping elements in a way that maximizes OR values. The key insight is to pair elements
so that their OR results are as large as possible.
*/

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <map>

typedef long long int64;
std::map<int64, int64> a;

// Recursive function to reorder elements in range [l, r] 
void Divide(int d, int64 mid, int64 l, int64 r) {
  if (d < 0)
    return; // Base case: no more bits to process
  if (l > r)
    assert(0); // Invalid range
  if (l == r)
    return (void)(a[l] = l); // Base case: single element, map it to itself

  // Adjust mid point if needed to handle edge cases
  if (mid < l)
    return Divide(d - 1, mid + (1LL << (d - 1)), l, r);
  if (mid > r)
    return Divide(d - 1, mid - (1LL << (d - 1)), l, r);

  // Pair elements around the midpoint to maximize OR
  int64 c = std::min(r - mid + 1, mid - l); // Number of pairs to process
  for (int64 i = 0; i < c; ++i) {
    a[mid - i - 1] = mid + i;     // Assign values to achieve maximum OR
    a[mid + i] = mid - i - 1;
  }

  // Recursively process the remaining portions of the range
  if (r - mid + 1 == mid - l)
    return;
  if (r - mid + 1 > mid - l)
    Divide(d - 1, mid + (1LL << (d - 1)), mid + c, r); // Process right half
  else
    Divide(d - 1, mid - (1LL << (d - 1)), l, mid - c - 1); // Process left half
}

void work() {
  a.clear();
  int64 l, r;
  std::cin >> l >> r;
  Divide(30, 1LL << 30, l, r); // Start recursion with full range

  int64 ans = 0;
  for (int64 i = l; i <= r; ++i)
    ans += a[i] | i; // Calculate total OR sum
  std::cout << ans << '\n';

  for (int64 i = l; i <= r; ++i)
    std::cout << a[i] << " \n"[i == r]; // Output reordered array
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int T = 1;
  std::cin >> T;
  for (; T--;)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/