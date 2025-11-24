# Problem: CF 1731 C - Even Subarrays
# https://codeforces.com/contest/1731/problem/C

"""
Problem: Count subarrays whose XOR has an even number of divisors.

Approach:
- Use prefix XOR to compute XOR of any subarray in O(1).
- For each prefix XOR value, we want to know how many previous prefix XORs 
  when XORed with it result in a number with an odd number of divisors.
- A number has an odd number of divisors if and only if it's a perfect square.
- So for each prefix, count how many previous prefixes XOR to a perfect square.
- Subtract this from the total number of subarrays to get count of subarrays 
  with XOR having even number of divisors.

Time Complexity: O(n * sqrt(n)) where n is the size of array.
Space Complexity: O(n) for the prefix array and frequency array.

Algorithms/Techniques:
- Prefix XOR
- Perfect square detection
- Two-pointer / frequency counting approach
"""

for i in range(int(input())):
    n = int(input())
    a = [int(i) for i in input().split()]
    b = [0] * (n + 1)
    # Compute prefix XOR
    for j in range(1, n + 1):
        b[j] = b[j - 1] ^ a[j - 1]
    # Frequency array to store count of each prefix XOR value
    c = [0] * (4 * n + 1)
    # Total number of subarrays
    ans = (n + 1) * n / 2
    for i in range(n + 1):
        j = 0
        # Check all perfect squares up to 2*n (upper bound for XOR of two numbers in [1, n])
        while j * j <= 2 * n:
            ans -= c[b[i] ^ (j * j)]
            j += 1
        c[b[i]] += 1
    print(int(ans))


# https://github.com/VaHiX/CodeForces/