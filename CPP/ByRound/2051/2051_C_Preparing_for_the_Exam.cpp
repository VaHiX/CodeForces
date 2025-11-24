// Problem: CF 2051 C - Preparing for the Exam
// https://codeforces.com/contest/2051/problem/C

/*
C. Preparing for the Exam

Purpose:
This program determines whether Monocarp can pass an exam based on m different question lists,
each missing one specific question (denoted by 'a[i]'), and given k known questions.

Algorithm:
- For each test case:
  1. Input n (total questions), m (number of lists), k (known questions count).
  2. Read m values representing the missing question index in each list.
  3. Read k values representing known question indices.
  4. Mark all known questions in a boolean array `d`.
  5. Find the smallest missing question (the first one not in `d`), if any.
  6. For each of the m lists, compute whether the student passes:
     - A list passes if the missing question is either not present in the known set
       or matches the found missing question.

Time Complexity: O(n + m + k) per test case, due to linear scanning and vector operations.
Space Complexity: O(n) for storing known questions and the boolean array `d`.

*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k;
    scanf("%ld %ld %ld", &n, &m, &k);
    std::vector<long> a(m); // stores the missing question index for each list
    for (long p = 0; p < m; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<bool> d(n + 1, 1); // marks known questions; initially all are marked as known
    for (long p = 0; p < k; p++) {
      long x;
      scanf("%ld", &x);
      d[x] = 0; // mark the question as NOT known
    }
    long miss(0); // find the smallest unknown question
    for (long p = 1; !miss && p <= n; p++) {
      if (d[p]) {
        miss = p;
      }
    }
    // for each list, output '1' if the student passes, else '0'
    for (long p = 0; p < m; p++) {
      printf("%c", (k + 1 >= n && (!miss || miss == a[p])) ? '1' : '0');
    }
    printf("\n");
  }
}


// https://github.com/VaHiX/codeForces/