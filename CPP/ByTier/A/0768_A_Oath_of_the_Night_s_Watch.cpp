// Problem: CF 768 A - Oath of the Night's Watch
// https://codeforces.com/contest/768/problem/A

/*
Purpose: This code determines how many stewards Jon Snow will support based on their strengths.
         A steward is supported if there exists at least one steward with strictly less strength 
         and at least one with strictly greater strength.

Algorithms/Techniques: 
    - Single pass to find minimum and maximum strengths
    - Second pass to count stewards that are neither minimum nor maximum

Time Complexity: O(n) - Two passes through the array
Space Complexity: O(n) - Vector to store the strengths
*/
#include <iostream>
#include <vector>
int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::vector<long> a(n);
  long min(1e9 + 1), max(-1e9 - 1); // Initialize min to large value, max to small value
  for (long p = 0; p < n; p++) {
    std::cin >> a[p];
    min = (min < a[p]) ? min : a[p];  // Update minimum strength
    max = (max > a[p]) ? max : a[p];  // Update maximum strength
  }
  long count(0);
  for (long p = 0; p < n; p++) {
    count += (min < a[p] && a[p] < max); // Increment count if strength is strictly between min and max
  }
  std::cout << count << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/