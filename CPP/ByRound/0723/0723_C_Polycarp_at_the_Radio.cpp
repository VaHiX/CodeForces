// Problem: CF 723 C - Polycarp at the Radio
// https://codeforces.com/contest/723/problem/C

/*
Purpose: 
This code solves the problem of reorganizing a playlist to maximize the minimum number of songs performed by bands numbered from 1 to m.
The strategy is to ensure each of the bands 1 through m has at least `n/m` songs, and minimize the number of playlist changes.

Algorithms/Techniques:
- Greedy approach to distribute songs among bands.
- Two passes: first counting existing occurrences, then modifying the playlist to achieve the desired minimum count.

Time Complexity: O(n * m) in worst case due to nested loops for adjusting counts.
Space Complexity: O(n + m) for storing the playlist and band counts.

*/
#include <cstdio>
#include <vector>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<long> a(n, 0), b(m + 1, 0); // 'a' stores playlist, 'b' stores count of each band
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    if (a[p] <= m) {
      ++b[a[p]]; // Count how many songs each band already has
    }
  }
  long chg(0), min(n / m); // 'min' is the target minimum count per band
  for (long p = 1; p <= m; p++) {
    while (b[p] < min) { // If current band has less than required minimum
      for (long q = 0; q < n && b[p] < min; q++) {
        if (a[q] > m) { // If song is from an unknown band ( > m)
          a[q] = p; // Change it to band p
          ++b[p];
          ++chg;
        } else if (b[a[q]] > n / m) { // If current song's band has more than needed
          --b[a[q]]; // Reduce its count
          a[q] = p; // Change this song to band p
          ++b[p];
          ++chg;
        }
      }
    }
  }
  printf("%ld %ld\n", min, chg); // Output the result
  for (int p = 0; p < n; p++) {
    printf("%ld ", a[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/