// Problem: CF 1891 E - Brukhovich and Exams
// https://codeforces.com/contest/1891/problem/E

/*
Algorithm/Technique: Greedy + Sliding Window + GCD
Time Complexity: O(n * log(max(a[i]))), where n is the number of exams and log(max(a[i])) accounts for GCD computation
Space Complexity: O(n), for storing cnt array and input array

The problem involves minimizing the sadness (number of adjacent pairs with GCD = 1) by setting at most k elements to 0.
Approach:
- First, handle special case where all elements are 1 (minimum possible sadness is n - k).
- For other cases, process intervals:
  * If current element is 1, find consecutive 1s and mark potential savings.
  * If not 1, extend until a pair with GCD > 1 is found, calculate cost to fix.
- Use greedy strategy to subtract the highest impact savings from k operations.
*/

#include <stdio.h>
#include <algorithm>

#define FL(i, a, b) for (int i = (a); i <= (b); ++i)
using namespace std;
const int N = 1e5 + 10;
int n, k, ans, flag, a[N], cnt[N];

void solve() {
  scanf("%d%d", &n, &k);
  fill(cnt, cnt + n + 1, 0), ans = 0, flag = 1;
  FL(i, 1, n) scanf("%d", &a[i]), flag &= (a[i] == 1);
  if (flag)
    return printf("%d\n", n - k), (void)0;
  FL(i, 2, n) if (a[i - 1] == 1 || a[i] == 1)++ ans;
  FL(i, 1, n) {
    int j = i;
    if (a[i] == 1) {
      while (j < n && a[j + 1] == 1)
        ++j;
      if (i > 1 && j < n)
        ++cnt[j - i + 1]; // Count consecutive 1s interval saving
    } else {
      while (j < n && a[j + 1] > 1 && __gcd(a[j], a[j + 1]) == 1)
        ++j;
      ans += j - i, cnt[1] += (j - i) / 2; // Accumulate GCD=1 pairs in sequence
    }
    i = j;
  }
  ans -= k;
  FL(i, 1, n) while (k >= i && cnt[i]) k -= i, --cnt[i], --ans; // Greedily apply operations
  printf("%d\n", max(ans, 0));
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/