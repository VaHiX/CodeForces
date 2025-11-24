# Problem: CF 1492 C - Maximum width
# https://codeforces.com/contest/1492/problem/C

"""
Algorithm: Two-pointer / Greedy Approach
Time Complexity: O(n + m)
Space Complexity: O(m)

The problem asks to find the maximum width of a beautiful sequence, which is a subsequence
of string s that matches string t, where width is the maximum distance between consecutive
positions in the subsequence.

The approach:
1. First, we find the leftmost possible positions for each character of t in s from left to right.
   This gives us a list 'a' where a[i] is the position of t[i] in s.
2. Then, we traverse t from right to left to find the rightmost possible positions for each character.
   For each step, we calculate the gap between the current rightmost position and the corresponding
   leftmost position and update the answer with the maximum gap.
"""

n, m = map(int, input().split())
s = input()
t = input()
a = []  # Store the leftmost positions for each character in t
ans = 0
i = -1  # Starting index for searching in s

# Find leftmost valid positions for each character in t
for x in t[:-1]:  # Process all characters except the last one
    i = s.find(x, i + 1)  # Find the next occurrence of x starting from i+1
    a += [i]  # Store the position

i = n  # Start from the end of string s

# Traverse t in reverse to compute max width
for x in t[:0:-1]:  # Process all characters except the first one in reverse
    i = s.rfind(x, 0, i)  # Find the last occurrence of x before position i
    ans = max(ans, i - a.pop())  # Compare with the width and update max width

print(ans)  # Output the result


# https://github.com/VaHiX/CodeForces/