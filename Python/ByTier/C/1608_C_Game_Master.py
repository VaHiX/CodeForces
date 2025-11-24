# Problem: CF 1608 C - Game Master
# https://codeforces.com/contest/1608/problem/C

"""
Purpose: Determine which players can potentially win a tournament based on their strengths on two different maps.
Algorithm:
- For each player, we check if they can be a winner by analyzing their strength on both maps.
- We sort players by strength on each map in descending order.
- Then we iterate through the sorted lists to find players who, in the worst-case scenario, can still win.
- Time Complexity: O(n log n) due to sorting
- Space Complexity: O(n) for storing sorted data and result
"""

for _ in range(int(input())):  # Process each test case
    n = int(input())  # Number of players
    # Create list of (strength, player_index) for first map and sort in descending order
    x = [(int(i[1]), i[0]) for i in enumerate(input().split())]  # x[i][0] = strength, x[i][1] = player index
    y = [(int(i[1]), i[0]) for i in enumerate(input().split())]  # y[i][0] = strength, y[i][1] = player index
    x = sorted(x, reverse=True)  # Sort by strength in descending order for first map
    y = sorted(y, reverse=True)  # Sort by strength in descending order for second map
    q = set()  # Set to store indices of players who can potentially win
    # Iterate to find potential winners by examining the top players in each map
    for i in range(n):
        q.add(x[i][1])  # Add player index from first map
        q.add(y[i][1])  # Add player index from second map
        # If we've added all players to set, break early
        if len(q) == i + 1:
            break
    ans = ["0"] * n  # Initialize result array with '0'
    for i in q:  # Mark players who can win with '1'
        ans[i] = "1"
    print("".join(ans))  # Print final result string


# https://github.com/VaHiX/CodeForces/