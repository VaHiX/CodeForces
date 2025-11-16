// Problem: CF 1737 F - Ela and Prime GCD
// https://codeforces.com/contest/1737/problem/F

/*
Algorithm/Technique: 
This code solves a problem where we are given the prime factorization of a number c and need to find a sequence of divisors of c (excluding 1) such that the GCD of adjacent elements is a prime number. The approach uses precomputed patterns for small cases, then extends these patterns to larger inputs using a recursive-like construction.

Time Complexity: O(m * n) where m is the number of prime factors and n is the number of divisors
Space Complexity: O(n^2) due to storing multiple sequences and vectors
*/

#include <stdio.h>
#include <vector>
using namespace std;

int a[1000], n, pos1, pos;

// Function to print the result sequence
void print_ans(vector<vector<int>> &res) {
  for (vector<int> &v : res) {
    for (int elem : v)
      printf("%d ", elem);
    printf("\n");
  }
}

// Function to push all patterns from 'from' into 'to' with specific positions updated
void push_all(vector<vector<int>> &to, vector<vector<int>> from) {
  vector<int> first;
  first.resize(n);
  for (vector<int> &v : from) {
    first[pos] = v[0];
    if (v.size() != 1)
      first[pos1] = v[1];
    to.push_back(first);
    first[pos] = 0;
    if (v.size() != 1)
      first[pos1] = 0;
  }
}

void solve() {
  vector<vector<int>> ans;
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  int count = 0;
  pos = pos1 = -1;
  // Count the number of prime factors with exponent > 1
  for (int i = 0; i < n; i++)
    if (a[i] > 1) {
      count += a[i] - 1;
      if (pos == -1)
        pos = i;
      else
        pos1 = i;
    }
  // If count exceeds 2, impossible to form valid sequence
  if (count > 2) {
    printf("-1\n");
    return;
  }
  // Handle special case where count is 0
  if (count == 0) {
    if (n == 1) {
      printf("1\n");
      return;
    }
    pos = 0;
    pos1 = 1;
    push_all(ans, {{1, 0}, {1, 1}, {0, 1}});
  }
  // Handle case where count is 1
  if (count == 1)
    push_all(ans, {{1}, {2}});
  // Handle case where count is 2
  if (count == 2) {
    if (pos1 == -1)
      push_all(ans, {{3}, {1}, {2}});
    else
      push_all(
          ans,
          {{1, 0}, {2, 1}, {0, 2}, {1, 1}, {2, 0}, {1, 2}, {0, 1}, {2, 2}});
  }
  // Extend the pattern recursively for remaining prime factors
  for (int i = 0; i < n; i++)
    if (i != pos1 && i != pos) {
      vector<vector<int>> tmp;
      vector<int> prime;
      int num = ans.size() % 2 == 0 ? ans.size() - 1 : ans.size();
      prime.resize(n);
      prime[i] = 1;
      for (int j = 0; j < num; j++) {
        tmp.push_back(ans[j]);
        if (j % 2 == 1)
          tmp.back()[i] = 1;
      }
      for (int j = num < ans.size() ? num : ans.size() - 2; j >= 0; j--) {
        tmp.push_back(ans[j]);
        if (j % 2 == 0)
          tmp.back()[i] = 1;
      }
      tmp.push_back(prime);
      tmp.push_back(ans.back());
      tmp.back()[i] = 1;
      ans = tmp;
    }
  print_ans(ans);
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++)
    solve();
}


// https://github.com/VaHiX/CodeForces/