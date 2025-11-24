# Problem: CF 1492 D - Genius's Gambit
# https://codeforces.com/contest/1492/problem/D

"""
Algorithm: Genius's Gambit
Purpose: Given a number of zeros (a), ones (b), and desired ones in difference (k),
         find two binary numbers x and y with a zeros and b ones such that x - y has exactly k ones.
         
Approach:
1. Special case k=0: Both x and y are identical (all ones followed by all zeros).
2. If k > a + b - 1, impossible due to constraints.
3. Handle edge cases where a=0 or b=0.
4. Construct x and y greedily:
   - x has a 1 at position k (to minimize subtraction effect).
   - y has a 1 at position 0.
   - Then allocate remaining bits to satisfy a and b constraints.
   - Adjust to ensure x >= y and constraints met.

Time Complexity: O(a + b) - single pass through the bit positions
Space Complexity: O(a + b) - arrays to store the bit representations of x and y
"""
for _ in range(1):
    a, b, k = map(int, input().split())
    if k == 0:
        print("Yes")
        n = "1" * b + "0" * a
        print(n)
        print(n)
        continue
    if (a + b - 2) <= (k - 1):
        print("No")
        continue
    if a == 0 or b == 0:
        print("No")
        continue
    n, m = [0] * (a + b), [0] * (a + b)
    n[k] = 1
    m[0] = 1
    ca, cb = a, b
    a -= 1
    b -= 1
    for i in range(1, k):
        if a > 0:
            a -= 1
        else:
            b -= 1
            n[i] = 1
            m[i] = 1
    if k < (ca + cb - 1):
        if b == 0:
            print("NO")
            continue
        n[ca + cb - 1] = 1
        m[ca + cb - 1] = 1
        for i in range(k + 1, ca + cb - 1):
            if a > 0:
                a -= 1
            else:
                b -= 1
                n[i] = 1
                m[i] = 1
    print("Yes")
    for i in n[-1::-1]:
        print(i, end="")
    print()
    for i in m[-1::-1]:
        print(i, end="")
    print()


# https://github.com/VaHiX/CodeForces/