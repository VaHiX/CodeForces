// Problem: CF 2130 E3 - Interactive RBS (Hard Version)
// https://codeforces.com/contest/2130/problem/E3

/*
E3. Interactive RBS (Hard Version)
Algorithms/Techniques: Binary search, interactive problem solving, bit manipulation
Time Complexity: O(n * log(n)) - due to binary search over indices and processing segments
Space Complexity: O(n) - for storing the result string and auxiliary arrays

The problem is an interactive task that involves reconstructing a bracket sequence.
We are given a hidden bracket sequence of length n (only '(' and ')') and we use
queries to get information about the number of regular bracket substrings in selected subsets.

Approach:
1. First, determine an index 't' which will be used as a reference point for queries.
   This is done via binary search by checking query results on subranges.
2. Then, decompose the entire sequence into chunks (of size maxAns = 13) and reconstruct
   each chunk using a specific query structure based on arrays 'a' and 'b'.
3. The values in arrays 'a' and 'b' determine the pattern of indices used in constructing
   queries to extract bit information about individual characters.
4. The final result is reconstructed character-by-character by inspecting the bits returned
   from queries with special patterns.

The algorithm uses a clever idea with bitwise XOR operations and precomputed structures
in arrays 'a' and 'b' to encode the bracket types at each location in the sequence.
*/

#include <cstdio>

const int a[13] = {0, 1, 1, 2, 1, 4, 9, 8, 3, 16, 34, 32, 1};
const int b[13] = {1, 1, 2, 3, 5, 7, 10, 15, 22, 31, 44, 63, 90};
int query(int l, int r) {
  printf("? %d ", r - l + 1);   // Ask for the number of queries needed
  for (int i = l; i <= r; ++i)
    printf("%d ", i);
  printf("\n");
  fflush(stdout);
  int ans;
  scanf("%d", &ans);
  return ans;
}
char str[1010];
const int maxAns = 13;
void getans(int l, int r, int t) {
  int len = r - l + 1;
  int sumcost = 0;
  for (int i = 0; i < len; ++i) {
    sumcost += ((a[i] + b[i]) << 1); // Calculate how many indices needed in total
    ++sumcost;
  }
  printf("? %d ", sumcost);
  int rep = 0;
  for (int i = l; i <= r; ++i, ++rep) {
    for (int j = 0; j < a[rep]; ++j)
      printf("%d ", i); // Add index 'i' 'a[rep]' times
    for (int j = 0; j < b[rep]; ++j)
      printf("%d %d ", i, t); // Add pair of indices (i, t) 'b[rep]' times
    for (int j = 0; j < a[rep]; ++j)
      printf("%d ", t); // Add index 't' 'a[rep]' times
    printf("%d ", t); // Add final index 't'
  }
  printf("\n");
  fflush(stdout);
  int ret;
  scanf("%d", &ret);
  rep = 1;
  for (int i = l; i <= r; ++i, rep <<= 1) { // Extract bit information using left shift
    str[i] = ((ret & rep) ? '(' : ')'); // Set character based on bit value
  }
}
int main() {
  int T;
  scanf("%d", &T);
  for (; T; --T) {
    int n;
    scanf("%d", &n);
    str[n + 1] = '\0'; // Null terminate the string
    int t;
    printf("? %d ", n); // Query all indices to get overall count
    for (int i = 1; i <= n; ++i)
      printf("%d ", i);
    printf("\n");
    fflush(stdout);
    int ret;
    scanf("%d", &ret);
    if (ret == 0) {
      t = 1; // If no regular brackets, use first index as reference
    } else {
      int l = 1, r = n;
      while (r - l > 1) {
        int mid = ((l + r) >> 1); // Binary search to find an index where a change occurs
        if (query(l, mid) > 0)
          r = mid;
        else
          l = mid;
      }
      t = r;
    }
    for (int l = 1, r = maxAns; l <= n; l += maxAns, r += maxAns) { // Process segments of size maxAns
      if (r > n)
        r = n; // Adjust for remaining elements at the end
      getans(l, r, t);
    }
    printf("! %s\n", str + 1); // Output the final bracket sequence
    fflush(stdout);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/