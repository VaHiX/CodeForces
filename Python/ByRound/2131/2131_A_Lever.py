"""
Problem: CF2131A - Lever

This program solves the Lever problem from Codeforces Round 809 (Div. 2).
It calculates the minimum number of operations needed to balance a lever by
adjusting weights on either side.

Approach:
1. Read the number of test cases
2. For each test case:
   - Read the number of weights and their current positions
   - Read the target positions for the weights
   - Calculate the total difference between current and target positions
   - The answer is total_difference + 1 (minimum operations needed)

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the weights
"""


def solve():
    # Read number of test cases
    num_test_cases = int(input())

    for _ in range(num_test_cases):
        # Read number of weights
        num_weights = int(input())

        # Read current and target weights
        current_weights = list(map(int, input().split()))
        target_weights = list(map(int, input().split()))

        # Calculate total difference
        total_difference = 1  # Start with 1 as per problem statement
        for i in range(num_weights):
            # Add the difference if current weight is greater than target
            total_difference += max(0, current_weights[i] - target_weights[i])

        print(total_difference)


if __name__ == "__main__":
    solve()
