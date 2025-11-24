// Problem: CF 1779 D - Boris and His Amazing Haircut
// https://codeforces.com/contest/1779/problem/D

/*
Algorithm: 
- The problem is to determine whether a sequence of haircuts using razors can transform array `a` into array `b`.
- Key idea: Process from left to right, maintaining a stack of required heights that need to be cut.
- For each position, if `a[i] > b[i]`, a cut operation is needed.
- Use a greedy approach: when a required height is pushed to stack, ensure there's a razor of that size or larger.
- Sort razors by size to efficiently find available razors with binary search.
- Time Complexity: O(n log n + m log m)
- Space Complexity: O(n + m)

Techniques:
- Sorting razors
- Binary search using upper_bound
- Stack for maintaining required heights
*/

#include <stdio.h>
#include <algorithm>
#include <functional>
#include <stack>
#include <utility>

#define F first
#define S second
using namespace std;
typedef pair<int, int> pii;
const int MAX_N = 200005;
int a[MAX_N], b[MAX_N];
pii cut[MAX_N], *itr;
bool flag;
int T, i, j, n, m, now, in;
stack<int> st;

void debug() {
  for (int k = 0; k < m; ++k) {
    printf("%d-%d ", cut[k].F, cut[k].S);
  }
  printf("\n");
}

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
      scanf("%d", a + i);
    for (i = 0; i < n; ++i)
      scanf("%d", b + i);
    scanf("%d", &m);
    for (i = 0; i < m; ++i) {
      scanf("%d", &j);
      cut[i] = {j, 0}; // Store razor size and usage flag
    }
    flag = 0;
    // Early check: if any element in a is less than b, impossible
    for (i = 0; i < n; ++i) {
      if (a[i] < b[i]) {
        printf("NO\n");
        flag = 1;
        break;
      }
    }
    if (flag)
      continue;
    
    // Sort razors by size
    sort(cut, cut + m, less<pii>());
    
    // Clear stack
    while (!st.empty())
      st.pop();
    
    // Process each position from left to right
    for (i = 0; i < n; ++i) {
      now = b[i]; // Desired height at position i
      // While the stack top is less than desired height, pop and check if we can perform the cut
      while (!st.empty() && now > st.top()) {
        in = st.top();
        st.pop();
        // Find a razor of size 'in' that hasn't been used yet
        itr = upper_bound(cut, cut + m, make_pair(in, 0));
        if (itr == cut || (itr - 1)->F != in) {
          printf("NO\n");
          flag = 1;
          break;
        }
        (itr - 1)->S = 1; // Mark razor as used
      }
      if (flag)
        break;
      // If stack is empty or top element is not now, and original a[i] != now, push now to stack
      if ((st.empty() || st.top() != now) && a[i] != now)
        st.push(now);
    }
    if (flag)
      continue;
    
    // Handle remaining elements in stack at end of processing
    while (!st.empty()) {
      in = st.top();
      st.pop();
      itr = upper_bound(cut, cut + m, make_pair(in, 0));
      if (itr == cut || (itr - 1)->F != in) {
        printf("NO\n");
        flag = 1;
        break;
      }
      (itr - 1)->S = 1;
    }
    
    if (!flag)
      printf("YES\n");
  }
}


// https://github.com/VaHiX/CodeForces/