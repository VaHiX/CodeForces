# Problem: CF 2037 E - Kachina's Favorite Binary String
# https://codeforces.com/contest/2037/problem/E

"""
Algorithm: Binary String Reconstruction using Subsequence Queries
Techniques: Interactive Problem, Greedy Reconstruction, Prefix Sum Analysis

Time Complexity: O(n^2) in worst case due to up to n queries, each with a linear scan for counting subsequences.
Space Complexity: O(n) for storing the answer string.

This solution attempts to reconstruct a binary string by querying for the number of "01" subsequences 
in various ranges. It makes strategic queries and uses the results to determine each character of the string.
If the string cannot be uniquely determined after n queries, it returns "IMPOSSIBLE".
"""

Ints = lambda: map(int, input().split())


def query(l, r):
    # If l == r, there are no subsequences of "01", so return 0
    if l == r:
        return 0
    print("?", l, r, flush=True)
    return int(input())


def test():
    n = int(input())
    # Initialize answer array with placeholder "-"
    ans = ["-" for _ in range(n)]
    # Store previous query result
    prev = 0
    # Query the entire string to start
    if (prev := query(1, n)) == 0:
        # If total count of "01" is 0, then no "01" exists in the string
        # This implies all characters are the same (either all 0s or all 1s)
        # But since we cannot distinguish between "0000" or "1111", it's impossible
        return "! IMPOSSIBLE"
    
    cur = 0
    # Start from the end and work backwards to determine individual characters
    i = n - 1
    # Continue while we're still getting a count > 0
    while (cur := query(1, i)) > 0:
        # If current count equals previous count, this character is '0'
        if cur == prev:
            ans[i] = "0"
        else:
            # Otherwise, it's '1' and update previous count
            ans[i] = "1"
            prev = cur
        i -= 1
    
    # When loop ends, set the last character to '1' 
    ans[i] = "1"
    
    # Fill in the remaining positions to make the final string valid
    # The number of zeros should match the count of "01" subsequences found
    for j in range(i - prev, i):
        ans[j] = "0"
    for j in range(0, i - prev):
        ans[j] = "1"

    return "! " + "".join(ans)


for _ in range(int(input())):
    print(test(), flush=True)


# https://github.com/VaHiX/CodeForces/