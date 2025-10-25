# Problem: CF 1881 E - Block Sequence
# https://codeforces.com/contest/1881/problem/E

"""
Code Purpose:
This code solves the problem of finding the minimum number of deletions required to make a sequence "beautiful".
A beautiful sequence is defined as a series of blocks where each block starts with its length followed by its elements.
The algorithm uses dynamic programming to determine the minimum number of operations needed.

Algorithm/Techniques:
- Dynamic Programming (DP)
- Reverse iteration approach
- Greedy DP state transitions

Time Complexity: O(n), where n is the length of the input sequence.
Space Complexity: O(n), for the DP array 'res'.

The key idea is:
1. Reverse the input array to process from end to start.
2. For each element, determine if it can start a new block.
3. Use a DP array where res[i] represents the minimum deletions needed for the first i elements.
4. If element at index i can form a block of length s[i], update DP accordingly.
"""

def solution():
    n = int(input())
    s = list(map(int, input().split()))
    s.reverse()  # Reverse the sequence to process from end to start
    res = [0]  # DP array initialized with 0
    
    for i in range(n):
        # Check if s[i] can be the length of a block ending at position i
        # If s[i] <= i and it's beneficial to use previous state
        if s[i] <= i and res[i - s[i]] < res[i] + 1:
            res.append(res[i - s[i]])  # Use previous state efficiently
        else:
            res.append(res[i] + 1)  # Increment deletion count
    
    print(res[-1])  # Output the minimum deletions needed


N = int(input()) + 1
while N := N - 1:
    solution()


# https://github.com/VaHiX/CodeForces/