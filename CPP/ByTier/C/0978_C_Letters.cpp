// Problem: CF 978 C - Letters
// https://codeforces.com/contest/978/problem/C

/*
Algorithm: Binary Search (lower_bound)
Purpose: Given a list of dormitories with their room counts, and a list of room numbers 
         across all dormitories, determine for each room number which dormitory and 
         which room within that dormitory it corresponds to.

Time Complexity: O(n + m * log(n))
Space Complexity: O(n)

The algorithm uses prefix sums to map room numbers to dormitories efficiently.
For each query room number, binary search (lower_bound) is used to find the 
dormitory it belongs to. Then, the room number within that dormitory is computed 
using the prefix sum difference.
*/

#include <algorithm>
#include <cstdio>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 200100
#define pp pair<ll, ll>
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d ", n)
#define pfl(n) printf("%I64d ", n)
#define pfs(s) printf("%s", s)
#define pb push_back
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  ll x, y;
  sff(n, m);
  ll a[n], b[m];
  vector<ll> v; // Vector to store prefix sums of room counts
  
  // Read the number of rooms in each dormitory
  for (i = 0; i < n; i++)
    sfl(a[i]);
    
  // Read the room numbers to process
  for (i = 0; i < m; i++)
    sfl(b[i]);
    
  // Build prefix sum array
  v.push_back(a[0]);
  for (i = 1; i < n; i++)
    v.push_back(v[i - 1] + a[i]);
    
  // Process each room number
  vector<ll>::iterator itr;
  for (i = 0; i < m; i++) {
    // Find the first dormitory whose prefix sum is >= current room number
    itr = lower_bound(v.begin(), v.end(), b[i]);
    
    // Get the index of that dormitory (0-based)
    x = itr - v.begin();
    
    // Print dormitory number (1-based)
    printf("%I64d ", x + 1);
    
    // Print room number within the dormitory
    if (x == 0)
      printf("%I64d\n", b[i]);
    else {
      // Subtract prefix sum of previous dormitories to get room number within current dormitory
      printf("%I64d\n", b[i] - v[x - 1]);
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/