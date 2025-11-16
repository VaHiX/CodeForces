# Problem: CF 1771 B - Hossam and Friends
# https://codeforces.com/contest/1771/problem/B

"""
Algorithm: Sliding Window + Prefix Maximum
Time Complexity: O(n + m) per test case
Space Complexity: O(n) per test case

This solution uses a preprocessing approach to determine the leftmost
friend in a subsegment that blocks it from being "good". For each position,
we track the furthest friend that cannot be in the same subsegment as the current one.
This allows us to compute the number of good subsegments in linear time.

The key idea is:
- For each pair (x, y) that are not friends, we record that in any subsegment
  that includes both x and y, the subsegment cannot be good.
- We want to find how many subsegments [a, b] have all friends pairwise known.
- To do this, we track the furthest "bad" friend to the left of each position.
- Then, for each position j, we count how many valid subsegments end at j.
"""

t = int(input())
for i in range(t):
    n, m = map(int, input().split())
    a = [0] * n  # Array to store the latest conflicting index for each position
    
    # Process each pair of friends who don't know each other
    for j in range(m):
        z = list(map(int, input().split()))
        z.sort()  # Sort to put smaller index first
        # Update the maximum bad index for the larger index
        a[z[1] - 1] = max(a[z[1] - 1], z[0])
    
    # Propagate the max bad index forward (prefix max)
    for j in range(1, n):
        a[j] = max(a[j], a[j - 1])
    
    # Count total good subsegments
    ans = 0
    for j in range(n):
        # Number of valid subsegments ending at position j
        # is (j + 1) - a[j], where a[j] is the leftmost bad friend
        ans += j + 1 - a[j]
    
    print(ans)


# https://github.com/VaHiX/CodeForces/