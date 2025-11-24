# Problem: CF 1992 A - Only Pluses
# https://codeforces.com/contest/1992/problem/A

"""
Code Purpose:
This code solves the problem of maximizing the product a×b×c by incrementing any of the three integers at most 5 times.
The strategy is to always increment the smallest of the three numbers to maximize the product.

Algorithms/Techniques:
- Greedy approach: Always increase the smallest number to optimize the product.
- Iterative process: Loop up to 5 times to distribute increments optimally.

Time Complexity: O(1) - The loop runs a constant number of times (at most 5), and each iteration is O(1).
Space Complexity: O(1) - Only a constant amount of extra space is used.
"""

t = int(input())
for i in range(t):
    a, b, c = map(int, input().split())
    for i in range(5): # Perform at most 5 increments
        if a <= b and a <= c:
            a += 1 # Increment smallest number
        elif b <= a and b <= c:
            b += 1 # Increment smallest number
        else:
            c += 1 # Increment smallest number
    print(a * b * c) # Output the maximum possible product


# https://github.com/VaHiX/CodeForces/