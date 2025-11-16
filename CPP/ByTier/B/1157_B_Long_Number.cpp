// Problem: CF 1157 B - Long Number
// https://codeforces.com/contest/1157/problem/B

/*
B. Long Number
Purpose: Given a long decimal number and a function mapping digits to other digits,
         find the maximum number possible by applying the function to at most one
         contiguous subsegment of the number.
Algorithms/Techniques: Greedy algorithm with two passes over the string.
Time Complexity: O(n) where n is the length of the string.
Space Complexity: O(1) excluding input storage.

The solution works as follows:
1. First, we find the leftmost digit that can be increased (i.e., f(digit) > digit).
2. Then we extend this segment as far right as possible while f(digit) >= digit,
   ensuring we don't decrease any digit.
3. This greedy approach ensures maximum increase with one operation.
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  const int D = 10; // Number of digits (1-9, index 0 unused)
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::vector<long> a(D); // Mapping function f(1) to f(9)
  for (long p = 1; p < D; p++) { // Read the mapping for digits 1-9
    scanf("%ld", &a[p]);
  }
  long idx(0); // Index to traverse the string
  
  // First pass: find the first digit that can be increased
  while (idx < s.size() && a[s[idx] - '0'] <= (s[idx] - '0')) {
    ++idx;
  }
  
  // Second pass: extend the segment while we can still increase or keep same value
  while (idx < s.size() && a[s[idx] - '0'] >= (s[idx] - '0')) {
    s[idx] = '0' + a[s[idx] - '0']; // Apply the function mapping
    ++idx;
  }
  
  std::cout << s << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/