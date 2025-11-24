// Problem: CF 1324 D - Pair of Topics
// https://codeforces.com/contest/1324/problem/D

/*
D. Pair of Topics
Algorithm: Two-pointer technique after transformation
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for the array

The problem asks to count pairs (i, j) where i < j and a_i + a_j > b_i + b_j.
Rearranging the inequality: a_i - b_i + a_j - b_j > 0.
We can transform each element to d_i = a_i - b_i, then we need to count pairs
where d_i + d_j > 0. After sorting the transformed array, we use two pointers:
for each element from the end, we count how many elements before it sum up to > 0.

*/

#import <regex>
int i, j, n, a[7 << 15]; // i,j loop counters; n size; a array for input
long long r; // result counter
int main() {
  for (scanf("%d", &n); i < n; i++) // read n topics and store a[i]
    scanf("%d", a + i);
  for (; j < n; j++) // read b[i] and compute difference a[i] -= b[i]
    scanf("%d", &i), a[j] -= i;
  std::sort(a, a + n); // sort the transformed array
  while (--j) // loop from end of sorted array
    if (a[n - j - 1] + a[n - 1] > 0) // check if current + max sum > 0
      r += j, n--; // add valid pairs and decrease window size
  printf("%lld", r); // output result
}


// https://github.com/VaHiX/codeForces/