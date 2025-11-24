# Problem: CF 2164 F1 - Chain Prefix Rank (Easy Version)
# https://codeforces.com/contest/2164/problem/F1

"""
Algorithm: Dynamic Programming on Tree with Combinatorics
Time Complexity: O(n^2)
Space Complexity: O(n^2)

This problem involves counting valid permutations of a tree where each node u must have exactly a[u] ancestors 
with smaller values in the permutation. The solution uses a post-order DFS traversal of the tree, maintaining 
a count of how many valid permutations exist for each subtree at each possible "rank" level.

The approach:
1. Build the tree from parent information
2. Perform post-order DFS to process children before parent
3. For each node, maintain an array where anses[node][i] represents number of ways to assign values 
   such that the rank (relative position) of the value assigned is exactly i.
4. Use combinatorics to combine results from children: multinomial coefficients
5. For each node, compute how many valid ways there are to assign it based on its constraints a[node]

Key techniques:
- Post-order DFS for tree traversal
- Dynamic programming with multinomial coefficients
- Modular arithmetic with modular inverse calculation
"""

def alge(a, b):
    if b == 0:
        return 1, 0
    if a < b:
        c, d = alge(b, a)
        return d, c
    if a % b == 0:
        return 1, -(a // b - 1)
    c, d = alge(b, a % b)
    return d, c - a // b * d


def deli(a, b):
    c, d = alge(b, 998244353)
    return c * a % 998244353


fact = [1]
act = 1
for i in range(1, 5002):
    act *= i
    act %= 998244353
    fact.append(act)

for test in range(int(input())):
    n = int(input())
    ans = 1

    p = list(map(int, input().split()))
    for i in range(n - 1):
        p[i] -= 1
    a = list(map(int, input().split()))
    tree = [[] for _ in range(n)]
    for i in range(n - 1):
        tree[p[i]].append(i + 1)
    stack = [[0, 0, 0]]
    anses = [0] * n
    while True:
        if len(stack) == 0:
            break
        el = stack.pop()
        if el[1] == 0:
            stack.append([el[0], 1, el[2]])
            for x in tree[el[0]]:
                stack.append([x, 0, el[2] + 1])
        else:
            mas = [0] * (el[2] + 1)
            for i in range(el[2] + 2):
                kol = 0
                for j in tree[el[0]]:
                    kol += anses[j][i]
                if i <= a[el[0]]:
                    mas[i] += kol
                else:
                    mas[i - 1] += kol
                if kol > 1:
                    for j in tree[el[0]]:
                        ans *= deli(
                            fact[kol], fact[anses[j][i]] * fact[kol - anses[j][i]]
                        )
                        ans %= 998244353
                        kol -= anses[j][i]
            mas[a[el[0]]] += 1
            anses[el[0]] = mas.copy()

    print(ans % 998244353)


# https://github.com/VaHiX/CodeForces/