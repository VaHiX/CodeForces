"""
Problem: 2130B - Pathless

This script solves a problem where we need to determine if it's possible to create a path
with a specific sum 's' using elements from a given array. The solution involves analyzing
the counts of 0s, 1s, and 2s in the array to determine the valid path configuration.

Approach:
1. For each test case:
   a. Read the array length 'n' and target sum 's'
   b. Calculate the total sum of the array
   c. Calculate the remaining sum needed to reach 's'
   d. If the remaining sum is negative or exactly 1, output the path configuration
   e. Otherwise, output -1 indicating no valid path exists

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the result
"""


def solve():
    # Read number of test cases
    test_cases = int(input())

    for _ in range(test_cases):
        # Read input
        n, target_sum = map(int, input().split())
        numbers = list(map(int, input().split()))

        # Calculate total sum and remaining sum needed
        current_sum = sum(numbers)
        remaining_sum = target_sum - current_sum

        # Count occurrences of each number
        count_0 = numbers.count(0)
        count_1 = numbers.count(1)
        count_2 = numbers.count(2)

        # Determine if a valid path exists and construct it if possible
        if remaining_sum < 0 or remaining_sum == 1:
            # Construct the path by concatenating 0s, 2s, and 1s in order
            path = [0] * count_0 + [2] * count_2 + [1] * count_1
            print(" ".join(map(str, path)))
        else:
            # No valid path exists
            print(-1)


if __name__ == "__main__":
    solve()
