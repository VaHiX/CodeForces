// Problem: CF 1622 F - Quadratic Set
// https://codeforces.com/contest/1622/problem/F

/*
Purpose: This code finds a maximum quadratic subset of the set {1, 2, ..., n}.
A quadratic set is one where the product of factorials of its elements is a perfect square.

Algorithm:
- Uses a probabilistic approach with random hash values to represent prime factors
- For each number i from 2 to n, compute a "signature" based on prime factorization
- Maintain a map of signatures to track which numbers have been seen
- Use XOR operations on these signatures to find subsets with product of factorials being a perfect square

Time Complexity: O(n * sqrt(n)) where n is the input number
Space Complexity: O(n) for storing hash values and signature map
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <set>

using namespace std;
#define N 1000010
typedef unsigned long long ull;
int n;
ull h[N], f[N], o;
map<ull, int> mp;
struct Ans {
  set<int> s;
  void Ins(int x) { s.insert(x); }
  void print(int n) {
    printf("%d\n", n - (int)s.size());
    for (int i = 1; i <= n; i++)
      if (!s.count(i))
        printf("%d ", i);
  }
} ans;
ull Rand() {
  ull r = 0;
  for (int i = 0; i < 64; i++)
    r = r * 2 + rand() % 2;
  return r;
}
int main() {
  srand(time(0));
  for (int i = 1; i < N; i++)
    h[i] = Rand(); // Generate random hash values for each number
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    int x = i;
    f[i] = f[i - 1]; // Start with previous signature
    for (int j = 2; j * j <= x; j++) // Factorize x
      while (x % j == 0)
        f[i] ^= h[j], x /= j; // XOR the hash of prime factor j into signature
    if (x > 1)
      f[i] ^= h[x]; // If x is still > 1, it's a prime factor
    o ^= f[i]; // Accumulate XOR of all signatures
    mp[f[i]] = i; // Store mapping from signature to number
  }
  if (o == 0) // Special case: entire set is already quadratic
    return ans.print(n), 0;
  if (mp.count(o)) { // If we can find a number with signature equal to accumulated XOR
    ans.Ins(mp[o]); // Include it in answer
    ans.print(n);
    return 0;
  }
  for (int i = 2; i <= n; i++) // Look for a pair that makes XOR equal to zero
    if (mp.count(o ^ f[i])) { // Check if there exists a previous number with signature such that XOR equals o
      ans.Ins(i); // Include both numbers
      ans.Ins(mp[o ^ f[i]]);
      ans.print(n);
      return 0;
    }
  ans.Ins(n); // Fallback: include these numbers
  ans.Ins(2);
  ans.Ins(n / 2);
  ans.print(n);
}


// https://github.com/VaHiX/CodeForces/