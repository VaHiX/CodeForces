// Problem: CF 1849 E - Max to the Right of Min
// https://codeforces.com/contest/1849/problem/E

/*
 * Problem: E. Max to the Right of Min
 * Algorithm: Use monotonic stacks to determine ranges where each element is max or min
 *            and use two functions solve1 and solve2 to count valid subarrays efficiently.
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * The key idea is to:
 * 1. Precompute for each element the nearest smaller (minl, minr) and larger (maxl, maxr) elements on left and right.
 * 2. For each element, determine the range where it is the maximum.
 * 3. Use two helper functions to calculate valid subarrays where maxpos > minpos.
 */

using LL = long long;
#define min(x, y) ((x) > (y) ? (y) : (x))
#define max(x, y) ((x) > (y) ? (x) : (y))
const int kMaxN = 1e6 + 5;
int n, a[kMaxN], maxl[kMaxN], minl[kMaxN], maxr[kMaxN], minr[kMaxN];
LL ret, q[kMaxN], top;

// Function to count valid subarrays where current element is min and max is to its left
void solve1(int l, int r, int x) {
  for (int i = x - 1, mini = 1e9, y; i >= l; i--) {
    if (a[i] < mini)
      mini = a[i], y = minr[i];
    ret += 1ll * min(y - x - 1, r - x);
  }
}

// Function to count valid subarrays where current element is min and max is to its right
void solve2(int l, int r, int x) {
  for (int i = x + 1, mini = 1e9, y; i <= r; i++) {
    if (a[i] < mini)
      mini = a[i], y = minl[i];
    ret += 1ll * max(y - l + 1, 0);
  }
}

int main() {
  __builtin_scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    __builtin_scanf("%d", &a[i]);

  // Compute minl array: nearest smaller element to the left
  q[0] = top = 0;
  for (int i = 1; i <= n; i++) {
    for (; top && a[i] < a[q[top]]; top--)
      ;
    minl[i] = q[top];
    q[++top] = i;
  }

  // Compute maxl array: nearest larger element to the left
  q[0] = top = 0;
  for (int i = 1; i <= n; i++) {
    for (; top && a[i] > a[q[top]]; top--)
      ;
    maxl[i] = q[top];
    q[++top] = i;
  }

  // Compute minr array: nearest smaller element to the right
  q[0] = n + 1, top = 0;
  for (int i = n; i >= 1; i--) {
    for (; top && a[i] < a[q[top]]; top--)
      ;
    minr[i] = q[top];
    q[++top] = i;
  }

  // Compute maxr array: nearest larger element to the right
  q[0] = n + 1, top = 0;
  for (int i = n; i >= 1; i--) {
    for (; top && a[i] > a[q[top]]; top--)
      ;
    maxr[i] = q[top];
    q[++top] = i;
  }

  // For each element, calculate contribution to result using solve1 or solve2
  for (int i = 1, l, r; i <= n; i++) {
    l = maxl[i] + 1, r = maxr[i] - 1;
    if (i - l + 1 <= r - i + 1)
      solve1(l, r, i);
    else
      solve2(l, r, i);
    ret += (i - l);
  }

  __builtin_printf("%lld", ret);
  return 0;
}


// https://github.com/VaHiX/CodeForces/