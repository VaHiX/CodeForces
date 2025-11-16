# Problem: CF 2056 C - Palindromic Subsequences
# https://codeforces.com/contest/2056/problem/C

"""
Purpose: Generate a sequence of length n such that the number of longest palindromic subsequences (g(a)) is greater than n.
Algorithm/Technique: 
    - Construct a sequence where we have a pattern that allows many palindromic subsequences of maximum length.
    - The sequence is built to ensure a large number of palindromic subsequences by repeating certain elements strategically.
    
Time Complexity: O(n) - linear time to construct the result list.
Space Complexity: O(n) - space to store the result list of size n.

The approach uses a construction strategy:
    - Start with [1, 1, 2, 3] to initiate a pattern
    - Fill the middle with increasing numbers from 4 to n-2
    - End with [1, 2] to ensure the constructed sequence allows for many palindromic subsequences of length 3.
    - This ensures f(a)=3 and g(a) > n for n >= 6.
"""

for _ in range(int(input())):
    n = int(input())
    res = [1, 1, 2, 3] + [i for i in range(4, n - 2)] + [1, 2]
    print(*res)


# https://github.com/VaHiX/CodeForces/