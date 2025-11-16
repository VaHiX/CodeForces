// Problem: CF 682 B - Alyona and Mex
// https://codeforces.com/contest/682/problem/B

/*
Purpose: To find the maximum possible value of the mex (minimum excludant) of an array
         after performing any number of operations where each element can be decreased
         to any positive integer smaller than its current value.

Algorithms/Techniques: 
- Sort the array to process elements in ascending order.
- Use a greedy approach to determine the mex by tracking the smallest missing positive integer.

Time Complexity: O(n log n) due to sorting, where n is the number of elements in the array.
Space Complexity: O(1) if we ignore the space used for input storage, as we only use a constant amount of extra space.

*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld\n", &n);
  std::vector<long> a(n, 0);
  for (long p = 0; p < n; p++) {
    scanf("%ld ", &a[p]);
  }
  sort(a.begin(), a.end()); // Sort the array to process elements in ascending order
  long mex(1); // Initialize mex to 1, the smallest positive integer
  for (long p = 0; p < n; p++) {
    if (mex <= a[p]) {
      ++mex; // If current element is >= mex, we can include mex in our result and increment mex
    }
  }
  printf("%ld\n", mex);
  return 0;
}


// https://github.com/VaHiX/CodeForces/