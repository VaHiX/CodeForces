# Problem: CF 1728 C - Digital Logarithm
# https://codeforces.com/contest/1728/problem/C

"""
Purpose: 
This code solves the problem of making two arrays similar by applying digital logarithm operations. 
The digital logarithm f(x) is defined as the number of digits in x (i.e., length of base-10 representation).
In each operation, we can either replace a[i] with f(a[i]) or f(b[i]) for some index i.
We aim to find the minimum number of such operations to make the two arrays similar (i.e., have the same multiset of elements after rearrangement).

Key Algorithm:
1. Count frequencies of each number in both arrays.
2. Compute difference in counts between arrays.
3. For numbers with more than one digit, we can potentially convert them to their digital logarithm (number of digits).
4. The operations required is the sum of absolute differences of counts, considering conversions where possible.

Time Complexity: O(n), where n is the size of arrays. Each element is processed once, and operations on Counter are efficient.
Space Complexity: O(n), due to storing counters and keys.
"""

from collections import Counter

for _ in range(int(input())):
    n = int(input())
    a = Counter(input().split())  # Count frequencies of elements in array a
    b = Counter(input().split())  # Count frequencies of elements in array b
    a.subtract(b)  # Subtract b's counts from a's; positive values mean excess in a, negative in b
    keys = list(a.keys())
    ans = 0
    num1 = 0
    for k in keys:
        if len(k) > 1:  # If current number has more than one digit
            a[str(len(k))] += a[k]  # Transfer count to its digital logarithm
            ans += abs(a[k])  # Add operations needed for this conversion
            a[k] = 0  # Clear the original key
    for k in a:
        if k != "1":  # For all keys except 1 (since f(1) = 1)
            ans += abs(a[k])  # Add the remaining differences
    print(ans)


# https://github.com/VaHiX/CodeForces/