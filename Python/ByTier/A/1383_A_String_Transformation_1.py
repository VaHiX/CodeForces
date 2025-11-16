# Problem: CF 1383 A - String Transformation 1
# https://codeforces.com/contest/1383/problem/A

"""
String Transformation 1
Algorithms/Techniques: Graph, Union-Find, Greedy
Time Complexity: O(n + 26^2) = O(n) where n is the length of strings
Space Complexity: O(26) = O(1) for the fixed-size arrays and sets

The algorithm works as follows:
1. For each position, if b[i] < a[i], it's impossible to make them equal (return -1).
2. If b[i] > a[i], we record a dependency: a[i] can be transformed to b[i].
3. We model these dependencies as a graph using sets to track which letters can be transformed into others.
4. Using a greedy approach, for each letter that can be transformed, we merge it with the smallest letter it can transform into.
5. The number of such operations gives us the minimum moves required.

The core idea is to treat each transformation as an edge in a directed graph and find connected components using union-like operations.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    a = input()[:-1]  # Read string A, remove newline
    b = input()[:-1]  # Read string B, remove newline
    q = [set() for i in range(26)]  # For each letter, store which letters it can transform into
    for i in range(n):
        if a[i] > b[i]:  # If a[i] is greater than b[i], transformation impossible
            print(-1)
            break
        elif b[i] > a[i]:  # If b[i] is greater, record transformation from a[i] to b[i]
            q[ord(a[i]) - 97].add(ord(b[i]) - 97)  # Convert char to index (0-25)
    else:
        c = 0  # Count of moves
        i = 0
        while i < 26:  # Process each letter from 'a' to 'z'
            if len(q[i]):  # If this letter has transformations
                x = min(q[i])  # Find the smallest letter it can transform to
                q[i].remove(x)  # Remove that target
                q[x] |= q[i]  # Merge all transformations of current letter into target letter
                c += 1  # Increment move counter
            i += 1
        print(c)


# https://github.com/VaHiX/codeForces/