# Problem: CF 2171 B - Yuu Koito and Minimum Absolute Sum
# https://codeforces.com/contest/2171/problem/B

"""
Purpose: 
This code solves the problem of minimizing the absolute sum of the difference array 
by filling in the blanks (-1) in the given array with non-negative integers. 
The approach uses greedy filling to ensure minimal absolute difference sum and 
lexicographically smallest result.

Algorithms/Techniques:
- Greedy filling of missing elements
- Handling boundary conditions for first and last elements
- Ensuring lexicographically smallest array by choosing minimal values

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the array
"""

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    # If both first and last elements are -1, fill them with 0 for minimal sum
    if a[0] == -1 and a[-1] == -1:
        a[0] = a[-1] = 0
    # If only first element is -1, set it to the last element to minimize difference
    elif a[0] == -1:
        a[0] = a[-1]
    # If only last element is -1, set it to the first element to minimize difference
    elif a[-1] == -1:
        a[-1] = a[0]
    # Fill all remaining -1s with 0 to keep array lexicographically small
    for i in range(n):
        if a[i] == -1:
            a[i] = 0
    # Calculate the absolute difference between last and first element
    res = abs(a[-1] - a[0])
    print(res)
    print(*a)


# https://github.com/VaHiX/CodeForces/