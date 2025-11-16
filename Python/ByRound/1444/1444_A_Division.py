# Problem: CF 1444 A - Division
# https://codeforces.com/contest/1444/problem/A

"""
Algorithm: Find the largest divisor x of p such that x is not divisible by q.
Approach:
- First, we find all the prime factors of q.
- Then for each prime factor of q, we remove that factor from p repeatedly until it's no longer divisible by q.
- We track the maximum value of p after such removals.
- Time Complexity: O(sqrt(q) + log(p)) per test case
- Space Complexity: O(log(q)) for storing prime factors
"""

t = int(input())
for _ in range(t):
    p, q = list(map(int, input().split()))
    t_factors = []  # List to store prime factors of q
    ans = 1
    i = 2
    n = q
    # Factorize q into its prime factors
    while i * i <= n:
        if n % i == 0:
            t_factors.append(i)
            n //= i
        else:
            i += 1
    t_factors.append(n)  # Add the last prime factor if greater than sqrt(q)
    
    # Convert to set to get unique prime factors
    t_factors = set(t_factors)
    
    # For each unique prime factor of q, compute potential x values
    for factor in t_factors:
        k = p
        # Remove all instances of this factor from p as long as p is divisible by q
        while k % q == 0:
            k //= factor
        ans = max(ans, k)
    
    print(ans)


# https://github.com/VaHiX/CodeForces/