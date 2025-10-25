// Problem: CF 1677 A - Tokitsukaze and Strange Inequality
// https://codeforces.com/contest/1677/problem/A

/*
Problem: A. Tokitsukaze and Strange Inequality
Algorithms/Techniques: Nested loop with prefix counting optimization
Time Complexity: O(n^3) per test case
Space Complexity: O(n) 

Description:
This code counts the number of quadruples [a,b,c,d] such that a<b<c<d and p[a]<p[c] and p[b]>p[d].
The algorithm uses a nested loop approach where for each valid i (from n-1 down to 3), it processes
the elements after i. For each j from i+1 down to 3, it increments the count of elements seen so far.
Then, for all valid j from i-2 down to 1, it calculates how many elements before j are less than p[j+1]
and adds this to a running sum 'now'. If p[j] < p[i], then ans is incremented by now.

The main idea is to maintain a count array where cnt[j] represents how many times value j
has appeared in the sequence from i+1 onwards.
*/

#include <stdio.h>

typedef long long ll;
int n, p[5005], cnt[5005];
ll ans;

void MAIN() {
  ans = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", p + i), cnt[i] = 0; // Initialize permutation and count array
  
  for (int i = n - 1; i >= 3; i--) {
    // For each element after i, increment its count
    for (int j = p[i + 1]; j <= n; j++)
      cnt[j]++;
    
    ll now = 0;
    // Process elements from i-2 down to 1
    for (int j = i - 2; j; j--) {
      // Add count of elements less than p[j+1] to 'now'
      now += cnt[p[j + 1] - 1];
      // If p[j] < p[i], this contributes to the answer
      if (p[j] < p[i])
        ans += now;
    }
  }
  printf("%lld\n", ans);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    MAIN();
  return 0;
}


// https://github.com/VaHiX/codeForces/