// Problem: CF 978 G - Petya's Exams
// https://codeforces.com/contest/978/problem/G

/*
Algorithm/Techniques: Greedy approach with sorting
Time Complexity: O(m * n) where m is the number of exams and n is the number of days
Space Complexity: O(n + m) for storing the schedule and exam details

This solution uses a greedy strategy to assign days for preparing and taking exams.
Exams are sorted by their exam date (d_i) to process them in chronological order.
For each day, we check if it's an exam day or a preparation day:
- If it's an exam day, we mark it and ensure the student has finished all required preparation.
- If it's a preparation day, we assign it to the earliest available exam that needs preparation.

The key idea is to assign preparation days greedily to ensure all exams are completed on time.
*/

#include <algorithm>
#include <cstdio>
#include <vector>

struct xm {
  long s, d, c, r;
};
bool xmCompare(xm a, xm b) { return a.d < b.d; }
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<xm> v(m);
  for (long p = 0; p < m; p++) {
    scanf("%ld %ld %ld", &v[p].s, &v[p].d, &v[p].c);
    v[p].r = p + 1;
  }
  sort(v.begin(), v.end(), xmCompare);
  std::vector<long> res(n + 1, 0);
  std::vector<long> taken;
  bool possible(true);
  for (long p = 1; p <= n; p++) {
    if (!possible) {
      break;
    }
    for (long u = 0; u < m; u++) {
      if (p == v[u].d) {
        if (v[u].c > 0) {
          possible = false;
        } else {
          res[p] = m + 1;
          taken.push_back(v[u].r);
        }
        break;
      } else if ((p >= v[u].s) && (v[u].c > 0)) {
        res[p] = v[u].r;
        --v[u].c;
        break;
      }
    }
  }
  possible &= (taken.size() >= m);
  if (possible) {
    for (long p = 1; p <= n; p++) {
      printf("%ld ", res[p]);
    };
    puts("");
  } else {
    puts("-1");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/