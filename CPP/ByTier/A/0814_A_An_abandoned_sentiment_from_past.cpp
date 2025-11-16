// Problem: CF 814 A - An abandoned sentiment from past
// https://codeforces.com/contest/814/problem/A

#include <cstdio>
#include <vector>
// Flowerbox describing the code purpose, algorithms, time and space complexity
/*
Code Purpose:
This program determines whether it's possible to replace zeros in a sequence 'a' with elements from another sequence 'b' 
such that the resulting sequence is NOT strictly increasing.

Algorithms/Techniques:
- Greedy approach: For k > 1, we can always make a non-increasing sequence by placing the smallest element in 'b' where the largest zero is.
  For k = 1, we check if replacing the zero with the only element in 'b' results in a strictly increasing sequence.

Time Complexity: O(n), where n is the length of sequence a. We scan the array once to find the zero and then once more to check if the sequence is increasing.
Space Complexity: O(n), for storing the sequence a.
*/

int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  if (k > 1) {
    puts("Yes"); // If there are more than one zero, we can always arrange b such that the final sequence is not increasing
    return 0;
  }
  std::vector<long> a(n);
  long index(-1), b(0);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    if (a[p] == 0) {
      index = p; // Record the position of the only zero
    }
  }
  scanf("%ld", &b);
  a[index] = b; // Replace the zero with the single element from b
  bool sorted(true);
  for (long p = 1; p < n; p++) {
    if (a[p - 1] >= a[p]) {
      sorted = false; // If any element is greater than or equal to the next, it's not strictly increasing
      break;
    }
  }
  puts(sorted ? "No" : "Yes"); // If it was sorted (increasing), output No; otherwise output Yes
  return 0;
}


// https://github.com/VaHiX/CodeForces/