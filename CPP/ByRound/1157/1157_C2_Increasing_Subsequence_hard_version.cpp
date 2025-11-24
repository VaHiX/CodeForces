// Problem: CF 1157 C2 - Increasing Subsequence (hard version)
// https://codeforces.com/contest/1157/problem/C2

/*
C2. Increasing Subsequence (hard version)
Algorithm: Greedy with careful comparison logic to build longest strictly increasing subsequence
Time Complexity: O(n)
Space Complexity: O(n)

The problem asks to construct the longest strictly increasing sequence by choosing elements from either the left or right end of an array.
We use a greedy approach:
- At each step, we compare the available left and right elements.
- If one is greater than the current element in our sequence and the other is not,
  we choose the one that improves our sequence.
- If both are greater, we check which prefix allows us to extend the sequence further
  by simulating how many elements we can take from each side.
- When both choices are equally good or bad, we prefer the left one (or right if it's safer).
*/

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  long left(0), right(n - 1), cur(0);
  std::vector<char> res;
  while (left <= right) {
    // If the left element is valid and better than right, take it
    if (cur < a[left] && a[left] < a[right]) {
      res.push_back('L');
      cur = a[left];
      ++left;
    } 
    // If the right element is valid and better than left, take it
    else if (cur < a[right] && a[right] < a[left]) {
      res.push_back('R');
      cur = a[right];
      --right;
    } 
    // Both are good but equal; simulate which side gives more elements
    else if (cur < a[left] && a[left] == a[right]) {
      long tl(cur), cntl(0);
      while (left + cntl < n && tl < a[left + cntl]) {
        tl = a[left + cntl];
        ++cntl;
      }
      long tr(cur), cntr(0);
      while (right - cntr >= 0 && tr < a[right - cntr]) {
        tr = a[right - cntr];
        ++cntr;
      }
      if (cntl >= cntr) {
        res.push_back('L');
        cur = a[left];
        ++left;
      } else {
        res.push_back('R');
        cur = a[right];
        --right;
      }
    } 
    // Only left is valid, take it
    else if (cur < a[left]) {
      res.push_back('L');
      cur = a[left];
      ++left;
    } 
    // Only right is valid, take it
    else if (cur < a[right]) {
      res.push_back('R');
      cur = a[right];
      --right;
    } 
    // Nothing is valid, stop
    else {
      break;
    }
  }
  printf("%ld\n", res.size());
  for (long p = 0; p < res.size(); p++) {
    printf("%c", res[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/