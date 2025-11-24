# Problem: CF 2131 A - Lever
# https://codeforces.com/contest/2131/problem/A

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

Algorithms/Techniques: Greedy, Simulation

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the weights

"""

def solve():
    num_test_cases = int(input())
    for _ in range(num_test_cases):
        num_weights = int(input())
        current_weights = list(map(int, input().split()))
        target_weights = list(map(int, input().split()))
        total_difference = 1  # Start with 1 because at least one operation is needed
        for i in range(num_weights):
            # For each weight, if current position is greater than target,
            # we need (current - target) operations to reduce it
            total_difference += max(0, current_weights[i] - target_weights[i])
        print(total_difference)


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/