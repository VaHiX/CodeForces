// Problem: CF 1546 A - AquaMoon and Two Arrays
// https://codeforces.com/contest/1546/problem/A

/*
A. AquaMoon and Two Arrays
Algorithm: Greedy + Simulation
Time Complexity: O(n^2) per test case
Space Complexity: O(n) per test case

The problem is about making two arrays equal using operations where we can transfer 
1 unit from any element of array 'a' to another element of 'a'.

Key insight:
- If sum(a) != sum(b), it's impossible to make them equal.
- Otherwise, we need to balance the differences between a and b.
- For each position i:
  - If a[i] < b[i], we need to add (b[i] - a[i]) units to this position.
  - If a[i] > b[i], we need to remove (a[i] - b[i]) units from this position.
- We can transfer units greedily: whenever we have excess at position i, 
  we transfer them to positions with deficit.

Approach:
1. Check if sums are equal; if not, output -1.
2. Identify positions where a[i] < b[i] (need more) and a[i] > b[i] (have excess).
3. For each "excess" position, we need to transfer units to "deficit" positions.
4. Build lists of "plus" and "minus" indices to track who needs what.
5. Match the excesses with deficits by creating transfer operations.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n), b(n);
    long sa(0), sb(0);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      sa += a[p]; // accumulate sum of array a
    }
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
      sb += b[p]; // accumulate sum of array b
    }
    if (sa != sb) { // check if sums are equal
      puts("-1");
      continue;
    }
    std::vector<long> plus, minus; // stores indices that need more and have extra units
    for (long p = 0; p < n; p++) {
      if (a[p] < b[p]) { // if current element of a is less than b, we need more
        for (long u = 0; u < b[p] - a[p]; u++) { // for each unit needed
          plus.push_back(p + 1); // store 1-based index
        }
      } else if (a[p] > b[p]) { // if current element of a is greater than b, we have excess
        for (long u = 0; u < a[p] - b[p]; u++) { // for each unit to transfer
          minus.push_back(p + 1); // store 1-based index
        }
      }
    }
    printf("%ld\n", plus.size()); // number of operations equals number of units to move
    for (long p = 0; p < plus.size(); p++) {
      printf("%ld %ld\n", minus[p], plus[p]); // output transfer operation: from minus[p] to plus[p]
    }
  }
}


// https://github.com/VaHiX/codeForces/