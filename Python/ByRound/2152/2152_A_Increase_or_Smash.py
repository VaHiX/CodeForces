# Problem: CF 2152 A - Increase or Smash
# https://codeforces.com/contest/2152/problem/A

"""
Algorithm: Count Unique Elements
Approach:
- For each test case, we are given an array of integers.
- The task is to determine the minimum number of operations (Increase and Smash) needed to transform an initial array of zeros into the target array.
- Key insight:
  - Each unique value (except 0) in the sorted array requires at least one Increase operation.
  - Each time a new value appears that's greater than the previous one, we need another increase operation.
  - However, the problem can be simplified:
    - The number of distinct elements in the array equals the number of times we must increase (excluding the first element).
    - We start with all zeros, so to reach a value `x`, we must perform at least one increase operation.
    - If any element is zero, it doesn't contribute to an increase but may require a smash operation.
    - But actually the key observation is that:
      - The number of distinct non-zero values in order gives us exactly how many operations we need.
      - More precisely: it's `2 * (number_of_unique_elements) - 1` if the array contains multiple unique elements, or just 1 if all are same.

Complexity:
- Time complexity: O(n log n), due to sorting set and set operations.
- Space complexity: O(n), for storing set of unique elements.
"""

t = int(input())
for i in range(t):
    n = int(input())
    k = list(map(int, input().split()))
    j = len(set(k))  # Count unique elements
    print((j * 2) - 1)  # Calculate minimum operations


# https://github.com/VaHiX/CodeForces/