# Problem: CF 2171 D - Rae Taylor and Trees (easy version)
# https://codeforces.com/contest/2171/problem/D

"""
Purpose: Determine if a permutation can represent the order of vertices in a tree such that for every edge (u,v), u appears before v in the permutation.
Algorithm: 
    - For each position in the permutation, keep track of the minimum value seen so far.
    - If at any point the minimum value equals the number of remaining elements, then it's impossible to construct a valid tree.
Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input storage
"""

t = int(input())
for g in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    mn = n + 1  # Initialize to a value larger than any possible element
    answer = "Yes"
    for i in range(n - 1):  # Iterate up to n-1 because we are checking pairs
        value = a[i]  # Current value in permutation
        if value < mn:
            mn = value  # Update minimum value seen so far
        # If the current minimum matches the number of remaining elements,
        # it's impossible to place the remaining elements in a valid way
        if mn == n - i:
            answer = "No"
            break
    print(answer)


# https://github.com/VaHiX/CodeForces/