# Problem: CF 2035 C - Alya and Permutation
# https://codeforces.com/contest/2035/problem/C

"""
Algorithm/Techniques: Bit manipulation, constructive algorithm, binary representation analysis

Time Complexity: O(n) for each test case, since we construct the permutation in linear time
Space Complexity: O(n) for storing the permutation

This problem involves constructing a permutation of integers 1 to n that maximizes the value of k 
after a series of bitwise AND and OR operations. The key insight is to analyze how the operations 
affect the bits of k. For odd steps, we perform AND which can only reduce or keep the same bits, 
while for even steps, OR can only set or keep bits. The algorithm constructs a specific permutation 
to maximize the final value of k by strategically placing numbers to ensure that the final value 
after all operations is maximized.
"""

t = int(input())


def get_max(n):
    # If n is even, return the maximum possible value which is 2^(number of bits) - 1
    if n % 2 == 0:
        return 2 ** (len(bin(n)) - 2) - 1
    else:
        # If n is odd, return n itself as the maximum possible value
        return n


def gen_perm(n):
    # Base case for small n
    if n == 5:
        return [2, 1, 3, 4, 5]
    
    # If n is even
    if n % 2 == 0:
        # If n is a power of 2, we recursively get permutation for n-1 and append n
        if n.bit_count() == 1:
            ans = gen_perm(n - 1)
            ans.append(n)
        else:
            # Otherwise, compute the highest power of 2 less than n
            last = (2 ** (len(bin(n)) - 3)) - 1
            # Generate permutation by excluding 'last' and appending it at the end
            ans = [i for i in range(1, n + 1) if i != last]
            ans.append(last)
    else:
        # If n is odd, recursively generate permutation for n-1 and append n
        ans = gen_perm(n - 1)
        ans.append(n)
    
    return ans


for _ in range(t):
    n = int(input())
    print(get_max(n))
    print(" ".join(map(str, gen_perm(n))))


# https://github.com/VaHiX/CodeForces/