# Problem: CF 1767 C - Count Binary Strings
# https://codeforces.com/contest/1767/problem/C

"""
Count Binary Strings

Algorithm:
This problem is solved using dynamic programming. The idea is to build the binary string from left to right, keeping track of the number of valid strings that end at each position with a specific character. 

We define dp[i][j] as the number of valid ways to fill the first i positions of the string such that the i-th character is j (where j=0 or j=1).

The constraints are defined for all substrings [i,j] with a[i,j] which can be:
- 1: all characters in substring must be the same
- 2: at least two different characters in substring
- 0: no constraint

Time Complexity: O(n^3)
Space Complexity: O(n^2)

Approach:
1. Parse input matrix a[i][j] which represents constraints for substring [i,j]
2. Use dynamic programming where dp[i][j] stores number of valid strings of length i ending with character j
3. For each position, update dp values based on constraint checks
4. Sum all dp[n][j] for final answer

"""

n = int(input())
N = 105
a = [0] * N
for i in range(1, n + 1):
    a[i] = [0] * i + list(map(int, input().split()))
f = [[0] * N for i in range(N)]
mod = 998244353
f[1][1] = 2  # Initially we have 2 ways to fill first position (0 or 1)

# Iterate through all positions of the string
for i in range(1, n + 1):
    for j in range(1, i + 1):
        # Check if current configuration is valid given constraints
        flag = True
        for k in range(1, i + 1):
            if a[k][i] == 1 and k < j:
                flag = False  # If any 1 constraint (all same) is violated
            if a[k][i] == 2 and k >= j:
                flag = False  # If any 2 constraint (at least two different) is violated
        # If constraints are satisfied, accumulate the number of valid sequences
        if flag == False:
            f[i][j] = 0
        f[i + 1][j] = (f[i + 1][j] + f[i][j]) % mod  # Propagate valid sequences to next position with same ending character
        f[i + 1][i + 1] = (f[i + 1][i + 1] + f[i][j]) % mod  # Propagate to new character (i+1) at position i+1

res = 0
# Sum up all valid ways to finish at position n
for i in range(1, n + 1):
    res = (res + f[n][i]) % mod
print(res)


# https://github.com/VaHiX/CodeForces/