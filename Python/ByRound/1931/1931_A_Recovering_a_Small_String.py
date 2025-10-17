# Problem: CF 1931 A - Recovering a Small String
# https://codeforces.com/contest/1931/problem/A

"""
Recover the lexicographically smallest 3-letter word from a given sum of letter positions.

The problem involves decoding a sum of letter positions (a=1, b=2, ..., z=26) into the 
lexicographically smallest valid 3-letter word. 

Algorithm:
1. For a given sum n:
   - If n == 27, the only valid solution is "aay" (1+1+25=27)
   - If n <= 28, we use the form "aaX" where X is chosen such that 1+1+X = n => X = n-2
   - If n >= 53, we use the form "Xzz" where X is chosen such that X+26+26 = n => X = n-52
   - For other cases, we use the form "aXz" where 1+X+26 = n => X = n-27

Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - constant extra space used
"""

t = int(input())
for _ in range(t):
    v = int(input())
    if v == 27:
        print("aay")  # Special case: only valid 3-letter word with sum 27
    elif v <= 28:
        # Form: "aaX" where X = v - 2
        k = "aa" + chr(v - 2 + 96)  # Convert position to character
        print(k)
    elif v >= 53:
        # Form: "Xzz" where X = v - 52
        k = chr(v - 52 + 96) + "zz"  # Convert position to character
        print(k)
    else:
        # Form: "aXz" where X = v - 27
        k = "a" + chr(v - 27 + 96) + "z"  # Convert position to character
        print(k)


# https://github.com/VaHiX/CodeForces/