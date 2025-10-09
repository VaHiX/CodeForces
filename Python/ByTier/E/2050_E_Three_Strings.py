# Problem: CF 2050 E - Three Strings
# https://codeforces.com/contest/2050/problem/E

"""
E. Three Strings

Algorithm: Dynamic Programming
Time Complexity: O(|a| * |b|), where |a| and |b| are the lengths of strings a and b.
Space Complexity: O(|a| * |b|), for the DP table.

This problem involves finding the minimum number of changes required in string c 
to make it a valid interleaving of strings a and b, where characters from a and b 
are alternately appended to form c, with some characters possibly changed.

The solution uses 2D dynamic programming:
- dp[i][j] represents the minimum number of changes needed to form the first i+j characters 
  of string c using the first i characters of b and the first j characters of a.
- The recurrence considers two options at each step:
    1. Take character from b (if valid)
    2. Take character from a (if valid)
- Finally, we return dp[len(b)][len(a)] which gives the minimum cost to match entire string c.

"""

for _ in range(int(input())):
    a = "-" + input()  # Adding prefix to handle 1-based indexing
    b = "-" + input()
    c = "-" + input()
    dp = [[10**5] * len(a) for _ in range(len(b))]  # DP table initialized with large values
    dp[0][0] = 0  # Base case: no changes needed for empty prefixes
    
    for i in range(len(dp)):
        for j in range(len(dp[0])):
            if i != 0:
                # Take character from b and check if it matches c[i+j]
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + (c[i + j] != b[i]))
            if j != 0:
                # Take character from a and check if it matches c[i+j]
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + (c[i + j] != a[j]))
    
    print(dp[len(b) - 1][len(a) - 1])


# https://github.com/VaHiX/codeForces/