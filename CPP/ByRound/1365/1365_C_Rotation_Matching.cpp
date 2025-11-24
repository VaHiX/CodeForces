// Problem: CF 1365 C - Rotation Matching
// https://codeforces.com/contest/1365/problem/C

/* 
C. Rotation Matching
Algorithms/Techniques: Prefix counting, modular arithmetic
Time Complexity: O(n)
Space Complexity: O(n)

The problem asks to find the maximum number of matching pairs between two permutations 
after performing any number of cyclic shifts on either permutation. 

Key insight:
If we align permutation a with permutation b such that a[i] == b[j], then shifting b by k positions
means b[j] becomes b[j-k] (with wraparound). Therefore, for each element value, we can compute the 
difference in indices and use modular arithmetic to count how many times each shift leads to matches.

We precompute the positions of all elements in both permutations.
Then iterate through all possible shifts (differences) modulo n, and count occurrences.
The maximum such count gives us the answer.
*/

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> bpos(n + 1); // position of each element in b
  for (long p = 1; p <= n; p++) {
    long x;
    scanf("%ld", &x);
    bpos[x] = p;
  }
  std::vector<long> apos(n + 1); // position of each element in a
  for (long p = 1; p <= n; p++) {
    long x;
    scanf("%ld", &x);
    apos[x] = p;
  }
  std::vector<long> cnt(n, 0); // count of each shift difference
  long mx(0);
  for (long p = 1; p <= n; p++) {
    long diff = apos[p] - bpos[p]; // difference in positions
    if (diff < 0) {
      diff += n; // handle wraparound using modular arithmetic
    }
    ++cnt[diff]; // count this shift
    mx = (mx > cnt[diff]) ? mx : cnt[diff]; // track maximum matches
  }
  printf("%ld\n", mx);
  return 0;
}


// https://github.com/VaHiX/codeForces/