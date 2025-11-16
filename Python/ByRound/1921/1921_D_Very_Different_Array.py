# Problem: CF 1921 D - Very Different Array
# https://codeforces.com/contest/1921/problem/D

"""
Task: Maximize the sum of absolute differences between two arrays.
Approach:
- Sort the first array 'a' in descending order.
- Sort the second array 'b' in ascending order.
- For each element in 'a', we can pair it with either the smallest or the largest remaining element in 'b'.
- To maximize difference, we compute the maximum of two possibilities at each step:
  1. Pair current element of 'a' with the smallest unused element in 'b'
  2. Pair current element of 'a' with the largest unused element in 'b'
- Use two pointers: one from the start (smallest) and one from the end (largest) of sorted 'b'.

Time Complexity: O(n log n + m log m) due to sorting
Space Complexity: O(1) excluding input arrays
"""

def solve():
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    a.sort(reverse=True)  # Sort first array in descending order
    b.sort()              # Sort second array in ascending order
    base = m - n          # Index to split b into two parts
    ans = 0
    for i in range(n):
        # For each element in a, compare with smallest and largest available in b
        ans += max(abs(a[i] - b[i]), abs(a[i] - b[base + i]))
    print(ans)


t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/