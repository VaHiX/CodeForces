// Problem: CF 991 B - Getting an A
// https://codeforces.com/contest/991/problem/B

/* 
 * Problem: B. Getting an A
 * 
 * Purpose: Determine the minimum number of lab works Vasya needs to redo 
 *          to achieve an average grade of at least 4.5 (rounded up to 5).
 * 
 * Approach:
 * - Calculate the minimum total points required to achieve an average of 4.5.
 * - Count current grades and compute how many points are missing.
 * - Greedily select the lowest grades to upgrade to 5, minimizing the number of redos.
 * 
 * Time Complexity: O(n), where n is the number of grades.
 * Space Complexity: O(1), as we use a fixed-size vector of size 6.
 * 
 * Algorithms/Techniques: 
 * - Greedy algorithm to minimize the number of redos.
 * - Vector-based counting of grades.
 */

#include <cmath>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  // Calculate the required total points to get an average of at least 4.5
  long req = ceil(4.5 * n);
  // Vector to count occurrences of each grade (2 to 5)
  std::vector<long> v(6, 0);
  long s(0);  // Current sum of grades
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    ++v[x];  // Increment count of this grade
    s += x;  // Add to current sum
  }
  // Calculate how many more points are needed
  long rem = req - s;
  long ind(0), cnt(0);  // ind is the grade index, cnt is the number of redos
  // Greedily upgrade the lowest grades to 5 until we meet the requirement
  while (rem > 0) {
    if (v[ind] > 0) {
      --v[ind];  // Use one instance of grade 'ind'
      rem -= (5 - ind);  // Points gained by upgrading to 5
      ++cnt;  // Increment redo count
    } else {
      ++ind;  // Move to next grade if current is exhausted
    }
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/