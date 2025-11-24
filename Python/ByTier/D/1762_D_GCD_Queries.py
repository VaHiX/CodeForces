# Problem: CF 1762 D - GCD Queries 
# https://codeforces.com/contest/1762/problem/D

"""
Algorithm: Find indices x and y such that p_x = 0 or p_y = 0
Technique: Binary search-like reduction with GCD queries
Time Complexity: O(n log n) - Each iteration reduces the list size by ~1/3, and we do O(log n) iterations.
Space Complexity: O(n) - Storing the list of indices.

Approach:
1. Start with a list of all indices [1, 2, ..., n].
2. In each iteration:
   - Pick three indices a, b, c from the list.
   - Query gcd(p_a, p_b) and gcd(p_a, p_c).
   - If gcd(p_a, p_b) == gcd(p_a, p_c), it indicates that p_a is likely not 0, so remove it.
   - Else, we can deduce which of p_b or p_c is likely 0, so remove the other one.
3. Continue until only 2 indices remain.
4. Output these two indices as the answer.

This works because:
- If p_a = 0, then gcd(0, p_b) = p_b and gcd(0, p_c) = p_c.
- If p_b = 0, then gcd(p_a, 0) = p_a.
- So, by comparing gcd(p_a, p_b) and gcd(p_a, p_c), we can distinguish cases.
"""

def get(a, b):
    print("?", a, b)
    return int(input())


for _ in range(int(input())):
    n = int(input())
    vls = list(range(1, n + 1))
    while len(vls) > 2:
        a = vls[0]
        b = vls[1]
        c = vls[2]
        u = get(a, b)
        v = get(a, c)
        if u == v:
            # If gcd(p_a, p_b) == gcd(p_a, p_c), then it's likely that p_a is not zero,
            # which means p_b and p_c aren't zero either, so remove p_a.
            del vls[0]
        elif u > v:
            # If gcd(p_a, p_b) > gcd(p_a, p_c), then it's very likely that p_c = 0.
            del vls[2]
        else:
            # If gcd(p_a, p_b) < gcd(p_a, p_c), then it's very likely that p_b = 0.
            del vls[1]
    print("! ", end="")
    print(*vls)
    n = input()


# https://github.com/VaHiX/CodeForces/