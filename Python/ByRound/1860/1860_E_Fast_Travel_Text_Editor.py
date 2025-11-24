# Problem: CF 1860 E - Fast Travel Text Editor
# https://codeforces.com/contest/1860/problem/E

"""
Algorithm: Single Source Shortest Path with Preprocessing
Time Complexity: O(n^2 + mn) where n is length of string and m is number of queries
Space Complexity: O(n^2 + n + m) for preprocessing and query storage

This solution uses a BFS approach to precompute shortest distances between all positions
and special nodes representing pairs of adjacent characters. The key insight is that
the third operation allows jumping between positions with matching adjacent character pairs.
"""
def I():
    return input().strip()
def II():
    return int(I())
def GMI():
    return map(lambda x: int(x) - 1, I().split())

def main():
    s = I()
    n = len(s)
    # Create a value for each pair of adjacent characters (encoded as 26*x + y)
    value = [ord(s[i + 1]) % 26 * 26 + ord(s[i]) % 26 for i in range(n - 1)]

    q = II()
    ls = []
    rs = []
    ans = []
    for _ in range(q):
        l, r = GMI()  # Convert to 0-indexed
        ls.append(l)
        rs.append(r)
        ans.append(abs(r - l) * 2)  # Initial distance (without using third operation)

    tot = 26 * 26  # Total possible character pairs
    pos = [[] for _ in range(tot)]  # Store positions for each character pair
    for i in range(n - 1):
        pos[value[i]].append(i)

    # BFS to compute distances from each "special" node
    dq = [0] * (n + tot)
    for i in range(26 * 26):
        if len(pos[i]) == 0:
            continue
        dist = [-1] * (n + tot)
        l, r = 0, 1
        dq[l] = n + i  # Special node representing character pair i
        dist[n + i] = 0
        while l < r:
            u = dq[l]
            l += 1
            if u < n:  # Regular position
                # Move to the special node representing adjacent characters at position u
                if dist[n + value[u]] == -1:
                    dist[n + value[u]] = dist[u] + 1
                    l -= 1  # Insert at beginning (BFS)
                    dq[l] = n + value[u]
                # Move left
                if u and dist[u - 1] == -1:
                    dist[u - 1] = dist[u] + 2
                    dq[r] = u - 1
                    r += 1
                # Move right
                if u + 1 < n - 1 and dist[u + 1] == -1:
                    dist[u + 1] = dist[u] + 2
                    dq[r] = u + 1
                    r += 1
            else:  # Special node
                # Move to positions with matching character pairs
                for v in pos[u - n]:
                    if dist[v] == -1:
                        dist[v] = dist[u] + 1
                        dq[r] = v
                        r += 1
        for i in range(q):
            if dist[ls[i]] + dist[rs[i]] < ans[i]:
                ans[i] = dist[ls[i]] + dist[rs[i]]
    print("\n".join(str(x // 2) for x in ans))
    return


t = 1
for _ in range(t):
    main()


# https://github.com/VaHiX/CodeForces/