# Problem: CF 1992 B - Angry Monk
# https://codeforces.com/contest/1992/problem/B

"""
Code Purpose:
This solution computes the minimum number of operations required to merge all pieces of a casserole back into one piece of length `n`. 
The allowed operations are:
1. Split a piece of length >= 2 into two pieces of lengths 1 and (a_i - 1).
2. Merge a piece of length > 1 with a piece of length 1 into a single piece of length (a_i + 1).

Key insight:
- Each operation either increases or decreases the number of pieces by 1.
- The total number of operations needed is determined based on:
    - Number of pieces that need to be merged to form a single piece (which is k - 1).
    - The length of the largest piece, as it determines how many splits are needed to break it down to 1s.
    
Time Complexity: O(k) per test case, due to finding the maximum element in the array.
Space Complexity: O(1), as only a few variables are used regardless of input size.

Algorithms/Techniques:
- Greedy approach
- Mathematical analysis of splitting and merging operations

"""

for _ in range(int(input())):
    n, k = map(int, input().split())  # Read n (total length) and k (number of pieces)
    mx = max(map(int, input().split()))  # Find the maximum piece length
    print((n - mx) * 2 - (k - 1))  # Calculate minimum operations using derived formula


# https://github.com/VaHiX/CodeForces/