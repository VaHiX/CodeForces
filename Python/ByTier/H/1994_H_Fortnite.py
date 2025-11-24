# Problem: CF 1994 H - Fortnite
# https://codeforces.com/contest/1994/problem/H

"""
Algorithm/Techniques: 
- This problem uses a system of equations derived from polynomial hash values to determine the base (p) and modulus (m).
- It leverages the fact that with only 3 queries, we can deduce properties about p and m by analyzing patterns in hash outputs.
- The key insight is to use known strings like 'aa' and 'zzzzz...' to extract information about p and m.
- Time Complexity: O(log m) due to modular arithmetic and iterations up to the size of m.
- Space Complexity: O(1) as only a fixed-size vector is used.

Main Idea:
- The code exploits how hash values change with specific string patterns to reverse-engineer p and m.
- First query uses 'aa' to find p.
- Second uses long 'z' sequence to determine part of m.
- Third query uses derived values to get final m.
"""

for _ in range(int(input())):
    print("? aa")
    p = int(input()) - 1  # Subtracting 1 is part of deriving p from hash of 'aa'
    print("? zzzzzzzzzz")  # Use a long string of 'z' to get a hash that helps compute m
    hsh = int(input()) + 1  # Adding 1 is correction for computing hsh properly
    hsho = hsh - 1
    nom = 0
    cnt = 1
    v = [0] * 10
    for i in range(10):  # 10 iterations suffice to compute v[i] values
        nom += 26 * cnt  # Accumulate sum for later
        cnt *= p
        v[i] = 26 - (hsh % p)  # Derive one digit of the base-p representation
        hsh //= p
    s = ""
    cnt = 1
    ch = 0
    for i in range(10):  # Reverse-engineer the string s that gives correct hash
        if v[i] < 1:  # Handle carry-over
            v[i] = 26
            v[i + 1] -= 1
        ch += cnt * v[i]
        cnt *= p
        s += chr(ord("a") + v[i] - 1)  # Construct character string
    print("? " + s)
    ans = int(input())
    print("! " + str(p) + " " + str(ans + nom - ch - hsho))  # Final answer combining all deductions


# https://github.com/VaHiX/CodeForces/