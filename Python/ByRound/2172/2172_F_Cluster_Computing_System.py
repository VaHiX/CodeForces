# Problem: CF 2172 F - Cluster Computing System
# https://codeforces.com/contest/2172/problem/F

"""
Purpose: To find the minimum total cost to connect all servers in a cluster computing system,
         where the cost of connecting two servers u and v is gcd(p_u, p_u+1, ..., p_v).

Algorithms/Techniques:
- Preprocessing using prefix and suffix GCD arrays
- Greedy selection of minimum cost edges to form a minimum spanning tree

Time Complexity: O(n * log(max_value)) where n is the number of servers and max_value is the maximum protocol type
Space Complexity: O(n) for storing prefix and suffix arrays

The solution uses the idea that for a spanning tree, we can greedily select edges with minimal costs,
and by computing prefix and suffix GCDs, we efficiently determine the minimum cost of connecting segments.
"""

from math import gcd


def main():
    n = int(input())
    a = list(map(int, input().split()))
    pre = list(a)  # Prefix GCD array
    suf = list(a)  # Suffix GCD array
    
    # Build prefix GCD array: pre[i] = gcd(a[0], a[1], ..., a[i])
    for i in range(1, n):
        pre[i] = gcd(pre[i - 1], pre[i])
    
    # Build suffix GCD array: suf[i] = gcd(a[i], a[i+1], ..., a[n-1])
    for i in range(n - 2, -1, -1):
        suf[i] = gcd(suf[i + 1], suf[i])
    
    # Sum up the minimum of prefix and suffix GCDs for each internal point
    ans = 0
    for i in range(1, n):
        ans += min(pre[i], suf[i])
    
    print(ans)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/