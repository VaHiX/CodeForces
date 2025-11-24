# Problem: CF 1900 D - Small GCD
# https://codeforces.com/contest/1900/problem/D

"""
Algorithm: 
- Precompute Euler's totient function (phi) for all numbers up to 10^5 using sieve technique.
- Precompute divisors for all numbers up to 10^5.
- For each sorted array element, calculate contribution of previous elements using precomputed data.
- Use inclusion-exclusion principle with totient function to efficiently compute sum of GCDs over all triplets.

Time Complexity: O(N * sqrt(max_val) + max_val * log(max_val)) where N is the number of elements in the array and max_val is 100000.
Space Complexity: O(max_val) for storing phi and divisors arrays.
"""

import sys


def main():
    max_val = 100000
    # Precompute Euler's totient function using sieve
    phi = list(range(max_val + 1))
    for i in range(2, max_val + 1):
        if phi[i] == i:  # i is prime
            for j in range(i, max_val + 1, i):
                phi[j] -= phi[j] // i  # Apply Euler's totient formula
    # Precompute divisors for each number up to max_val
    divisors = [[] for _ in range(max_val + 1)]
    for i in range(1, max_val + 1):
        for j in range(i, max_val + 1, i):
            divisors[j].append(i)
    # Read input data
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    res = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        a = list(map(int, data[index : index + n]))
        index += n
        a.sort()  # Sort the array to simplify processing
        cnt = [0] * (max_val + 1)  # Count of elements with specific divisors
        total_ans = 0
        for j in range(n):
            x = a[j]
            s_j = 0
            # For current element x, compute its contribution using previous elements
            for d in divisors[x]:
                s_j += phi[d] * cnt[d]  # Sum of phi(d) * count of elements divisible by d
            # Update counters for all divisors of x
            for d in divisors[x]:
                cnt[d] += 1
            # Add contribution of this element to the result
            total_ans += s_j * (n - j - 1)
        res.append(str(total_ans))
    sys.stdout.write("\n".join(res))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/