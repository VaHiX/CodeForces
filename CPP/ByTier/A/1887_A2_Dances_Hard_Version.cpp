// Problem: CF 1887 A2 - Dances (Hard Version)
// https://codeforces.com/contest/1887/problem/A2

/*
Algorithm: Greedy + Two Pointers + Prefix Sum
Time Complexity: O(n * log(n)) due to sorting
Space Complexity: O(n) for arrays and auxiliary space

Approach:
1. Sort array 'a' (excluding first element) in ascending order.
2. Sort array 'b' in ascending order.
3. Use two pointers to match elements from sorted 'a' to sorted 'b' such that a[i] < b[j].
4. Mark matched elements in 'b' to avoid double counting.
5. For each value from 1 to m, calculate how many valid pairs (c[i], b[j]) exist where c[i] < b[j].
   - This is done by precomputing how many unmatched elements in 'b' are greater than a given value in 'a'.

The key idea is that we want to minimize operations, so we greedily match smallest possible elements from 'a' to smallest possible elements in 'b'.
We then compute how many valid assignments (c[i], b[j]) exist for all possible values of c[i] from 1 to m.
*/
#include <stdio.h>

typedef long long LL;
#include <algorithm>

using namespace std;
bool rcmp(int a, int b) { return a > b; }
class mypcmp {
public:
  bool operator()(const int &a, const int &b) { return a < b; }
};
int as[100004];  // Stores elements of array 'a' except the first one
int bs[100004];  // Stores elements of array 'b'
char mk[100004]; // Marks which elements in 'b' are matched
int cs[100004];  // Not used in current implementation
int main() {
  int n, m, i, j;
  LL r, c, s, e, cc;  // r: result, c: count of unmatched, s: start, e: end, cc: count
  int tc;
  scanf("%d", &tc);
  while (tc--) {
    scanf("%d %d", &n, &m);
    for (i = 0; i < n - 1; i++)
      scanf("%d", &as[i]);
    sort(as, as + n - 1);  // Sort remaining elements in array 'a'
    for (i = 0; i < n; i++)
      scanf("%d", &bs[i]);
    sort(bs, bs + n);  // Sort array 'b'
    for (i = 0; i < n; i++)
      mk[i] = 0;  // Initialize marking array
    
    // Match elements from 'a' to 'b' greedily
    for (i = j = 0; i < n - 1; i++) {
      // Find next element in 'b' that is greater than current element in 'a'
      while (j < n && as[i] >= bs[j])
        j++;
      if (j >= n)
        break;
      mk[j] = 1;  // Mark this element in 'b' as matched
      j++;
    }
    
    c = n - i;  // Number of unmatched elements left in 'a'
    r = 0;      // Initialize result
    s = 1;      // Start value for range iteration
    
    // Process remaining unmatched elements in 'b'
    for (i = 0; i < n && s <= m; i++)
      if (mk[i] == 0) {  // If this element in 'b' is not matched
        e = bs[i] - 1;   // Upper bound of valid c values for this element
        if (e > m)
          e = m;         // Cap upper bound at m
        cc = e - s + 1;  // Count of valid c values
        r += cc * (c - 1); // Add contribution to result
        s = bs[i];       // Update start for next interval
      }
    
    // Handle any remaining range from s up to m
    if (s <= m) {
      cc = m - s + 1;
      r += cc * c; // Add final contribution
    }
    
    printf("%lld\n", r);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/