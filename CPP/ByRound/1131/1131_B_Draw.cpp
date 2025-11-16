// Problem: CF 1131 B - Draw!
// https://codeforces.com/contest/1131/problem/B

/*
B. Draw!
Algorithm: Greedy approach to maximize the number of draws.
Time Complexity: O(n), where n is the number of score entries.
Space Complexity: O(1), as we use only a constant amount of extra space.

The problem asks us to find the maximum number of times the score was a draw (equal scores) during a football match,
given partial information about the score at certain moments. We simulate the process greedily to maximize
the number of draws by extending previous scores in such a way that we increase the count whenever possible.

We start with initial score 0:0 and then for each pair of scores, we determine how many additional draw moments
can occur between the current and next score, based on how much we can increment either side without violating
the order of scores.
*/

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long cnt(1), a(0), b(0); // cnt starts at 1 to include initial 0:0 draw
  while (n--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    long mx = (a > b) ? a : b; // maximum of previous scores
    long mn = (x < y) ? x : y; // minimum of current scores
    long diff = (mn > mx) ? (mn - mx) : 0; // how much we can extend to get more draws
    cnt += diff + (mn >= mx) * (a != b); // increment count for extra draws and if prev was not equal
    a = x;
    b = y;
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/