# Problem: CF 1867 E1 - Salyg1n and Array (simple version)
# https://codeforces.com/contest/1867/problem/E1

"""
Algorithm: Interactive XOR Array Reconstruction
Techniques: Query-based manipulation, XOR properties, prefix-xor optimization

Time Complexity: O(n/k * k) = O(n), where n is the size of the array
Space Complexity: O(1), only using a few variables for computation

The algorithm uses the property that XOR of a subarray can be used to deduce
the XOR of the entire array by exploiting overlapping queries and the reversals
that occur. By strategically querying subarrays, we can reconstruct the final
XOR of all elements. When the array length is not divisible by k, special care
is taken to handle the remainder using additional queries.

Approach:
1. If the remaining elements after full k-sized chunks aren't divisible by k:
   - Query the last k-sized chunk and the overlapping portion to resolve remainder.
2. Iterate through the array in chunks of size k:
   - For each chunk, perform a query to get its XOR.
3. Combine all XOR results to get the final answer.

This solution works under 100 queries due to the efficient use of the overlapping
properties of XOR operations and chunked processing.
"""

from sys import stdin


def make_query(i):
    print(f"? {i }", flush=True)
    resp = int(stdin.readline())
    assert resp != -1
    return resp


n_tests = int(stdin.readline())
for test_id in range(n_tests):
    n, k = map(int, stdin.readline().split())
    res = 0
    rem = n % k
    if rem > 0:
        half_rem = rem // 2
        # Query the last k-sized chunk and an overlapping portion to resolve remainder
        res ^= make_query(n - k + 1)
        res ^= make_query(n - k - half_rem + 1)
        n -= rem
    # Process full k-sized chunks
    for i in range(1, n + 1, k):
        res ^= make_query(i)
    print(f"! {res }", flush=True)


# https://github.com/VaHiX/CodeForces/