// Problem: CF 1073 B - Vasya and Books
// https://codeforces.com/contest/1073/problem/B

/*
B. Vasya and Books
Algorithms/Techniques: Simulation with set tracking and reverse iteration
Time Complexity: O(n)
Space Complexity: O(n)

Vasya has got n books, numbered from 1 to n, arranged in a stack.
The topmost book has number a_1, the next one — a_2, and so on.
The book at the bottom of the stack has number a_n.

During i-th step he wants to move the book number b_i into his backpack.
If the book with number b_i is in the stack, he takes this book and all the books above the book b_i,
and puts them into the backpack; otherwise he does nothing.

Input:
- n: number of books
- a[]: initial stack of books (top to bottom)
- b[]: order of books to be moved

Output:
- For each step, print number of books moved
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 200138
#define inf 1e18
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;
bool ase[N]; // Tracks which books are currently in the stack
int idx[N];  // Index of each book in original stack
int main() {
  int i, j, k;
  int n, m;
  int cnt;
  sf(n);
  vector<int> a, b;
  memset(ase, 0, sizeof(ase));
  a.resize(n), b.resize(n);
  for (i = 0; i < n; i++)
    sf(a[i]), ase[a[i]] = true, idx[a[i]] = i; // Mark book presence and store index
  for (i = 0; i < n; i++)
    sf(b[i]);
  for (i = 0; i < n; i++) {
    if (!ase[b[i]]) // If book is not in stack
      pfs("0 ");
    else {
      k = idx[b[i]]; // Get index of the book in original stack
      cnt = 0;
      while (k >= 0) { // Move books from current position to top
        cnt++; // Count books moved
        ase[a[k]] = false; // Mark that book is no longer in stack
        k--;
        if (k >= 0 && !ase[a[k]]) // Stop if next book not in stack
          break;
      }
      pf(cnt); // Print number of books moved
      pfs(" ");
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/