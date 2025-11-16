// Problem: CF 1593 C - Save More Mice
// https://codeforces.com/contest/1593/problem/C

/*
C. Save More Mice
Algorithm: Greedy with sorting
Time Complexity: O(k log k) per test case due to sorting
Space Complexity: O(k) for storing distances

The problem involves a cat moving from position 0 to n, and mice moving towards the hole at n.
Each second:
- One mouse moves right by 1 (if it reaches the hole, it's saved)
- Then cat moves right by 1 and eats all mice in its new position
We use a greedy strategy: sort mice by their distance to the hole and process them from closest to farthest,
trying to save as many mice as possible.

The key idea is that we want to maximize the number of mice that can reach the hole.
To do so:
1. Calculate how far each mouse is from the hole (n - x_i)
2. Sort these distances
3. Process mice greedily: for each mouse, if we have enough "time" (remaining steps) to let it reach the hole,
   then we save the mouse
4. Each time a mouse moves, the cat moves and eats all mice in its new position
*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> dist(k);
    for (long p = 0; p < k; p++) {
      long x;
      scanf("%ld", &x);
      dist[p] = n - x; // Distance from hole
    }
    sort(dist.begin(), dist.end()); // Sort distances to process greedily
    long cnt(0), rem(n); // cnt: number of saved mice, rem: remaining steps
    for (long p = 0; (rem > 0) && (p < dist.size()); p++) {
      rem -= dist[p]; // Move this mouse to the hole
      cnt += (rem > 0); // If there's still time after this move, count it as saved
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/