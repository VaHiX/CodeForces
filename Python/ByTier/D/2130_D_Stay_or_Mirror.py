"""
Problem: 2130D - Stay or Mirror

This script solves a problem where we need to calculate the minimum number of operations
to transform a permutation into a sorted sequence. Each operation allows us to either
keep an element as is or replace it with its mirror position in the sequence.

Approach:
1. For each element in the permutation, count how many elements before it are greater than it.
2. For each element, calculate the minimum between:
   - The count of greater elements before it (keeping it as is)
   - The count of elements that would be less than it if mirrored (n - p[j] - count)
3. Sum these minimum values to get the total minimum operations needed.

Time Complexity: O(n^2) per test case, where n is the length of the permutation
Space Complexity: O(n) to store the permutation
"""


def solve():
    # Read number of test cases
    test_cases = int(input())

    for _ in range(test_cases):
        # Read input
        n = int(input())
        permutation = list(map(int, input().split()))
        total_operations = 0

        for current_idx in range(n):
            # Count number of elements before current_idx that are greater than permutation[current_idx]
            greater_before = 0
            for prev_idx in range(current_idx):
                if permutation[prev_idx] > permutation[current_idx]:
                    greater_before += 1

            # Calculate the minimum operations for the current element
            mirror_operations = n - permutation[current_idx] - greater_before
            total_operations += min(greater_before, mirror_operations)

        print(total_operations)


if __name__ == "__main__":
    solve()
