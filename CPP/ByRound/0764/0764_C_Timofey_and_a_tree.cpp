// Problem: CF 764 C - Timofey and a tree
// https://codeforces.com/contest/764/problem/C

/*
Algorithm/Technique: Tree traversal, edge color matching, degree counting
Time Complexity: O(n)
Space Complexity: O(n)

The problem is to find a root vertex such that no subtree (except the whole tree) contains vertices of different colors.
We use the following approach:
1. For each edge, check if the two vertices it connects have different colors.
2. For each such edge, increment the degree count for both vertices.
3. The vertex with degree equal to the total count of differing edges is a valid root.
4. If such a vertex exists, output YES and the vertex index; otherwise output NO.
*/

#include <stdio.h>
#include <iostream>

using namespace std;
const int N = 2E5 + 10;
int a[N], b[N], c[N];  // a and b store edges, c stores colors
int mp[N];  // mp[i] counts how many edges incident to vertex i have different-colored endpoints

int main() {
  int n, f = 0, ans = 0, sum = 0;  // f is flag, ans stores the result vertex, sum counts differing edges
  cin >> n;
  
  // Read all edges
  for (int i = 1; i <= n - 1; i++)
    scanf("%d%d", &a[i], &b[i]);
  
  // Read all colors
  for (int i = 1; i <= n; i++)
    scanf("%d", &c[i]);
  
  // For each edge, if endpoints have different colors, increment degree count of both endpoints
  for (int i = 1; i <= n - 1; i++)
    if (c[a[i]] != c[b[i]])
      sum++, mp[a[i]]++, mp[b[i]]++;
  
  // Find vertex whose degree equals total number of differing edges
  for (int i = 1; i <= n; i++)
    if (mp[i] == sum) {
      ans = i;
      f = 1;
      break;
    }
  
  // Output result
  if (f)
    printf("YES\n%d\n", ans);
  else
    puts("NO");
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/