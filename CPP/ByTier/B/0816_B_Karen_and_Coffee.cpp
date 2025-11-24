// Problem: CF 816 B - Karen and Coffee
// https://codeforces.com/contest/816/problem/B

/*
Algorithm/Technique: Coordinate Compression + Square Root Decomposition + Two Pointers

This problem involves preprocessing ranges and answering queries about how many integers in a given range are "admissible" — meaning they are recommended by at least k out of n recipes.

Approach:
1. Use a difference array technique to calculate how many recipes recommend each temperature.
2. Preprocess all queries using square root decomposition to optimize query processing.
3. Use two pointers to efficiently adjust the range for each query.

Time Complexity: O(n + q*sqrt(q) + q*log(q)) where:
- O(n) for building the frequency array from ranges.
- O(q*sqrt(q)) for processing each query with two pointers.
- O(q*log(q)) for sorting the queries and results.

Space Complexity: O(S + q) where S = 200001 is the maximum temperature, and q is the number of queries.
*/

#include <string.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in\n");
#define NL printf("\n");
#define S 200001
#define inf 1000000000000
using namespace std;
ll block;

struct query {
  ll a, b, i;
  query() {}
  query(ll x, ll y, ll j) {
    a = x;
    b = y;
    i = j;
  }
};

// Comparator for sorting queries using block-based sorting (SQRT decomposition)
bool cmp(query a, query b) {
  if (a.a / block != b.a / block)
    return a.a < b.a;
  return a.b < b.b;
}

int main() {
  ll i, j, k;
  ll n, l, r;
  ll q;
  ll a[S];
  memset(a, 0, sizeof(a));
  cin >> n >> k >> q;
  
  // Build difference array: increment at l, decrement at r+1
  for (i = 0; i < n; i++)
    cin >> l >> r, a[l]++, a[r + 1]--;
  
  // Convert difference array into prefix sum to get actual recipe count per temperature
  for (i = 1; i < S; i++)
    a[i] += a[i - 1];
  
  struct query x[q];
  for (i = 0; i < q; i++) {
    cin >> l >> r;
    x[i] = query(l, r, i);
  }
  
  block = sqrt(q);
  sort(x, x + q, cmp);
  
  // Initialize first query result
  ll sum = 0;
  for (i = x[0].a; i <= x[0].b; i++) {
    if (k <= a[i])
      sum++;
  }
  
  pp ff[q];
  ff[0].first = x[0].i;
  ff[0].second = sum;
  
  ll lq = x[0].a;  // left pointer for current query range
  ll rq = x[0].b;  // right pointer for current query range
  
  for (i = 1; i < q; i++) {
    // Adjust left boundary
    if (x[i].a > lq) {
      while (lq < x[i].a) {
        if (a[lq] >= k)
          sum--;
        lq++;
      }
    } else if (x[i].a < lq) {
      lq--;
      while (x[i].a <= lq) {
        if (a[lq] >= k)
          sum++;
        lq--;
      }
    }
    
    // Adjust right boundary
    if (x[i].b > rq) {
      rq++;
      while (rq <= x[i].b) {
        if (a[rq] >= k)
          sum++;
        rq++;
      }
    } else if (x[i].b < rq) {
      while (x[i].b < rq) {
        if (a[rq] >= k)
          sum--;
        rq--;
      }
    }
    
    ff[i] = {x[i].i, sum};
    lq = x[i].a;
    rq = x[i].b;
  }
  
  // Sort answers back to original query order
  sort(ff, ff + q);
  
  for (i = 0; i < q; i++)
    cout << ff[i].second << endl;
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/