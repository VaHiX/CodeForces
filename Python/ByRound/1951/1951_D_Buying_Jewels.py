# Problem: CF 1951 D - Buying Jewels
# https://codeforces.com/contest/1951/problem/D

"""
Code Purpose:
This code determines whether Bob can set up at most 60 stalls with integer prices between 1 and 10^18 such that Alice buys exactly k jewels using n coins. 
Alice buys greedily: she fills each stall completely before moving to the next.

Algorithms/Techniques:
- Greedy approach simulation
- Mathematical trick: If n >= 2*k - 1, we can use 2 stalls with prices (n - k + 1) and 1.
- Special case when n == k: 1 stall with price 1.
- For other cases, it's impossible to achieve exact k jewels under constraints.

Time Complexity:
O(1) - The algorithm performs constant-time calculations per test case.

Space Complexity:
O(1) - Only a constant amount of extra space used, not counting the output storage.
"""

def fg():
    return int(input())


def fgf():
    return [int(x) for x in input().split()]


out = []
for _ in range(fg()):
    n, k = map(int, input().split())
    if n < k:
        out.append("NO")
        continue
    if n >= 2 * k - 1:
        out.append("YES")
        out.append(2)
        out.append(f"{n -k +1 } 1")
        continue

    if n == k:
        out.append("YES")
        out.append(1)
        out.append("1")
        continue
    out.append("NO")

print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/