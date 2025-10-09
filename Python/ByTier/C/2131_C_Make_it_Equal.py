# Problem: CF 2131 C - Make it Equal
# https://codeforces.com/contest/2131/problem/C

"""
C. Make it Equal
time limit per test2 seconds
memory limit per test256 megabytes

Problem: 
Given two multisets S and T of size n and a positive integer k, determine if it is possible to transform S into T by repeatedly performing operations:
- Select an element x in S, remove one occurrence of x.
- Insert either x + k or |x - k| into S.

Approach:
1. For each element in both arrays, compute the minimum cost (number of operations) to make it congruent to 0 modulo k.
   This is done by taking min(x % k, k - x % k), representing the minimal steps needed to reach a multiple of k.
2. Sort these computed remainders for both arrays.
3. If sorted remainder arrays are equal, then S can be transformed into T.

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the remainder arrays

Algorithms/Techniques:
- Modular arithmetic for equivalence classes
- Greedy approach using minimal operations
- Sorting for comparison of multiset properties
"""

def read_ints():
    """Read a line of integers from input."""
    return list(map(int, input().split()))


def can_make_equal(n, k, a, b):
    """
    Check if two arrays can be made equal by adding/subtracting multiples of k.
    Args:
        n: Number of elements in each array
        k: The modulo value for operations
        a: First array of integers
        b: Second array of integers
    Returns:
        bool: True if arrays can be made equal, False otherwise
    """
    # Compute minimal operations needed to make each element divisible by k
    remainders_a = [min(x % k, k - x % k) for x in a]
    remainders_b = [min(x % k, k - x % k) for x in b]
    # Compare sorted remainders
    return sorted(remainders_a) == sorted(remainders_b)


def main():
    test_cases = int(input())
    for _ in range(test_cases):
        n, k = map(int, input().split())
        a = list(map(int, input().split()))
        b = list(map(int, input().split()))
        if can_make_equal(n, k, a, b):
            print("YES")
        else:
            print("NO")


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/