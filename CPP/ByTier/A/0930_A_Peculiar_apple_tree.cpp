// Problem: CF 930 A - Peculiar apple-tree
// https://codeforces.com/contest/930/problem/A

/*
Code Purpose:
This program calculates the number of apples that will be collected by Arcady from the first inflorescence 
of a peculiar apple tree. Each inflorescence initially contains one apple, and apples roll down the tree 
based on parent relationships. Apples in the same inflorescence annihilate each other in pairs. 
The solution uses depth and count tracking to determine the final number of apples collected.

Algorithms/Techniques:
- Tree traversal to compute depths of each node
- Counting apples per depth level
- Odd counts contribute to final result (annihilation removes pairs)

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int MAXN = 100100;
int dep[MAXN], num[MAXN];  // dep[i] stores depth of inflorescence i, num[i] counts apples at depth i
int main() {
  int n, i, p, ans = 1;  // ans initialized to 1 because apple from inflorescence 1 is always collected
  scanf("%d", &n);
  for (i = 2; i <= n; i++) {  // process inflorescences from 2 to n
    scanf("%d", &p);
    dep[i] = dep[p] + 1;  // compute depth based on parent's depth
    num[dep[i]]++;  // increment apple count at that depth
  }
  for (i = 0; i <= n; i++)  // iterate through all possible depths
    ans += num[i] % 2;  // add 1 if odd number of apples (since even pairs annihilate)
  printf("%d", ans);
}


// https://github.com/VaHiX/CodeForces/