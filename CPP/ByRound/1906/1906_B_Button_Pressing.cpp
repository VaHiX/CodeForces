// Problem: CF 1906 B - Button Pressing
// https://codeforces.com/contest/1906/problem/B

/*
Code Purpose:
This code solves the problem of determining whether it's possible to reach a desired configuration of lamps by pressing buttons. Each button toggles the state of its adjacent lamps but not itself. The solution uses a reduction technique to map the positions of initially and finally on lamps into a simplified form that can be compared.

Algorithms/Techniques:
- Greedy approach with reduction
- Segment grouping and distance calculation based on lamp positions
- Efficient processing using vector and reverse operations

Time Complexity: O(N) amortized over all test cases
Space Complexity: O(N) for storing lamp positions and vectors

*/
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

#pragma GCC optimize(3)
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
int t, n;
char a[MAXN], b[MAXN];

// Function to reduce a vector of lamp positions into a single value representing the "distance" 
// from the closest end (1 or N) after grouping adjacent elements
int reduce(vector<int> &v) {
  if (!v.size())
    return 0;
  reverse(v.begin(), v.end());
  while (v.size() > 1) {
    int x = v.back();
    v.pop_back();
    int y = v.back();
    v.pop_back();
    if (y == x + 1) {
      v.push_back(1);  // If consecutive, group as 1 unit
      continue;
    } else {
      v.push_back(y - x);  // Otherwise store the gap
      continue;
    }
  }
  int x = v[0];
  return min(x, n + 1 - x);  // Return minimum distance from either end
}

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    vector<int> v1, v2;
    scanf("%s", a + 1);
    scanf("%s", b + 1);
    
    // Collect positions of all initially on lamps
    for (int i = 1; i <= n; i++)
      if (a[i] == '1')
        v1.push_back(i);
    
    // Collect positions of all desired on lamps
    for (int i = 1; i <= n; i++)
      if (b[i] == '1')
        v2.push_back(i);
        
    // Compare reduced values of both sets
    if (reduce(v1) == reduce(v2))
      puts("YES");
    else
      puts("NO");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/