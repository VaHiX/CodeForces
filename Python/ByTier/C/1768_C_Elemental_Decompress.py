# Problem: CF 1768 C - Elemental Decompress
# https://codeforces.com/contest/1768/problem/C

"""
Algorithm: Elemental Decompress
Purpose: Given an array a of n integers, find two permutations p and q such that max(p[i], q[i]) = a[i] for all i.
Approach:
- Use a greedy method to assign values to p and q.
- For each value from n down to 1:
  - If the value appears exactly twice, assign it to one element in p and another in q.
  - If the value appears once, assign it to both p and q at that position.
  - If the value appears more than twice, we may not be able to form valid permutations.
Time Complexity: O(n)
Space Complexity: O(n)
"""

for _ in range(int(input())):
    ok = True
    n = int(input())
    a = list(map(int, input().split()))
    p = [0] * n
    q = [0] * n
    pos = [[] for i in range(n + 1)]  # Store indices where each value appears
    for i in range(n):
        pos[a[i]].append(i)
    rp, rq = [], []  # Stacks for positions that need to be filled
    for i in range(n, 0, -1):
        if len(pos[i]) == 2:
            # Assign the same value to two different positions in p and q
            p[pos[i][0]] = i
            q[pos[i][1]] = i
            rq.append(pos[i][0])  # Store positions for later reuse
            rp.append(pos[i][1])
            continue
        if len(pos[i]) == 1:
            # Assign the same value to both p and q at the same position
            p[pos[i][0]] = i
            q[pos[i][0]] = i
            continue
        # If len(pos[i]) > 2 or no valid assignment, try to assign from stacks
        if len(rq) > 0 and len(rp) > 0:
            p[rp.pop()] = i
            q[rq.pop()] = i
        else:
            ok = False  # Impossible to construct permutations
    if ok:
        print("YES")
        print(*p)
        print(*q)
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/