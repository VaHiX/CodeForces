# Problem: CF 1735 E - House Planning
# https://codeforces.com/contest/1735/problem/E

"""
Algorithm: 
This solution attempts to reconstruct the positions of houses and two planned houses based on two arrays of distances.
It uses a greedy approach with preprocessing and sorting to match distances from two points to the houses.
The core idea is to determine a distance d such that two distances x from first array and y from second array satisfy x + y = d.

Time Complexity: O(n^2 * log(n)) due to sorting, nested loops, and hashmap operations.
Space Complexity: O(n) for storing input arrays and hashmaps.
"""

from collections import defaultdict
from sys import stdin

input = lambda: stdin.readline()[:-1]


def calc(c, d, n):
    # Pair up distances from both arrays such that their sum equals d
    pair = []
    rem1 = defaultdict(int)
    rem2 = defaultdict(int)
    
    # Process elements in descending order of distances
    for t, x in c:
        if t == 1:
            # If x + d exists in rem2, we can form a valid pair
            if rem2[x + d] > 0:
                pair.append((x, x + d))
                rem2[x + d] -= 1
            else:
                rem1[x] += 1
        else:
            # If x + d exists in rem1, we can form a valid pair
            if rem1[x + d] > 0:
                pair.append((x + d, x))
                rem1[x + d] -= 1
            else:
                rem2[x] += 1

    # Match remaining elements
    for i in rem1:
        if rem1[i] > 0:
            if rem1[i] == rem2[d - i]:
                for _ in range(rem1[i]):
                    pair.append((i, d - i))
            else:
                return -1

    # Check if all n pairs were formed
    if len(pair) != n:
        return -1
    else:
        return pair


def ANS(d, ans):
    # Adjust coordinates to make them non-negative, then print result
    X = []
    for x, y in ans:
        if x + y == d:
            X.append(x)
        elif x < y:
            X.append(-x)
        else:
            X.append(x)
    mn = min(min(X), 0)
    print("YES")
    print(*[i - mn for i in X])
    print(*[0 - mn, d - mn])
    return


def solve():
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    
    # Create a combined list of (type, distance) pairs
    c = []
    for i in range(n):
        c.append((1, a[i]))
        c.append((2, b[i]))
        
    # Sort in descending order of distances to process larger values first
    c.sort(key=lambda x: -x[1])
    
    # Try different values of d (sum of distances to form pairs)
    for i in range(n):
        d = a[0] + b[i]
        ans = calc(c, d, n)
        if ans != -1:
            ANS(d, ans)
            return
            
        d = abs(a[0] - b[i])
        ans = calc(c, d, n)
        if ans != -1:
            ANS(d, ans)
            return
    print("NO")


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/