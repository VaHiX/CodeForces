// Problem: CF 864 A - Fair Game
// https://codeforces.com/contest/864/problem/A

/*
 * Problem: Fair Game
 * 
 * Purpose: Determine if two players can select two distinct numbers from a set of cards such that each player takes exactly half the cards.
 * 
 * Algorithm:
 * 1. Count frequency of each number on the cards.
 * 2. Check if exactly two distinct numbers exist.
 * 3. Check if both numbers appear exactly the same number of times (so that each player gets half the total cards).
 * 
 * Time Complexity: O(n log n) due to map operations (insertion and iteration)
 * Space Complexity: O(n) for storing the frequencies in the map
 * 
 * Techniques:
 * - Using std::map to count occurrences of numbers
 * - Iterating through map to verify conditions
 */

#include <cstdio>
#include <map>
#include <utility>

int main() {
  long n;
  scanf("%ld", &n);
  std::map<long, long> m;
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    if (m.count(x) <= 0) {
      m[x] = 0;
    }
    ++m[x];
  }
  if (m.size() != 2) {
    puts("NO");
  } else {
    std::pair<long, long> a = *(m.begin());
    std::pair<long, long> b = *(++m.begin());
    if (a.second != b.second) {
      puts("NO");
    } else {
      puts("YES");
      printf("%ld %ld\n", a.first, b.first);
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/