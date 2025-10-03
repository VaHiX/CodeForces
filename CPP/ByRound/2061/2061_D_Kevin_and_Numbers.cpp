// Problem: CF 2061 D - Kevin and Numbers
// https://codeforces.com/contest/2061/problem/D

/*
D. Kevin and Numbers
Problem Description:
Given two sequences a and b of lengths n and m respectively, determine if it's possible to transform sequence a into sequence b using the following operation:
- Select two integers x, y on the blackboard such that |x - y| <= 1.
- Erase them and write down x + y.

Observation:
- The sum of elements must remain constant: sum(a) = sum(b).
- Elements in b can be formed by combining adjacent elements in a if their difference is at most 1.
- We use a greedy approach with multisets to simulate merging operations.

Algorithms/Techniques:
- Multisets with greater comparator to process largest elements first.
- Greedy matching and decomposition of large values into smaller ones, ensuring constraints are satisfied.

Time Complexity:
O(n log n + m log m) per test case due to insertion and deletion in multisets.
Space Complexity:
O(n + m) for storing the multisets.
*/

#include <cstdio>
#include <set>
#include <functional>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::multiset<long, std::greater<long>> msa, msb; // Multisets to track elements in a and b
    long long diff(0); // Difference between sums of a and b
    
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      msa.insert(x); // Insert all elements from sequence a
      diff += x;
    }
    
    for (long p = 0; p < m; p++) {
      long x;
      scanf("%ld", &x);
      if (msa.count(x)) { // If x exists in msa, remove one instance
        msa.erase(msa.find(x));
      } else { // Otherwise, insert into msb
        msb.insert(x);
      }
      diff -= x; // Subtract sum of b from sum of a
    }
    
    if (diff) {
      puts("No"); // If sums differ, impossible to transform
      continue;
    }
    
    // Greedy process: try to match large elements in msb with small elements in msa
    while (!msb.empty() && !msa.empty() && msa.size() >= msb.size() &&
           *msb.begin() >= *msa.begin()) {
      long x = *msb.begin(); // Get smallest element in msb (largest due to greater comparator)
      long y = *msa.begin(); // Get smallest element in msa
      
      msb.erase(msb.begin()); // Remove smallest from msb
      if (x == *msa.begin()) { // If x equals smallest in msa, remove that too
        msa.erase(msa.begin());
      } else {
        // Decompose x into two parts and insert back to msb
        msb.insert(x / 2);
        msb.insert((x + 1) / 2);
      }
    }
    
    // If both multisets are empty, transformation is possible
    puts(msa.empty() && msb.empty() ? "Yes" : "No");
  }
}


// https://github.com/VaHiX/codeForces/