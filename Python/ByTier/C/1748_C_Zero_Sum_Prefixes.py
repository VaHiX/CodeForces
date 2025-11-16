# Problem: CF 1748 C - Zero-Sum Prefixes
# https://codeforces.com/contest/1748/problem/C

"""
Algorithm: Zero-Sum Prefixes
Approach:
    - Calculate prefix sums to determine where the cumulative sum equals zero.
    - For each position from right to left, maintain a frequency map of prefix sums.
    - When encountering a zero, we can change it to any value to create new zero-sums.
    - The maximum score is achieved by greedily adding the highest frequency of prefix sums
      that we've seen so far before the current index.

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case
"""

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    pref = [0] * (n + 1)
    for i in range(1, n + 1):
        pref[i] = pref[i - 1] + a[i - 1]

    ans = 0
    d = {}
    # Traverse from right to left
    for j in reversed(range(n)):
        # Count the frequency of current prefix sum
        d[pref[j + 1]] = d.get(pref[j + 1], 0) + 1
        # If current element is zero, we can change it to contribute to score
        if a[j] == 0:
            # Add the maximum count of any prefix sum we've seen so far
            ans += max(d.values())
            # Reset the map for next section
            d.clear()
    # Add the number of times 0 occurred as a prefix sum
    ans += d.get(0, 0)
    print(ans)


# https://github.com/VaHiX/CodeForces/