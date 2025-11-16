# Problem: CF 1922 E - Increasing Subsequences
# https://codeforces.com/contest/1922/problem/E

"""
Algorithm: Constructing an array with exactly X increasing subsequences using binary representation and careful number assignment.

The key idea is based on the fact that the number of increasing subsequences of an array can be represented as a sum of powers of 2. 
This is done by using a binary decomposition approach: we try to construct the number X - 1 in binary form, and map each bit to a specific value in the array.

We assign values as follows:
- For each bit set in (X - 1), we add a value equal to 1000, 999, ... (in descending order)
- For each bit not set, we add a negative value, again in descending order (to maintain increasing subsequence count)

Time Complexity: O(log(X)) - Since we process the bits of (X - 1).
Space Complexity: O(log(X)) - For storing the answer array.
"""

import sys

input = sys.stdin.readline


for t in range(int(input())):
    X = int(input())
    original_X = X
    X -= 1  # Adjust for 0-based indexing of increasing subsequences (we want X total)
    ans = []
    i = 1000  # Starting value to assign, decreases with each step
    while X:
        if X & 1:  # If the least significant bit is 1
            ans.append(i)
            X = (X - 1) // 2  # Move to next bit (subtract 1 and divide by 2)
        else:
            ans.append(-i)
            X = X - 1  # Move to next bit (subtract 1)
        i -= 1

    ans.reverse()  # Reverse to get correct order (from least significant to most significant bit)
    print(len(ans))
    print(*ans)


# https://github.com/VaHiX/CodeForces/