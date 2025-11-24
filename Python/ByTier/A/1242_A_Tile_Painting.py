# Problem: CF 1242 A - Tile Painting
# https://codeforces.com/contest/1242/problem/A

"""
Problem: Tile Painting
Algorithm/Technique: Number theory, finding smallest prime factor
Time Complexity: O(sqrt(n)) - for finding the smallest prime factor
Space Complexity: O(1) - only using a few variables

The problem asks to find the maximum number of different colors that can be used 
to paint tiles such that if two tiles at positions i and j satisfy (n % |j-i| == 0) and |j-i| > 1, 
then they must have the same color. This constraint creates a periodic pattern based on divisors of n.
The key insight is that the number of distinct colors equals the smallest prime factor of n,
because tiles are constrained by the periodic structure imposed by the divisors of n.
If n is prime, then all tiles can have different colors (n colors).
"""

n = int(input())
if n == 1:
    print(1)
    exit()
p = n
for d in range(2, min(n + 1, int(n**0.5) + 2)):  # Find smallest prime factor of n
    if n % d == 0:
        p = d
        break
while n % p == 0:  # Remove all factors of p from n
    n //= p
if n != 1:  # If n is not 1 after removing factors, it means n had another prime factor
    print(1)
else:
    print(p)  # Return the smallest prime factor


# https://github.com/VaHiX/codeForces/