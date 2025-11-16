# Problem: CF 1847 D - Professor Higashikata
# https://codeforces.com/contest/1847/problem/D

"""
Code Purpose:
This solution addresses a problem where we maintain a binary string and process queries to flip bits.
The goal is to calculate the minimal number of swaps needed to make the concatenated substrings lexicographically maximal after each bit flip query.

Algorithms/Techniques:
- Union-Find (Disjoint Set Union) with path compression for grouping indices into segments.
- Efficient tracking of how many 1s are in the first part of the concatenated substring to determine minimum swaps needed.

Time Complexity: O(n + m + q * α(n)) where α(n) is the inverse Ackermann function (nearly constant).
Space Complexity: O(n)

"""

from sys import stdin

input = lambda: stdin.readline().rstrip("\r\n")


def inputia():
    return list(map(int, input().split()))


def inputInt():
    return int(input())


for test in range(1):
    n, m, q = inputia()

    s = input()
    # nxt array used for union-find structure to group indices
    nxt = [-1] * (n + 1)

    # Find function with path compression for Union-Find
    def find(u):
        path = []
        while nxt[u] != -1 and nxt[u] != u:
            path.append(u)
            u = nxt[u]
        for i in path:
            nxt[i] = u
        return u

    # ptra[i] stores the position of index i in the sorted array ra
    ptra = [-1] * n
    # ra stores the indices in order they appear in sorted segments
    ra = []
    
    # Process all segments [l, r] to group overlapping intervals
    for _ in range(m):
        l, r = inputia()
        l -= 1  # Convert to 0-based index
        r -= 1
        u = find(l)
        while u <= r:
            ptra[u] = len(ra)
            ra.append(u)
            nxt[u] = u + 1
            u = find(u)

    mx_rank = len(ra)  # Maximum number of sorted indices

    # Convert string to integer array (1 for '1', 0 for '0')
    arr = [1 if c == "1" else 0 for c in s]

    cnt = sum(arr)  # Count of 1s in current string
    # Calculate initial answer: number of 0s among first cnt positions in sorted segment
    ans = sum([arr[ra[i]] ^ 1 for i in range(min(cnt, mx_rank))])
    
    # Process each query
    for _ in range(q):
        i = inputInt() - 1  # Convert to 0-based index

        # Update answer if index i contributes to difference in first cnt elements
        if ptra[i] != -1 and ptra[i] < cnt:
            ans += 1 if arr[i] else -1
                
        if arr[i] == 0:
            arr[i] = 1
            cnt += 1
            # If this new 1 is within the first cnt positions, update answer accordingly
            if cnt <= mx_rank and arr[ra[cnt - 1]] == 0:
                ans += 1
        else:
            arr[i] = 0
            # Decrement count and adjust answer if the last element in first cnt positions was 0
            if cnt > 0 and cnt <= mx_rank and arr[ra[cnt - 1]] == 0:
                ans -= 1
            cnt -= 1
                
        print(ans)


# https://github.com/VaHiX/CodeForces/