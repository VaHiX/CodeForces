// Problem: CF 1989 C - Two Movies
// https://codeforces.com/contest/1989/problem/C

/*
C. Two Movies

Purpose:
This code solves the problem of assigning reviews to two movies such that the minimum of their ratings is maximized.
Each person can choose which movie to review, and based on their attitude toward each movie, they contribute +1 (like), 0 (neutral), or -1 (dislike) to that movie's rating.

Algorithms/Techniques:
- Greedy assignment based on sign of attitudes
- Classification of people into four categories depending on their attitudes towards both movies
- Optimization of assignments to balance the ratings

Time Complexity: O(n) per test case, where n is the number of people.
Space Complexity: O(n) for storing the input vectors.

*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<int> v(n); // attitudes toward first movie
    for (long p = 0; p < n; p++) {
      scanf("%d", &v[p]);
    }
    long a(0), b(0), minus(0), plus(0); // counters for different categories
    for (long p = 0; p < n; p++) {
      int x;
      scanf("%d", &x);
      if (v[p] < 0 && x < 0) {
        ++minus; // both dislike
      } else if (v[p] > 0 && x > 0) {
        ++plus; // both like
      } else if (v[p] > 0 && x <= 0) {
        ++a; // first like, second not like
      } else if (v[p] <= 0 && x > 0) {
        ++b; // first not like, second like
      }
    }
    if (a > b) {
      long u = a;
      a = b;
      b = u;
    }
    long diff = (b - a);
    diff = (diff < minus ? diff : minus); // balance the number of people from 'minus' to make b equal to a
    b -= diff;
    minus -= diff;
    diff = (b - a);
    diff = (diff < plus ? diff : plus); // use 'plus' to increase a so that a approaches b
    a += diff;
    plus -= diff;
    if (minus && plus) {
      long mn = (minus < plus ? minus : plus);
      minus -= mn;
      plus -= mn;
    }
    if (minus) {
      a -= (minus + 1) / 2; // reduce 'a' due to remaining negative contributions
    } else if (plus) {
      a += plus / 2; // add positive contributions to 'a'
    }
    printf("%ld\n", a);
  }
}


// https://github.com/VaHiX/codeForces/