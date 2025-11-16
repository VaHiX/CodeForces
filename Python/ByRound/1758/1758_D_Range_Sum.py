# Problem: CF 1758 D - Range = √Sum
# https://codeforces.com/contest/1758/problem/D

"""
Code Purpose:
This solution generates a sequence of n distinct integers satisfying the condition:
max - min = sqrt(sum). The approach constructs the sequence by:
1. Starting with a large number (3*n)
2. Adding consecutive odd numbers from (3*n + 3) to (5*n - 1)
3. Ending with another large number (5*n)
The sum of the sequence becomes a perfect square, and the difference between max and min equals the square root of that sum.

Algorithms/Techniques:
- Mathematical construction to satisfy the constraint
- Sequence generation using range and list comprehension

Time Complexity: O(n)
Space Complexity: O(n)
"""

for _ in range(int(input())):  # Read number of test cases
    n = int(input())  # Read the length of sequence
    # Construct the sequence:
    # 1. Start with 3*n
    # 2. Add odd numbers from (3*n + 3) to (5*n - 1)
    # 3. End with 5*n
    print(*([3 * n] + [i for i in range(3 * n + 3, 5 * n - 1, 2)] + [5 * n]), sep=" ")


# https://github.com/VaHiX/CodeForces/