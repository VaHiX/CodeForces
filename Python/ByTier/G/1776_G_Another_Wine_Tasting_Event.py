# Problem: CF 1776 G - Another Wine Tasting Event
# https://codeforces.com/contest/1776/problem/G

"""
Code purpose: This code finds the maximum number of white wines (W) that can be included in any contiguous subsequence of length n within a string of red (R) and white (W) wines.

Algorithms/Techniques: Sliding window technique to efficiently compute the maximum count of white wines in any substring of length n.

Time Complexity: O(2^n - 1) = O(len(s)), since we iterate through the string once.
Space Complexity: O(1), as we only use a constant amount of extra space.

The problem requires assigning intervals of at least n wines to each of n critics such that all critics taste the same number of white wines.
This solution uses a sliding window to find the maximum number of white wines in any consecutive subsequence of length n.
"""

def solve():
    n = int(input())
    s = input()
    ans = 0
    # Count white wines in the first window of size n
    for i in range(n):
        ans += s[i] == "W"
    tmp = ans  # tmp holds current window's white wine count
    # Slide the window across the rest of the string
    for i in range(n, len(s)):
        tmp += s[i] == "W"      # Add new element to window
        tmp -= s[i - n] == "W"  # Remove element that's no longer in window
        ans = max(ans, tmp)     # Update maximum
    print(ans)


t = 1
for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/