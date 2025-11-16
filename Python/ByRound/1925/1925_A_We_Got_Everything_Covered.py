# Problem: CF 1925 A - We Got Everything Covered!
# https://codeforces.com/contest/1925/problem/A

"""
Purpose: 
    This code generates a string s such that all possible strings of length n 
    formed using the first k lowercase English alphabets occur as a subsequence in s.
    
    The approach is to repeat the first k letters of the alphabet exactly n times 
    in sequence. This ensures that every combination of k letters repeated n times
    appears as a subsequence.

Algorithms/Techniques:
    - Greedy construction of the string
    - Direct repetition of first k characters n times

Time Complexity: O(n * k)
    - For each test case, we construct a string of length n * k.
    - The string construction is linear in the length of the output string.
    
Space Complexity: O(n * k)
    - We store the resulting string of length n * k.
"""

N = int(input())

s = "abcdefghijklmnopqrstuvwxyz"

for i in range(N):
    n, k = [int(i) for i in input().split()]
    print(n * s[:k])  # Repeat the first k characters n times to form the result string


# https://github.com/VaHiX/CodeForces/