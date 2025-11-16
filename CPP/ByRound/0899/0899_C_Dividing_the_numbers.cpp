// Problem: CF 899 C - Dividing the numbers
// https://codeforces.com/contest/899/problem/C

/*
 * Problem: Dividing the numbers
 * 
 * Approach:
 * The goal is to split integers 1 to n into two non-empty groups such that 
 * the absolute difference of their sums is minimized.
 * 
 * Key Insight:
 * - If n % 4 == 0: The sum of all numbers is divisible by 2, so we can split 
 *   them evenly.
 * - If n % 4 == 1: We must leave one number out to make the sums equal; 
 *   placing 1 in one group and distributing the rest to balance.
 * - If n % 4 == 2: We can split into two groups of equal sums by placing 
 *   1 in one group and 2 in another, then proceed.
 * - If n % 4 == 3: We can again balance the sums after placing the first 
 *   three numbers optimally.
 * 
 * The algorithm:
 * 1. Based on n % 4, we determine which numbers to put in the first group
 *    to minimize difference.
 * 2. For remaining numbers, we follow a pattern of placing numbers in groups
 *    alternately in a way to balance the sums.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a, b; // a and b are the two groups
  long m = n % 4;
  long diff(0);
  
  // Handle base cases based on remainder when dividing n by 4
  if (m == 1) {
    a.push_back(1);  // Put 1 in group a
    diff = 1;        // Difference is 1 since we have one extra
  } else if (m == 2) {
    a.push_back(1);  // Put 1 in group a
    b.push_back(2);  // Put 2 in group b
    diff = 1;        // Difference is 1
  } else if (m == 3) {
    a.push_back(1);  // Put 1 in group a
    a.push_back(2);  // Put 2 in group a
    b.push_back(3);  // Put 3 in group b
  }
  
  // Distribute remaining numbers (from m+1 to n) between groups a and b
  for (long p = m + 1, cnt = 0; p <= n; p++) {
    if (cnt % 4 == 0 || cnt % 4 == 3) {
      a.push_back(p);  // Add to group a
    } else {
      b.push_back(p);  // Add to group b
    }
    ++cnt;
    cnt %= 4;  // Cycle through 0,1,2,3
  }
  
  // Print result
  printf("%ld\n%ld ", diff, a.size());
  for (long p = 0; p < a.size(); p++) {
    printf("%ld ", a[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/