# Problem: CF 2067 D - Object Identification
# https://codeforces.com/contest/2067/problem/D

"""
Problem: Object Identification

This is an interactive problem where we must determine whether the jury has hidden 
Object A (a directed graph) or Object B (points on a coordinate plane) using at most 2 queries.

Algorithms/Techniques:
- Interactive binary guessing using shortest path vs Manhattan distance
- Graph representation via adjacency list (implicit in this case)
- Linear scan with queries to distinguish between graph and point objects

Time Complexity: O(n) per test case, where n is the size of arrays x and y.
Space Complexity: O(n) for storing the input array and auxiliary data structures.

"""

from sys import stdin

input = lambda: stdin.buffer.readline().decode().strip()


def ask(x, y):
    # Make a query to the interactor
    print("?", x, y, flush=True)
    return int(input())


for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    ans = "A"
    
    try:
        # Find positions of 1 and n in the array
        x, y = a.index(1) + 1, a.index(n) + 1
        d = ask(x, y)
        
        # If d >= n - 1, it could indicate a graph with long paths, or if same as reverse query,
        # it suggests a sparse graph structure typical for object A (directed graph)
        if d >= n - 1 and d == ask(y, x):
            ans = "B"
    except:
        # Fallback strategy if we couldn't find 1 and n
        a = set(a)
        for i in range(1, n + 1):
            if i not in a:
                # Query with a missing number to detect Manhattan distance pattern
                if ask(i, i - 1 if i > 1 else i + 1):
                    ans = "B"
                break
    print("!", ans, flush=True)


# https://github.com/VaHiX/codeForces/