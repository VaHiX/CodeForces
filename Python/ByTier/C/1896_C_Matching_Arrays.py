# Problem: CF 1896 C - Matching Arrays
# https://codeforces.com/contest/1896/problem/C

"""
Algorithm: Matching Arrays
Techniques: Sorting, Greedy, Hash Map

Time Complexity: O(n log n) due to sorting operations
Space Complexity: O(n) for storing sorted arrays and hash map

The problem involves determining if we can rearrange array b such that exactly x positions
have a[i] > b[i]. The approach uses sorting and a greedy strategy:
1. Sort both arrays
2. Check if it's possible to achieve exactly x positions where a[i] > b[i]
3. Use a hash map to assign b elements to a elements in a way that satisfies the condition
"""

import sys

input = sys.stdin.readline
t = int(input())
result = []
for _ in range(t):
    n, x = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    c = sorted(a)  # Sorted version of array a
    d = sorted(b)  # Sorted version of array b
    ans = True
    # Check if it's possible to have exactly x elements where a[i] > b[i]
    for i in range(0, n - x):
        if c[i] > d[x + i]:  # If a[i] > b[i] is required but a[i] <= b[i], impossible
            ans = False
            break
    # For the remaining elements, check the opposite condition
    for i in range(n - x, n):
        if c[i] <= d[i - n + x]:  # If a[i] <= b[i] but we want a[i] > b[i], impossible
            ans = False
            break
    if not ans:
        result.append("NO")
        continue
    else:
        result.append("YES")
        my_dict = {}  # Dictionary to map each element of a to elements of b
        for i in range(n):
            if i < n - x:  # Assign smaller elements of b to smaller elements of a
                if c[i] in my_dict.keys():
                    my_dict[c[i]].append(d[x + i])
                else:
                    my_dict[c[i]] = [d[x + i]]
            else:  # Assign larger elements of b to larger elements of a
                if c[i] in my_dict.keys():
                    my_dict[c[i]].append(d[i - n + x])
                else:
                    my_dict[c[i]] = [d[i - n + x]]
        ll = []
        # Build result by mapping each element in original array a to assigned elements in b
        for i in a:
            ll.append(str(my_dict[i][-1]))
            my_dict[i].pop()
        result.append(" ".join(ll))


sys.stdout.write("\n".join(result))


# https://github.com/VaHiX/CodeForces/