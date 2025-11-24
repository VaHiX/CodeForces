# Problem: CF 1808 E1 - Minibuses on Venus (easy version)
# https://codeforces.com/contest/1808/problem/E1

"""
Purpose: 
    This code calculates the number of "lucky" tickets on Venus, where a ticket is lucky if 
    one of its digits equals the sum of the remaining digits modulo k (the base of the numeral system).
    
Algorithms/Techniques:
    - Dynamic Programming with modular arithmetic
    - Mathematical manipulation using generating functions and inclusion-exclusion
    - Modular exponentiation and modular inverse
    
Time Complexity: O(k^2 * log(m)) due to modular inverse and iteration over k values
Space Complexity: O(1) as only a few variables are used
"""

def f(total, r, k):
    # Calculate a helper function using modular arithmetic
    # This involves modular exponentiation and modular inverse
    ans = ((pow(k - 1, n, m) - (-1) ** n) * pow(k, -1, m)) % m
    # Check if a specific condition is met and adjust result
    if (r * n - total) % k == 0:
        ans += (-1) ** n
    return ans


n, k, m = map(int, input().split())
ans = 0

# If k is odd, iterate through all digits from 0 to k-1
if k % 2 == 1:
    for i in range(k):
        # For each digit, compute contribution to the total lucky tickets
        ans += pow(k, n - 1, m) - f(2 * i, i, k)
    print(ans % m)
else:
    # If k is even, iterate through half the digits
    for i in range(k // 2):
        # For even k, compute a modified contribution
        ans += pow(k, n - 1, m) - f(2 * i, i, k // 2) * pow(2, n - 1, m)
    print(ans % m)


# https://github.com/VaHiX/CodeForces/