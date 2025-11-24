# Problem: CF 2034 E - Permutations Harmony
# https://codeforces.com/contest/2034/problem/E

"""
E. Permutations Harmony

Purpose:
This code solves the problem of constructing a k-harmonic set of permutations for given n and k.
A k-harmonic set of permutations means k distinct permutations of size n such that the sum of elements at each index position is constant across all permutations.

Algorithms/Techniques:
1. Basic mathematical analysis to check impossibility conditions
2. Permutation generation using itertools.permutations
3. Special handling for small n and k values
4. Construction algorithms based on parity of n and k

Time Complexity: O(k * n! * n) in worst case due to permutation generation (can be exponential)
Space Complexity: O(n * k) for storing permutations

"""

from itertools import permutations


def pp(str):
    if debug:
        print("ANSWER:", str)
    else:
        print(str)


def pp_arr(arr):
    if debug:
        print("ANSWER: " + " ".join(list(map(str, arr))))
    else:
        print(" ".join(list(map(str, arr))))


def factorial(n):
    if n == 0:
        return 1
    return n * factorial(n - 1)


def solve():
    n, k = map(int, input().split())
    if n == 1:
        if k == 1:
            pp("YES")
            pp("1")
            return
        else:
            pp("NO")
            return
    if k == 1:
        pp("NO")
        return
    if n <= 10:
        if k > factorial(n):
            pp("NO")
            return
    if k % 2 == 0:  # If k is even
        kk = k // 2
        pp("YES")
        cnt = 0
        for perm in permutations(range(1, n + 1)):  # Generate all permutations
            if cnt == kk:
                return
            pp_arr(perm)
            reflection = [n + 1 - x for x in perm]  # Create reflection permutation
            pp_arr(reflection)
            cnt += 1
    else:  # If k is odd
        if n % 2 == 0:  # Even n with odd k
            pp("NO")
            return
        m = n // 2  # Half of n
        if n < 3:
            pp("NO")
            return
        if n <= 12:
            if k > factorial(n) - 3:
                pp("NO")
                return
        pp("YES")
        perm1 = list(range(1, n + 1))  # Identity permutation
        perm2 = []
        for i in range(m):
            perm2.append(2 * m - 2 * i)
        for i in range(m + 1):
            perm2.append(2 * m + 1 - 2 * i)
        perm3 = []
        for i in range(m + 2, n + 1):
            perm3.append(i)
        for i in range(1, m + 2):
            perm3.append(i)
        pp_arr(perm1)  # Print first permutation
        pp_arr(perm2)  # Print second permutation
        pp_arr(perm3)  # Print third permutation
        num_pairs = (k - 3) // 2  # Number of additional pairs needed
        cnt = 0
        for perm in permutations(range(1, n + 1)):  # Generate remaining permutations
            if cnt == num_pairs:
                return
            reflection = [n + 1 - x for x in perm]  # Create reflection
            if list(perm) == perm1 or list(perm) == perm2 or list(perm) == perm3:
                continue  # Skip already used permutations
            if (
                list(reflection) == perm1
                or list(reflection) == perm2
                or list(reflection) == perm3
            ):
                continue  # Skip reflections of already used permutations
            pp_arr(perm)
            pp_arr(reflection)
            cnt += 1


debug = False
t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/codeForces/