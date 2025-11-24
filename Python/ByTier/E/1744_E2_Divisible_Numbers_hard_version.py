# Problem: CF 1744 E2 - Divisible Numbers (hard version)
# https://codeforces.com/contest/1744/problem/E2

from math import sqrt


def f(n):
    # Function to find all divisors of n
    l = []
    for i in range(1, int(sqrt(n)) + 1):
        if n % i == 0 and n // i != i:
            # If i and n//i are different, add both
            l.append(i)
            l.append(n // i)
        elif n % i == 0:
            # If i and n//i are same (perfect square), add only once
            l.append(i)
    return l


for _ in range(int(input())):
    a, b, c, d = [int(i) for i in input().split()]
    # Get all divisors of a and b
    fa, fb = f(a), f(b)
    ans = [-1, -1]
    # Iterate over all pairs of divisors from fa and fb
    for i in fa:
        for j in fb:
            q = i * j  # Product of two divisors
            p = a * b // q  # Calculate the remaining factor needed for divisibility
            x = (c // q) * q  # Find largest multiple of q <= c such that x > a
            y = (d // p) * p  # Find largest multiple of p <= d such that y > b
            if x > a and y > b:  # Check if constraints are satisfied
                ans = [x, y]
                break
        if ans != [-1, -1]:  # If valid pair found, break inner loop
            break
    print(*ans)

# ### Complexity Analysis

# **Time Complexity**:  
# $$ O(\sqrt{a} \cdot \sqrt{b} \cdot \log(\max(a, b))) $$  
# - Finding divisors of $ a $ and $ b $ costs $ O(\sqrt{a} + \sqrt{b}) $.
# - For each pair of these divisors, basic operations take constant time.
# - The maximum number of divisor pairs we check is bounded by $ O(\sqrt{a} \cdot \sqrt{b}) $.

# **Space Complexity**:  
# $$ O(\sqrt{a} + \sqrt{b}) $$  
# - Storing all the divisors of $ a $ and $ b $ uses space proportional to $ \sqrt{a} + \sqrt{b} $.

# https://github.com/VaHiX/CodeForces/