# Problem: CF 2145 A - Candies for Nephews
# https://codeforces.com/contest/2145/problem/A

"""
Task: Determine minimum additional candies needed so that n candies can be evenly distributed among 3 nephews.

Algorithm/Technique:
- Use modular arithmetic to find the remainder when n is divided by 3
- If remainder is 0, no additional candies needed
- Otherwise, additional candies = (3 - remainder)

Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - only using a few variables regardless of input size

Input:
- t: number of test cases (1 ≤ t ≤ 100)
- n: number of candies (1 ≤ n ≤ 100)

Output:
- For each test case, minimum additional candies needed
"""

t = int(input())
for k in range(t):
    n = int(input())
    if n % 3 == 0:  # If n is divisible by 3, no extra candies needed
        print(0)
    else:
        h = 3 - n % 3  # Calculate how many more needed to reach next multiple of 3
        print(h)


# https://github.com/VaHiX/CodeForces/