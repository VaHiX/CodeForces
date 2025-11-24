// Problem: CF 509 B - Painting Pebbles
// https://codeforces.com/contest/509/problem/B

/*
Code Purpose:
This program solves the pebble painting problem where pebbles from multiple piles must be painted with k colors such that the difference in count of any color between any two piles is at most 1.

Algorithm:
- First, determine the minimum and maximum pile sizes.
- Check if the difference between max and min pile sizes exceeds k. If so, it's impossible to color the pebbles, and we output "NO".
- Otherwise, for each pile:
  - For pebbles in the first m pebbles (where m is the size of the smallest pile), assign color 1.
  - For the rest of the pebbles in the pile, assign colors in a cyclic pattern starting from 2 up to k, wrapping around if needed.

Time Complexity: O(n * max(a_i)) where n is the number of piles and max(a_i) is the maximum number of pebbles in a pile.
Space Complexity: O(n) for storing the pile sizes.

Techniques:
- Greedy assignment of colors based on the difference between pile sizes.
- Cyclic color assignment modulo k.
*/
#include <cstdio>
#include <vector>
int main() {
  int n, k;
  scanf("%d %d\n", &n, &k);
  std::vector<int> a(n);
  int m(101), M(0);
  for (int p = 0; p < a.size(); p++) {
    scanf("%d", &a[p]);
    if (a[p] < m) {
      m = a[p];
    }
    if (a[p] > M) {
      M = a[p];
    }
  }
  if (M - m > k) {
    puts("NO");
  } else {
    puts("YES");
    for (int p = 0; p < n; p++) {
      for (int q = 1; q <= a[p]; q++) {
        if (q <= m) {
          printf("1 ");
        } else {
          printf("%d ", q - m);
        }
      }
      puts("");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/