# Problem: CF 2001 B - Generate Permutation
# https://codeforces.com/contest/2001/problem/B

"""
Code Purpose:
This code solves the problem of generating a permutation of length n such that 
the minimum number of carriage return operations needed to construct the permutation 
is the same regardless of which typewriter (left-to-right or right-to-left) is used.
The solution leverages the observation that for even n, it's impossible to achieve 
equal carriage return counts due to parity issues, while for odd n, a specific 
swap pattern ensures symmetry.

Algorithms/Techniques:
- Greedy approach with parity analysis
- Swapping adjacent elements to balance pointer movements
- Construction of permutation based on symmetry requirements

Time Complexity: O(n) for each test case, where n is the length of the permutation.
Space Complexity: O(n) for storing the result permutation and intermediate data.
"""

def main():
    import sys

    input = sys.stdin.read
    data = input().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        # If n is even, it's impossible to have equal carriage returns
        # because the number of operations required will differ due to parity
        if n % 2 == 0:
            results.append("-1")
        else:
            # Create a permutation from 1 to n
            p = list(range(1, n + 1))
            # Swap adjacent elements starting from index 1 to balance operations
            # This ensures that both typewriters require the same number of carriage returns
            for i in range(1, n, 2):
                if i + 1 < n:
                    p[i], p[i + 1] = p[i + 1], p[i]
            results.append(" ".join(map(str, p)))
    for result in results:
        print(result)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/