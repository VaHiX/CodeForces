# Problem: CF 1268 A - Long Beautiful Integer
# https://codeforces.com/contest/1268/problem/A

"""
Problem: Long Beautiful Integer

Given an integer x with n digits and a positive integer k < n, find the smallest beautiful integer y such that y >= x.
A beautiful integer has a repeating pattern of length k; that is, b_i = b_{i+k} for all valid i.

Approach:
1. Check if the input already forms a beautiful number; if so, output it directly.
2. If not, try to construct the smallest beautiful number >= x by:
   - Comparing x with a candidate made from repeating the prefix of length k.
   - Else, try to increment the prefix and apply it cyclically.
3. Handle special case where all digits are 9.

Time Complexity: O(n)
Space Complexity: O(n)

Algorithms/Techniques:
- Cyclic pattern matching
- Greedy construction
- String manipulation
"""

n, k = map(int, input().split())
a = input()
ind = -1

# Check if the input is already beautiful (repeating every k digits)
if all(a[i] == a[i + k] for i in range(n - k)):
    print(n)
    print(a)
# If the cyclic repeat of first k digits is greater than or equal to a
elif a[:k] * (n // k) + a[:k][: n % k] >= a:
    print(n)
    print(a[:k] * (n // k) + a[:k][: n % k])
else:
    # Initialize mx array to track maximum digit in each position mod k
    mx = ["0"] * k
    for i in range(n):
        mx[i % k] = max(mx[i % k], a[i])

    # Find first position where we can increment the digit to avoid all 9s
    for i in range(k):
        if a[i] != "9":
            ind = i
    # If all digits are 9, return all 9s with same length
    if ind == -1:
        print(n)
        print("9" * n)
    else:
        # Increment the digit at ind and fill rest with zeros
        print(n)
        t = a[:ind] + str(int(a[ind]) + 1) + "0" * (k - ind - 1)
        print(t * (n // k) + t[: n % k])


# https://github.com/VaHiX/codeForces/