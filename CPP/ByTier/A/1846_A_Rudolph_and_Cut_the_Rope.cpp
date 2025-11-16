// Problem: CF 1846 A - Rudolph and Cut the Rope 
// https://codeforces.com/contest/1846/problem/A

/*
Code Purpose:
This program determines the minimum number of ropes to cut so that a candy tied to all ropes falls to the ground.
Each rope is attached to a nail at height 'a' with length 'b'. The candy will fall if there exists at least one rope
whose length is less than or equal to the height of the nail it's attached to, meaning the rope doesn't reach the ground.
We count how many such ropes exist — these are the ones that must be cut to allow the candy to fall.

Algorithm:
- For each nail with height 'a' and rope length 'b', check if 'a <= b'.
- If true, the rope does not reach the ground and must be cut.
- Count such ropes and output the count.

Time Complexity: O(n) per test case where n is the number of nails.
Space Complexity: O(1), only using a few variables.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt(0);  // Counter for ropes that must be cut
    for (long p = 0; p < n; p++) {
      long a, b;
      scanf("%ld %ld", &a, &b);
      cnt += (a > b);  // Increment if rope is longer than nail height (i.e., needs to be cut)
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/CodeForces/