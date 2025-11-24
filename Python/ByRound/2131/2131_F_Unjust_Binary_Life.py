# Problem: CF 2131 F - Unjust Binary Life
# https://codeforces.com/contest/2131/problem/F

"""
F. Unjust Binary Life
Algorithm: Prefix Sum, Two Pointers, Sorting
Time Complexity: O(n log n) per test case (due to sorting)
Space Complexity: O(n) for storing the prefix sums

This program solves a problem involving binary strings and calculates a specific metric
based on the difference between two binary strings A and B of length n.
Approach:
1. Convert each character in the strings to 0 or 2 (instead of 0 or 1) for calculation purposes.
2. Compute prefix sums for both strings.
3. Adjust the prefix sums by subtracting the 1-based index from each element.
4. Sort both modified prefix sum arrays.
5. Use a two-pointer technique to calculate the required sum efficiently.
6. The final result is derived from the calculated sum and adjusted by a formula.
"""

import sys


def read_input():
    """Helper function to read input more efficiently."""
    return sys.stdin.readline().rstrip()


def solve():
    """
    Solves a single test case for the Unjust Binary Life problem.
    Returns:
        int: The calculated result for the given test case.
    """
    n = int(read_input())
    str_a = read_input()
    str_b = read_input()
    # Convert characters to 0 or 2 (instead of 0 or 1) for easier calculation
    prefix_a = [(2 if ch == "1" else 0) for ch in str_a]
    prefix_b = [(2 if ch == "1" else 0) for ch in str_b]
    # Compute prefix sums
    for i in range(1, n):
        prefix_a[i] += prefix_a[i - 1]
        prefix_b[i] += prefix_b[i - 1]
    # Adjust the prefix sums by subtracting the 1-based index from each element
    for i in range(n):
        prefix_a[i] -= i + 1
        prefix_b[i] -= i + 1
    # Sort both modified prefix sum arrays
    prefix_a.sort()
    prefix_b.sort()
    # Initialize variables for two-pointer technique
    left_sum = sum(prefix_b)
    right_sum = 0
    split_index = n - 1
    result = 0
    # Two-pointer technique to compute contribution of each element from prefix_a
    for x in prefix_a:
        while split_index >= 0 and prefix_b[split_index] + x >= 0:
            left_sum -= prefix_b[split_index]
            right_sum += prefix_b[split_index]
            split_index -= 1
        # Calculate left and right contributions
        left_contribution = left_sum + (split_index + 1) * x
        right_contribution = right_sum + (n - split_index - 1) * x
        result += -left_contribution + right_contribution
    # Final adjustment to get the required sum
    return (-result + n * n * (n + 1)) // 2


def main():
    """Main function to handle multiple test cases."""
    test_cases = int(read_input())
    for _ in range(test_cases):
        print(solve())


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/