# Problem: CF 1680 E - Moving Chips
# https://codeforces.com/contest/1680/problem/E

"""
Algorithm: Dynamic Programming
Techniques: 
- Segment processing: Identify the leftmost and rightmost chips to focus only on that range
- DP states: 
    dp1 = min moves to reach column i with chip in row 1
    dp2 = min moves to reach column i with chip in row 2

Time Complexity: O(n) - single pass through the string
Space Complexity: O(1) - only using a few variables for DP
"""

for _ in range(int(input())):
    n = int(input())
    s1, s2 = input(), input()

    # Find the leftmost and rightmost chip positions
    l = r = -1
    for i in range(n):
        if s1[i] == "*" or s2[i] == "*":
            if l == -1:
                l = i
            r = i

    # Initialize DP values for the first chip position
    dp1 = int(s2[l] == "*")  # moves to get chip to row 1 at first chip position
    dp2 = int(s1[l] == "*")  # moves to get chip to row 2 at first chip position

    # Iterate from second chip position to last chip position
    for i in range(l + 1, r + 1):
        # Calculate new DP values for both rows
        # dp1: minimum moves to reach column i with chip in row 1
        # dp2: minimum moves to reach column i with chip in row 2
        ndp1 = min(dp1 + 1 + int(s2[i] == "*"), dp2 + 2)  # moving from row 2 to row 1
        ndp2 = min(dp2 + 1 + int(s1[i] == "*"), dp1 + 2)  # moving from row 1 to row 2
        
        # Update DP values
        dp1, dp2 = ndp1, ndp2
    
    # Return the minimum of the final DP values
    print(min(dp1, dp2))


# https://github.com/VaHiX/CodeForces/