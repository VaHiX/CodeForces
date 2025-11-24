# Problem: CF 1299 A - Anu Has a Function
# https://codeforces.com/contest/1299/problem/A

"""
Algorithm: Reordering Array for Maximum Function Value
Techniques: Bit manipulation, prefix and suffix arrays

Time Complexity: O(n)
Space Complexity: O(n)

The problem involves maximizing the value of a nested function f(x, y) = (x | y) - y,
where | is bitwise OR. The key insight is to understand how the function behaves
and to strategically place elements to maximize the final result.

Approach:
1. Use prefix and suffix AND arrays to track the effect of operations.
2. Try placing each element at the beginning and compute the resulting value.
3. Choose the best placement to maximize the overall function value.

This solution uses bit manipulation and greedy selection to find the optimal arrangement.
"""

n = int(input())
x = [int(x) for x in input().strip().split()]
if n == 1:
    print(x[0])
    exit(0)

# Initialize prefix and suffix arrays with inverted values to handle operations
pref_and = [0] * n
suff_and = [0] * n
for i in range(0, n):
    pref_and[i] = -x[i] - 1  # Invert bits to handle AND operation effectively
    suff_and[i] = -x[i] - 1  # Invert bits to handle AND operation effectively

# Build prefix AND array
for i in range(1, len(x)):
    pref_and[i] = pref_and[i] & pref_and[i - 1]

# Build suffix AND array
for i in range(1, len(x)):
    suff_and[len(x) - i - 1] = suff_and[len(x) - i - 1] & suff_and[len(x) - i]

# Calculate initial maximum value when placing first element at the start
maxim, best = suff_and[1] & x[0], 0

# Check if placing last element at the start gives better result
if pref_and[n - 2] & x[n - 1] > maxim:
    maxim = pref_and[n - 2] & x[n - 1]
    best = n - 1

# Try all other positions for the best placement
for i in range(1, len(x) - 1):
    # Calculate the value of placing element at index i at the beginning
    if pref_and[i - 1] & suff_and[i + 1] & x[i] > maxim:
        maxim = pref_and[i - 1] & suff_and[i + 1] & x[i]
        best = i

# Swap the best element to the first position
x[0], x[best] = x[best], x[0]

# Output the result
ans = " ".join(str(i) for i in x)
print(ans)


# https://github.com/VaHiX/CodeForces/