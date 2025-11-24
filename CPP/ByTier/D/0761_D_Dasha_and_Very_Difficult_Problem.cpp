// Problem: CF 761 D - Dasha and Very Difficult Problem
// https://codeforces.com/contest/761/problem/D

/*
Purpose: 
This code solves the problem of reconstructing a sequence `b` such that the compressed sequence of `c = b - a` matches a given sequence `p`. 
The approach uses sorting and greedy assignment to ensure all values in `b` stay within the specified range [l, r] and the compressed sequence of `c` matches `p`.

Algorithms/Techniques:
- Sorting objects by rank (from compressed sequence)
- Greedy assignment of values to satisfy constraints
- Compressed sequence logic: rank of an element indicates its position in sorted order of unique elements

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing vectors and objects
*/

#include <algorithm>
#include <cstdio>
#include <vector>

struct obj {
  long initialPos, rank, lower, upper;
};

// Compare function to sort by rank
bool objCompare(obj a, obj b) { return a.rank < b.rank; }

int main() {
  long n, l, r;
  scanf("%ld %ld %ld", &n, &l, &r);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<obj> c(n);
  for (long p = 0; p < n; p++) {
    long u;
    scanf("%ld", &u);
    c[p].initialPos = p;      // Store original index
    c[p].rank = u - 1;        // Convert to 0-based rank
    c[p].lower = l - a[p];    // Lower bound for c[i] = b[i] - a[i]
    c[p].upper = r - a[p];    // Upper bound for c[i] = b[i] - a[i]
  }
  
  // Sort objects by rank to process elements in order of increasing rank
  sort(c.begin(), c.end(), objCompare);
  
  long last(-2e9);  // Initialize with a value smaller than any possible c[i]
  bool possible(true);
  std::vector<long> actual(n);  // To store resulting values of c[i]
  
  // Assign values to c[i] greedily based on available bounds
  for (long p = 0; p < n; p++) {
    long w = c[p].initialPos;  // Original position in result array
    
    // If last assigned value is less than lower bound, assign lower bound
    if (last < c[p].lower) {
      actual[w] = c[p].lower;
    } 
    // Otherwise, if there's room to assign a value just above last, do it
    else if (last < c[p].upper) {
      actual[w] = last + 1;
    } 
    // If neither is possible, it's impossible to construct valid sequence
    else {
      possible = false;
      break;
    }
    
    last = actual[w];  // Update last assigned value
  }
  
  // If impossible to construct valid sequence, print -1
  if (!possible) {
    puts("-1");
    return 0;
  }
  
  // Reconstruct the b sequence using c = b - a => b = c + a
  std::vector<long> b(n);
  for (long p = 0; p < n; p++) {
    b[p] = actual[p] + a[p];
  }
  
  // Output the reconstructed sequence b
  for (long p = 0; p < n; p++) {
    printf("%ld ", b[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/