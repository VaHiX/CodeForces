// Problem: CF 1746 E2 - Joking (Hard Version)
// https://codeforces.com/contest/1746/problem/E2

/*
Purpose: Solve an interactive puzzle where a hidden number x between 1 and n must be found with up to 53 queries and 2 guesses.
         The responses to queries can be lies, but at least one of two consecutive responses must be truthful.
         The algorithm uses a binary-search-like strategy with a twist to handle the liar responses.

Algorithms/Techniques:
- Divide and Conquer approach to reduce search space
- Interactive binary search with handling of inconsistent answers (liars)
- Recursive DFS with careful splitting to identify correct answers

Time Complexity: O(log n) for the search, but with a higher constant due to the need to check multiple cases and handle lies.
Space Complexity: O(log n) for recursion depth and storage of subsets during the search.
*/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to extract a substring from vector v starting at index s with size sz
vector<int> sbstr(vector<int> v, int s, int sz) {
  vector<int> ret;
  for (int i = s; i < s + sz; i++)
    ret.push_back(v[i]);
  return ret;
}

// Function to make a guess for the answer x
void findans(int x) {
  cout << "! " << x << '\n';
  fflush(stdout);
  string s;
  cin >> s;
  if (s == ":)")
    exit(0);
}

// Function to ask a question about whether x belongs to set v
bool Q(vector<int> v) {
  cout << "? " << v.size() << ' ';
  for (int i = 0; i < v.size(); i++)
    cout << v[i] << ' ';
  cout << '\n';
  fflush(stdout);
  string s;
  cin >> s;
  if (s == "YES")
    return 1;
  else
    return 0;
}

// Function to merge two vectors
vector<int> merge(vector<int> v, vector<int> g) {
  while (g.size())
    v.push_back(g.back()), g.pop_back();
  return v;
}

// Recursive DFS function to find the answer using divide and conquer
void dfs(vector<int> v, vector<int> g) {
  // Base case: if combined size is less than 3, try all elements as guesses
  if (v.size() + g.size() < 3) {
    while (v.size())
      findans(v.back()), v.pop_back();
    while (g.size())
      findans(g.back()), g.pop_back();
    return;
  }
  
  int i = v.size(), j = g.size(), k, l;
  
  // Split the two vectors based on their parity to maintain balance
  if (i % 2 == 0 && j % 2 == 0)
    k = i / 2, l = j / 2;
  if (i % 2 == 0 && j % 2 == 1)
    k = i / 2 + 1, l = j / 2;
  if (i % 2 == 1 && j % 2 == 0)
    k = i / 2, l = j / 2;
  if (i % 2 == 1 && j % 2 == 1)
    k = i / 2, l = (j + 1) / 2;
  
  // Query the merged subset and proceed accordingly
  if (Q(merge(sbstr(v, 0, k), sbstr(g, 0, l))))
    // If the answer is YES, continue search in the first half of the split
    dfs(merge(sbstr(v, 0, k), sbstr(g, 0, l)), sbstr(v, k, v.size() - k));
  else
    // If the answer is NO, continue search in the second half of the split
    dfs(merge(sbstr(v, k, v.size() - k), sbstr(g, l, g.size() - l)),
        sbstr(v, 0, k));
}

int main() {
  int n;
  cin >> n;
  vector<int> v;
  for (int i = 0; i < n; i++)
    v.push_back(i + 1);
  dfs(v, {});
}


// https://github.com/VaHiX/CodeForces/