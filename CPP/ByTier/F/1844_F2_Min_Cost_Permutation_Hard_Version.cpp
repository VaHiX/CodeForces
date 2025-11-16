// Problem: CF 1844 F2 - Min Cost Permutation (Hard Version)
// https://codeforces.com/contest/1844/problem/F2

/*
Purpose: This code finds the lexicographically smallest permutation of an array such that the sum of absolute differences (with a constant c) between consecutive elements in the permutation is minimized.

Algorithm:
- For a given array a and constant c:
  - If c >= 0, the optimal arrangement is simply sorting the array (since differences are minimized when elements are ordered).
  - If c < 0, a more complex greedy strategy is employed involving multiset manipulation to determine the arrangement.
  - The approach uses a greedy method with multiset to select next element that minimizes contribution to the cost function.

Time Complexity: O(n log n) due to sorting and multiset operations.
Space Complexity: O(n) for storing temporary arrays and multiset usage.
*/

#include <stdio.h>
#include <algorithm>
#include <set>
#include <vector>
#include <iterator>

using namespace std;
int c;

// Function to construct a sequence based on a greedy strategy
void finds(vector<int> &a) {
  int n = a.size();
  printf("%d ", a[0]);
  if (n == 1) {
    return;
  }
  multiset<int> s;
  int i;
  for (i = 1; i < n; i++) {
    s.insert(a[i]);
  }
  int now = a[0];
  for (; s.size() != 1;) {
    for (; s.size() != 1;) {
      multiset<int>::iterator ii = s.lower_bound(now - c);
      if (ii == s.begin()) {
        ii++;
      }
      if ((next(ii) == s.end()) || (*next(ii) - *prev(ii) <= c)) {
        now = (*ii);
        s.erase(ii);
        printf("%d ", now);
      } else {
        now = (*ii) + 1;
        break;
      }
    }
    multiset<int>::iterator ii;
    ii = s.lower_bound(now);
    for (; s.size() != 1;) {
      if (next(ii) == s.end()) {
        now = (*ii);
        s.erase(ii);
        printf("%d ", now);
        break;
      } else if (*next(ii) - *prev(ii) <= c) {
        now = (*ii);
        s.erase(ii);
        printf("%d ", now);
        ii = s.lower_bound(now);
      } else {
        ii++;
        now = (*ii);
      }
    }
  }
  printf("%d ", a[n - 1]);
}

// Function to process the main logic for finding answer
void find_ans(vector<int> &a) {
  int n = a.size();
  int i;
  vector<int> b;
  for (i = n - 1; i > 0; i--) {
    b.push_back(a[i]);
    if (a[i] - a[i - 1] > c) {
      finds(b);
      b.clear();
    }
  }
  b.push_back(a[0]);
  finds(b);
}

int a[200005];

int main() {
#ifdef absi2011
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int t;
  scanf("%d", &t);
  int zu;
  for (zu = 0; zu < t; zu++) {
    int n;
    scanf("%d%d", &n, &c);
    int i;
    for (i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    sort(a, a + n);
    if (c >= 0) {
      for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
      }
      printf("\n");
    } else {
      c = -c;
      vector<int> v;
      for (i = 0; i < n; i++) {
        v.push_back(a[i]);
      }
      find_ans(v);
      printf("\n");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/