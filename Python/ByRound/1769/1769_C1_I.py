# Problem: CF 1769 C1 - Подкрутка I
# https://codeforces.com/contest/1769/problem/C1

"""
Algorithm: Dynamic Programming with State Tracking
Techniques: Sliding window approach with state transitions

Time Complexity: O(n), where n is the number of commits
Space Complexity: O(n), for storing the state dictionary

This solution uses dynamic programming to find the maximum length of 
consecutive days with at least one commit. For each commit day, we consider
two possibilities: keeping the commit on the same day or moving it to the next day.
We track the maximum consecutive days ending at each possible day.
"""

t = int(input())


def dp(days):
    # Dictionary to store the maximum consecutive days ending at each day
    state = {}
    for d in days:
        # Get the maximum consecutive days ending at day d-1
        prev = state.get(d - 1, 0)
        # Update the state for day d+1 (moving commit to next day)
        state[d + 1] = state.get(d, 0) + 1
        # Update the state for day d (keeping commit on same day)
        state[d] = max(state.get(d, 0), prev + 1)

    # Return the maximum value in the state dictionary
    return max(state.values())


for _ in range(t):
    n = int(input())
    days = [int(i) for i in input().split(" ")]
    print(dp(days))


# https://github.com/VaHiX/CodeForces/