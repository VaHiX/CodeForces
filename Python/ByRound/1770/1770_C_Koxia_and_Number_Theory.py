# Problem: CF 1770 C - Koxia and Number Theory
# https://codeforces.com/contest/1770/problem/C

"""
Algorithm: Number Theory & Pigeonhole Principle
Techniques: 
- Precomputed primes checking modulo classes
- Pigeonhole principle to detect conflict

Time Complexity: O(n * k) where k is the number of precomputed primes (15)
Space Complexity: O(k) for the prime list and count array

This solution leverages the fact that if we can find a value x such that all pairs (a[i]+x, a[j]+x) are coprime,
then we can also check that for each prime p, there are at most one element in each residue class modulo p.
If any prime p has at least two elements in the same residue class, then no valid x exists.
"""

P = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47]

for s in [*open(0)][2::2]:
    a = [*map(int, s.split())]
    # Check for duplicates in the array
    if len(a) != len({*a}):
        print("NO")
        continue
    # For each precomputed prime p
    for p in P:
        cnt = [0] * p
        # Count occurrences of each residue class modulo p
        for x in a:
            cnt[x % p] += 1
        # If any residue class has at least 2 elements, conflict exists
        if min(cnt) >= 2:
            print("NO")
            break
    else:
        # If no conflict found for all primes, yes
        print("YES")


# https://github.com/VaHiX/CodeForces/