// Problem: CF 1980 B - Choosing Cubes
// https://codeforces.com/contest/1980/problem/B

/*
B. Choosing Cubes

Algorithm:
- For each test case, we determine whether the favorite cube (at index f) will definitely be removed, 
  definitely not be removed, or could go either way after sorting and removing the first k cubes.
- We use a counting approach to classify all cubes based on their value relative to the favorite cube's value:
    - bcnt: number of cubes with value greater than favorite cube
    - cnt: number of cubes with value equal to favorite cube  
    - scnt: number of cubes with value less than favorite cube
- Based on k and these counts, we determine the outcome:
    - If k <= bcnt, then favorite cube is definitely removed (NO)
    - If k >= bcnt + cnt, then favorite cube is definitely not removed (YES)  
    - Otherwise, it may or may not be removed depending on exact arrangements (MAYBE)

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the array of cubes

*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, f, k;
    scanf("%ld %ld %ld", &n, &f, &k);
    std::vector<long> v(n);
    --f; // Convert to 0-based indexing
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    long scnt(0), bcnt(0), cnt(0); // Counters for smaller, bigger, and equal values
    for (long p = 0; p < n; p++) {
      if (v[p] > v[f]) { // Value is greater than favorite cube's value
        ++bcnt;
      } else if (v[p] == v[f]) { // Value equals favorite cube's value
        ++cnt;
      } else { // Value is less than favorite cube's value
        ++scnt;
      }
    }
    if (k <= bcnt) {
      puts("NO"); // Favorite cube is definitely removed
    } else if (k >= bcnt + cnt) {
      puts("YES"); // Favorite cube is definitely not removed
    } else {
      puts("MAYBE"); // Favorite cube may or may not be removed
    }
  }
}


// https://github.com/VaHiX/codeForces/