// Problem: CF 2039 H2 - Cool Swap Walk (Hard Version)
// https://codeforces.com/contest/2039/problem/H2

/*
 * Code Purpose: This solution solves the "Cool Swap Walk" problem for sorting an array
 * using at most n+4 cool swap walks on an n×n grid, where each walk is represented as a path
 * from (1,1) to (n,n). Each time we step to cell (i,j), we swap array elements at positions i and j.
 * 
 * Algorithm/Techniques:
 * - The solution uses a two-step approach:
 *   1. step1() - performs transformations to sort the array, particularly handling small and large values
 *   2. step2() - performs additional swaps for the remaining disorder
 * - Paths are encoded as sequences of 'R' and 'D' commands.
 * 
 * Time Complexity: O(n^2) per test case due to nested loops and path construction.
 * Space Complexity: O(n^2) for storing paths and intermediate arrays.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2010;
int T, n, tot;
int a[N];
vector<int> X[N], Y[N];

// Create a path that moves elements to correct positions
void path1(int num) {
  for (int i = 1; i <= n; i++) {
    X[num].push_back(i), Y[num].push_back(i);
    if (i != n) {
      X[num].push_back(i), Y[num].push_back(i + 1);
      swap(a[i], a[i + 1]);
    }
  }
}

// Move all elements to first row, then down to last column
void path2(int num) {
  for (int i = 1; i <= n; i++) {
    X[num].push_back(1), Y[num].push_back(i);
    swap(a[1], a[i]);
  }
  for (int i = 2; i <= n; i++) {
    X[num].push_back(i), Y[num].push_back(n);
    swap(a[i], a[n]);
  }
}

// Generic path function for sorting based on a given set of positions
void path3(int num, vector<int> p) {
  for (int i = 1; i <= p[0]; i++) {
    X[num].push_back(1), Y[num].push_back(i);
    swap(a[1], a[i]);
  }
  for (int i = 1; i < p.size(); i++) {
    for (int j = p[i - 1]; j <= p[i]; j++) {
      X[num].push_back(i + 1), Y[num].push_back(j);
      swap(a[i + 1], a[j]);
    }
  }
  int x = p.size(), y = p.back();
  while (x != n) {
    x++;
    X[num].push_back(x), Y[num].push_back(y);
    swap(a[x], a[y]);
  }
  while (y != n) {
    y++;
    X[num].push_back(x), Y[num].push_back(y);
    swap(a[x], a[y]);
  }
}

// Special walk pattern 1 for three elements
void walk1(int j) {
  X[tot].push_back(j - 1), Y[tot].push_back(j);
  X[tot].push_back(j - 1), Y[tot].push_back(j + 1);
  X[tot].push_back(j), Y[tot].push_back(j + 1);
  X[tot].push_back(j + 1), Y[tot].push_back(j + 1);
  swap(a[j - 1], a[j + 1]);
}

// Special walk pattern 2 for three elements
void walk2(int j) {
  X[tot].push_back(j - 1), Y[tot].push_back(j);
  X[tot].push_back(j), Y[tot].push_back(j);
  X[tot].push_back(j), Y[tot].push_back(j + 1);
  X[tot].push_back(j + 1), Y[tot].push_back(j + 1);
  swap(a[j - 1], a[j]);
  swap(a[j], a[j + 1]);
}

// Special walk pattern 3 for three elements
void walk3(int j) {
  X[tot].push_back(j - 1), Y[tot].push_back(j);
  X[tot].push_back(j), Y[tot].push_back(j);
  swap(a[j - 1], a[j]);
}

// Initialize the problem and prepare sorted version of array
void init() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  tot = 0;
  for (int i = 1; i <= 3 * n; i++)
    X[i].clear(), Y[i].clear();
  vector<pair<int, int>> pr;
  for (int i = 1; i <= n; i++)
    pr.push_back(make_pair(a[i], i));
  sort(pr.begin(), pr.end());
  for (int i = 1; i <= n; i++)
    a[pr[i - 1].second] = i;
}

// Perform the first set of operations
void step1() {
  int p1, pn;
  vector<int> p;
  for (int i = 1; i <= n; i++)
    if (a[i] == 1)
      p1 = i;
  if (p1 != 1) {
    p.push_back(p1);
    path3(++tot, p);
  }
  if (n == 2)
    return;
  tot++;
  X[tot].push_back(1), Y[tot].push_back(1);
  for (int j = 2; j <= n; j += 2) {
    if (j + 1 > n)
      walk3(j);
    else if (a[j] == n)
      walk1(j);
    else
      walk2(j);
  }
  p1 = n;
  for (int i = 1; i <= n; i++)
    if (a[i] == n)
      pn = i;
  p.clear();
  p.push_back(pn);
  p.push_back(p1);
  path3(++tot, p);
  p.clear();
  for (int i = 1; i <= n; i++)
    if (a[i] <= (n + 1) / 2)
      p.push_back(i);
  path3(++tot, p);
}

// Perform the second set of operations
void step2() {
  int head;
  if (n & 1) {
    for (int t = 1; t <= 2; t++) {
      head = n / 2 + 2;
      for (int i = 1; i <= n / 2 + (t == 1); i++) {
        tot++;
        X[tot].push_back(1), Y[tot].push_back(1);
        for (int j = 2; j <= n; j++) {
          if (!(head <= j && j <= head + n / 2 - 1))
            walk3(j);
          else if (j == head && (head & 1))
            walk3(j);
          else {
            if (!(head <= j + 1 && j + 1 <= head + n / 2 - 1))
              walk3(j);
            else if (a[j] > a[j + 1])
              walk1(j), j++;
            else
              walk2(j), j++;
          }
        }
        head--;
      }
    }
  } else {
    for (int t = 1; t <= 2; t++) {
      head = n / 2 + 1;
      for (int i = 1; i <= n / 2; i++) {
        tot++;
        X[tot].push_back(1), Y[tot].push_back(1);
        for (int j = 2; j <= n; j++) {
          if (!(head <= j && j <= head + n / 2 - 1))
            walk3(j);
          else if (j == head && (head & 1))
            walk3(j);
          else {
            if (!(head <= j + 1 && j + 1 <= head + n / 2 - 1))
              walk3(j);
            else if (a[j] > a[j + 1])
              walk1(j), j++;
            else
              walk2(j), j++;
          }
        }
        head--;
      }
    }
  }
}

// Output all paths
void output() {
  printf("%d\n", tot);
  for (int i = 1; i <= tot; i++) {
    for (int j = 1; j < 2 * n - 1; j++) {
      if (X[i][j] == X[i][j - 1])
        printf("R");
      else
        printf("D");
    }
    printf("\n");
  }
}

int main() {
  scanf("%d", &T);
  while (T--) {
    init();
    step1();
    step2();
    output();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/