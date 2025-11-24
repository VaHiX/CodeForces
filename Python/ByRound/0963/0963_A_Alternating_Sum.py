# Problem: CF 963 A - Alternating Sum
# https://codeforces.com/contest/963/problem/A

# '''
# Problem: Alternating Sum
# 
# Algorithm:
# This problem requires computing a sum of the form:
# sum_{i=0}^{n} s_i * a^{n-i} * b^i
# where s_i is a k-periodic sequence of +1 and -1.
# 
# Key Observations:
# 1. The sequence s is k-periodic, so we only need to store the first k elements.
# 2. The terms of the sum can be rewritten as:
#    a^n * (s_0 * (b/a)^0 + s_1 * (b/a)^1 + ... + s_{k-1} * (b/a)^{k-1})
#    where (b/a) is used in geometric progression.
# 
# Approach:
# - Compute the contribution of one full period of the sequence.
# - Use geometric progression sum formula to compute total sum efficiently.
# - Modular arithmetic is used throughout to avoid overflow.
# 
# Time Complexity: O(k + log(n)) due to power computations and one loop over k elements.
# Space Complexity: O(k) for storing the sequence.
# '''

M = 10**9 + 9
n, a, b, k = [int(e) for e in input().split()]
seq = [1 if e == "+" else -1 for e in input()]
s = 0
x = pow(a, n, M) # Precompute a^n mod M
y = (pow(a, -1, M) * b) % M # Compute (b/a) mod M
for i in range(k):
    s += x * seq[i] # Add contribution of current term
    x *= y # Multiply by (b/a) for next term in the sum
    s %= M # Keep s in mod
    x %= M # Keep x in mod
q = pow(y, k, M) # Compute (b/a)^k mod M
S = s * ((n + 1) // k) # Total number of full periods
if q != 1:
    # Apply geometric series formula for sum of a^k + a^{2k} + ... + a^{(n+1)/k * k}
    # which is a^k * (1 - a^{(n+1)/k * k}) / (1 - a^k)
    S = s * (pow(q, (n + 1) // k, M) - 1) * pow(q - 1, -1, M) # Apply geometric progression sum
print(S % M)


# https://github.com/VaHiX/CodeForces/