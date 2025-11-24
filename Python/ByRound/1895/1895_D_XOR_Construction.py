# Problem: CF 1895 D - XOR Construction
# https://codeforces.com/contest/1895/problem/D

"""
Algorithm: XOR Construction
Techniques: 
    - XOR properties and bit manipulation
    - Constructing a sequence from XOR differences
    - Greedy bit construction

Time Complexity: O(n log n)
Space Complexity: O(n)

The problem is to construct an array b such that:
- Every integer from 0 to n-1 appears exactly once
- For each i, b[i] XOR b[i+1] = a[i]

Approach:
1. First, we compute prefix XORs p[i] such that p[i] = a[0] XOR ... XOR a[i-1]
2. We try to find a value x such that when we compute b[i] = x XOR p[i], 
   all values in b are distinct and in range [0, n-1].
3. To find x, we test each bit position and ensure that the XOR pattern 
   results in valid distribution of values.
4. The final array is constructed as b[i] = x XOR p[i]
"""

def solve():
    import sys

    data = sys.stdin.read().split()
    n = int(data[0])
    a = list(map(int, data[1 : 1 + n - 1]))
    p = [0] * n
    for i in range(1, n):
        p[i] = p[i - 1] ^ a[i - 1]
    x = 0
    for bit in range(0, 19):
        half = 1 << bit
        count_p = 0
        for num in p:
            if num & half:
                count_p += 1
        cycle = 2 * half
        count_i = (n // cycle) * half
        r = n % cycle
        if r > half:
            count_i += r - half
        if count_p != count_i:
            x |= half
    result = [x ^ num for num in p]
    print(" ".join(map(str, result)))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/