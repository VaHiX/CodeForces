// Problem: CF 1372 C - Omkar and Baseball
// https://codeforces.com/contest/1372/problem/C

/*
C. Omkar and Baseball
Purpose: Given a permutation of integers from 1 to n, find the minimum number of "special exchanges"
         needed to sort the array. A special exchange is a subarray permutation where no element remains
         in its original position.

Algorithms/Techniques: 
    - Greedy approach to count segments where the permutation is not in order.
    - The key observation is that each "disordered" segment requires at least one special exchange,
      and consecutive disordered segments can be fixed with 1 or 2 exchanges depending on overlap.

Time Complexity: O(n) per test case, since we process each element once.
Space Complexity: O(1) - only using constant extra space.

*/

#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool state(true); // Tracks if current position matches expected value
    long cnt(0);      // Counts how many segments need fixing
    
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      
      // If the current element is not in its correct position and the previous segment was ordered,
      // increment the counter (indicating a new disordered segment)
      cnt += (state && p != x);
      
      // Update state: if current position matches expected value, we're in a good segment
      state = (p == x);
    }
    
    // Output minimum exchanges needed:
    // If less than 2 segments are disordered, that's the answer.
    // Otherwise, at most 2 exchanges are required.
    printf("%ld\n", (cnt < 2) ? cnt : 2);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/