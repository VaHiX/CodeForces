// Problem: CF 1918 E - ace5 and Task Order
// https://codeforces.com/contest/1918/problem/E

/*
Code Purpose:
This code solves an interactive problem where the goal is to reconstruct a hidden permutation of integers from 1 to n using a series of queries. 
Each query compares a selected element of the permutation with a dynamically changing value 'x', updating 'x' based on the result.
The algorithm uses a randomized approach to partition elements into three groups (less than x, equal to x, greater than x) and recursively processes each group,
effectively performing a form of randomized quicksort to determine the permutation order.

Algorithms/Techniques:
- Interactive binary search with dynamic value 'x'
- Randomized partitioning (similar to quicksort)
- Divide and conquer approach to reconstruct the permutation

Time Complexity:
O(n log n) average case due to the randomized partitioning, which is similar to quicksort's average performance.
In the worst case, it could be O(n^2), but due to randomization, it's highly unlikely.

Space Complexity:
O(n) for storing the permutation and auxiliary data structures.
*/

#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

using namespace std;
typedef long long LL;
mt19937 rng{random_device{}()}; // Random number generator
int n, dnow;
vector<pair<int, int>> rd; // Stores the pairs of (x_value, index) for reconstruction

// Query function to interact with the judge
int query(int x) {
  cout << "?" << " " << x << endl;
  char ch;
  cin >> ch;
  if (ch == '=') {
    // If equal, store the index and current x value
    return rd.emplace_back(dnow, x), 0;
  } else if (ch == '<') {
    // If less than x, decrease x and return -1
    dnow -= 1;
    return -1;
  } else {
    // If greater than x, increase x and return 1
    dnow += 1;
    return 1;
  }
}

// Recursive function to sort the indices based on the comparisons
void solve(vector<int> p) {
  if (p.empty())
    return;
  // Shuffle the current partition to randomize the pivot
  shuffle(p.begin(), p.end(), rng);
  // Bucket to hold elements relative to x
  vector<int> buc[3];
  for (int x : p) {
    // Query element at index x and bucket accordingly
    buc[query(x) + 1].push_back(x);
  }
  // Randomly swap buckets to improve performance
  if (rng() & 1)
    swap(buc[0], buc[2]);
  // Recursively process buckets
  solve(buc[0]);
  solve(buc[2]);
}

// Main function for a single test case
int mian() {
  cin >> n;
  rd.clear(); // Clear the result vector
  dnow = 0; // Initialize x to 0
  vector<int> p(n);
  // Fill the initial indices
  for (int i = 1; i <= n; i++)
    p[i - 1] = i;
  solve(p); // Start the partitioning process
  sort(rd.begin(), rd.end()); // Sort the stored pairs
  int cnt = 0;
  // Assign final positions based on the stored indices and x values
  for (auto e : rd)
    p[e.second - 1] = ++cnt;
  cout << "!"; // Output the result
  for (auto x : p)
    cout << " " << x;
  cout << endl;
  return 0;
}

int main() {
  int t;
  cin >> t;
  while (t--)
    mian();
  return 0;
}


// https://github.com/VaHiX/CodeForces/