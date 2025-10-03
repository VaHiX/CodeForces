# Problem: CF 2132 E - Arithmetics Competition
# https://codeforces.com/contest/2132/problem/E

"""
E. Arithmetics Competition
Time Complexity: O(Q log K + (N + M) log (N + M))
Space Complexity: O(N + M)

This program solves a problem where two teams (Vadim and Kostya) need to select cards from their respective arrays A and B,
such that the total number of selected cards is exactly K, with constraints on how many cards can be taken from each array.
The goal is to maximize the sum of these selected elements.

Approach:
1. Sort both arrays in descending order to prioritize higher values
2. Precompute prefix sums for both arrays to quickly calculate sums of top x elements
3. For each query, use binary search over possible splits between the two arrays to find the maximum sum
   under the given constraints

Algorithms/Techniques:
- Sorting
- Prefix Sum Arrays
- Binary Search
"""

import sys
from itertools import accumulate


def main():
    input = sys.stdin.read
    data = input().split()
    idx = 0
    num_test_cases = int(data[idx])
    idx += 1
    for _ in range(num_test_cases):
        size_a, size_b, num_queries = map(int, data[idx : idx + 3])
        idx += 3
        array_a = list(map(int, data[idx : idx + size_a]))
        idx += size_a
        array_b = list(map(int, data[idx : idx + size_b]))
        idx += size_b
        array_a.sort(reverse=True)  # Sort A in descending order to maximize sum
        array_b.sort(reverse=True)  # Sort B in descending order to maximize sum
        prefix_a = [0] + list(accumulate(array_a))  # Prefix sum of sorted A
        prefix_b = [0] + list(accumulate(array_b))  # Prefix sum of sorted B
        for __ in range(num_queries):
            max_from_a, max_from_b, total_elements = map(int, data[idx : idx + 3])
            idx += 3
            left = max(0, total_elements - max_from_b)  # Minimum cards from A to satisfy constraint
            right = min(max_from_a, total_elements)     # Maximum cards from A to satisfy constraint
            best_sum = 0
            while left <= right:
                mid = (left + right) // 2
                current_sum = prefix_a[mid] + prefix_b[total_elements - mid]
                next_sum = 0
                if mid < right:
                    next_sum = prefix_a[mid + 1] + prefix_b[total_elements - mid - 1]
                if current_sum < next_sum:
                    left = mid + 1
                    best_sum = max(best_sum, next_sum)
                else:
                    right = mid - 1
                    best_sum = max(best_sum, current_sum)
            print(best_sum)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/