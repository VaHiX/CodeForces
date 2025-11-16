// Problem: CF 2146 B - Merging the Sets
// https://codeforces.com/contest/2146/problem/B

/*
B. Merging the Sets
Algorithm: Count how many times each element appears across all sets.
For each set, check if it contains any element that appears exactly once in total.
If at least 2 sets don't contain unique elements (i.e., no element is exclusive to them),
then we can choose at least three different combinations of sets such that all elements are covered.

Time Complexity: O(L) where L = sum of sizes of all sets
Space Complexity: O(m) for the frequency array and auxiliary arrays
*/

#include <algorithm>
#include <iostream>
#include <vector>

#define f(i, n) for (int i = 0; i < n; i++)
#define F(i, a, b) for (int i = a; i < b; i++)
#define vi vector<int>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<vi> v(n); // Store the sets
    vi c(m + 1, 0);  // Count of occurrences of each number from 1 to m
    f(i, n) {
      int l;
      cin >> l;
      v[i].resize(l);
      f(j, l) {
        cin >> v[i][j];
        c[v[i][j]]++; // Increment count for this element
      }
    }

    bool bad = 0;
    F(i, 1, m + 1) if (c[i] == 0) {
      bad = 1;
      break;
    }
    // If any number from 1 to m is missing in all sets, answer is NO
    if (bad) {
      cout << "NO\n";
      continue;
    }

    vi must(n, 0); // Track if set i has an element that appears only once globally
    f(i, n) {
      for (int x : v[i])
        if (c[x] == 1)
          must[i] = 1; // Mark that this set has a unique element
    }

    int free = 0; // Count of sets that do NOT have any unique elements
    f(i, n) if (!must[i]) free++;

    // If we have >= 2 sets without unique elements,
    // then we can choose at least 3 different combinations
    if (free >= 2)
      cout << "YES\n";
    else
      cout << "NO\n";
  }
}


// https://github.com/VaHiX/CodeForces/