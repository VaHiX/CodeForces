// Problem: CF 1692 F - 3SUM
// https://codeforces.com/contest/1692/problem/F

/*
F. 3SUM

Algorithm: 
- For each test case, we process an array of integers and check if there exist three distinct indices such that the sum of their values ends in digit 3.
- We use modular arithmetic: since we only care about the last digit of the sum, we can work with remainders modulo 10.
- Count frequency of each remainder (0 to 9) from input numbers.
- Try all combinations of three remainders (p, q, r) such that (p + q + r) % 10 == 3.
- Check if enough elements with those remainders exist.

Time Complexity: O(n + B^3) where n is the total number of elements across all test cases and B = 10.
Space Complexity: O(B) = O(1) because we use a fixed-size array cnt of size 10.

Input:
- First line contains t (number of test cases)
- For each test case:
  - First line contains n (array length)
  - Second line contains n integers

Output:
- For each test case: "YES" if such triplet exists, "NO" otherwise
*/

#include <cstdio>
int main() {
  const int B = 10; // B is the base (10 for decimal digits)
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt[B] = {0}; // Count of each remainder (0 to 9)
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++cnt[x % B]; // Increment count of remainder
    }
    bool res(false); // Flag to store result
    for (long p = 0; !res && p < B; p++) { // Iterate through all possible remainders for first element
      for (long q = p; !res && q < B; q++) { // Second element, start from p to avoid duplicates
        for (long r = q; !res && r < B; r++) { // Third element, start from q
          if ((p + q + r) % 10 != 3) { // If sum of remainders does not end in 3, skip
            continue;
          }
          --cnt[p]; // Temporarily reduce count for p
          --cnt[q]; // Temporarily reduce count for q
          --cnt[r]; // Temporarily reduce count for r
          if (cnt[p] >= 0 && cnt[q] >= 0 && cnt[r] >= 0) { // If enough elements are left
            res = true; // Found valid combination
          }
          ++cnt[p]; // Restore count of p
          ++cnt[q]; // Restore count of q
          ++cnt[r]; // Restore count of r
        }
      }
    }
    puts(res ? "YES" : "NO"); // Output result
  }
}


// https://github.com/VaHiX/codeForces/