// Problem: CF 978 D - Almost Arithmetic Progression
// https://codeforces.com/contest/978/problem/D

/*
Code purpose:
This program determines the minimum number of elements in a sequence that need to be changed by at most 1 
to form an arithmetic progression. It tries all possible combinations of changes for the first two elements 
and computes the resulting number of changes needed for the rest of the sequence.

Algorithms/Techniques:
- Brute-force over all possible adjustments for first two elements (each can be adjusted by -1, 0, or +1)
- For each valid pair of adjustments, compute the common difference of the arithmetic progression
- Then validate if the rest of the elements can be adjusted to fit this progression with at most 1 change

Time Complexity: O(n) where n is the length of the sequence. The nested loops over -1, 0, 1 for first two elements 
give constant time complexity O(3*3) = O(1), so overall is O(n).

Space Complexity: O(n) for storing the input sequence.
*/

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  if (n <= 2) {
    puts("0");
  } else {
    long minCnt(-1);
    for (long x = -1; x <= 1; x++) {  // Try all possible changes for first element
      long s = a[0] + x;              // s is the adjusted value of first element
      for (long y = -1; y <= 1; y++) { // Try all possible changes for second element
        long d = a[1] + y - s;        // Compute the common difference
        long cnt = (x != 0) + (y != 0); // Count changes made to first two elements
        for (long p = 2; p < n; p++) {
          long expected = s + p * d;    // Compute what the element should be in AP
          if (a[p] == expected) {
            continue; // No change needed
          } else if ((a[p] == expected + 1) || (a[p] == expected - 1)) {
            ++cnt;    // One change needed to make it fit
          } else {
            cnt = -1; // Impossible to form AP
            break;
          }
        }
        if (cnt >= 0) {
          if ((minCnt < 0) || (cnt < minCnt)) {
            minCnt = cnt; // Update minimum changes if needed
          }
        }
      }
    }
    printf("%ld\n", minCnt);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/