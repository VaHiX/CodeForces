# Problem: CF 1877 D - Effects of Anti Pimples
# https://codeforces.com/contest/1877/problem/D

"""
Code Purpose:
This code computes the sum of maximum values over all possible subsets of indices
chosen to be "black", where:
- Initially, all elements are white.
- Black elements are chosen from indices.
- Green elements are all white elements whose indices are multiples of at least one black index.
- Score is the maximum value among all black and green elements.
- We sum up scores for all 2^n - 1 possible choices of black indices.

Algorithm:
- For each index i, we compute the maximum value in the range [i, n] with step i (i.e., multiples of i).
- This is done by iterating from 1 to n and updating a[i] with max of a[i] and a[j] where j is a multiple of i.
- Then, we sort these values and compute the result using a weighted sum with powers of 2 (since each number can either be chosen or not in a subset).

Time Complexity: O(n log n) 
Space Complexity: O(n)

Techniques:
- Preprocessing to compute max values for multiples using sieve-like approach.
- Sorting and weighted sum using powers of 2.
"""

n = int(input())
a = [0] + [*map(int, input().split())]  # Add dummy 0 at start for 1-based indexing
mod = 998244353

# For each index i, propagate the max value to all its multiples
# This ensures a[i] holds the maximum value among all indices that are multiples of i
for i in range(1, n + 1):
    for j in range(i, n + 1, i):  # Iterate through all multiples of i
        a[i] = max(a[i], a[j])   # Update a[i] to be max between current and multiple

ans = 0
cnt = 1  # Count of subsets that include current element (starts with 1)

# Sort the processed values in ascending order for correct contribution calculation
for x in sorted(a[1:]):  # Iterate over elements from index 1 onwards
    ans = (ans + x * cnt) % mod  # Add contribution of current element
    cnt = (cnt * 2) % mod        # Double the count for next iteration (2^k subsets)

print(ans)


# https://github.com/VaHiX/CodeForces/