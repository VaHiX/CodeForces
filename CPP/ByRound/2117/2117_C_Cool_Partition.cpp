// Problem: CF 2117 C - Cool Partition
// https://codeforces.com/contest/2117/problem/C

/*
C. Cool Partition
Algorithm: Greedy with HashSet
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The problem asks us to find the maximum number of segments in a "cool" partition,
where every element in a segment must also appear in the next segment.
We use a greedy approach:
- We maintain two sets: ms (current segment elements) and fs (elements in the current window).
- As we iterate through the array, we add elements to fs.
- When an element already exists in ms, we remove it from ms.
- If ms becomes empty, we have found a valid segment boundary:
    - Increment the segment count
    - Move all elements from fs to ms
    - Clear fs for next segment

This ensures that each new segment contains only elements that were present in the previous one,
making it a valid cool partition.

Sample Input:
8
6
1 2 2 3 1 5
8
1 2 1 3 2 1 3 2
5
5 4 3 2 1
10
5 8 7 5 8 5 7 8 10 9
3
1 2 2
9
3 3 1 4 3 2 4 1 2
6
4 5 4 5 6 4
8
1 2 1 2 1 2 1 2

Sample Output:
2
3
1
3
1
3
3
4
*/

#include <cstdio>
#include <unordered_set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::unordered_set<long> ms, fs; // ms: elements of current segment, fs: elements in current window
    long cnt(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      fs.insert(x); // Add x to window
      if (ms.count(x)) { // If x was already in current segment
        ms.erase(x);   // Remove it from current segment
      }
      if (ms.empty()) { // If no elements left in current segment
        ++cnt;         // Start new segment
        ms = fs;       // Move window to current segment
        fs.clear();    // Clear window for next iteration
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/