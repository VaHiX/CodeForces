# Problem: CF 1943 E2 - MEX Game 2 (Hard Version)
# https://codeforces.com/contest/1943/problem/E2

"""
Algorithm: Binary search on the answer combined with a greedy game analysis.
The problem involves a game between Alice and Bob where they take turns picking elements from an array.
Alice picks 1 element per turn, Bob picks up to k elements per turn.
Alice wants to maximize her MEX (Minimum Excludant) of the array she builds.
Bob wants to minimize Alice's MEX.

Approach:
- The key idea is to binary search on the possible MEX value (from 0 to m+1).
- For a given MEX value `x`, we need to determine if Alice can achieve it.
- This is modeled using a greedy simulation and optimization:
  - We simulate how many elements of each value Alice and Bob can pick to allow `x` MEX.
  - For each value i, if there are `f[i]` copies and we want to allow Alice to build up to `x` (i.e., she can use all elements 0 to x-1), then we determine how many of these copies Alice can take or how many Bob can prevent her from taking.
  - This results in a greedy optimization problem, solved using sliding window techniques and precomputation.

Time Complexity: O((m + 1) log m) per test case due to binary search on MEX and greedy simulation.
Space Complexity: O(m + 1) for storing frequency and temporary arrays.
"""

def solve_test_case(m, k, frequencies):
    # Sort frequencies to process in increasing order
    frequencies.sort()
    temp = [float("inf")] * (m + 1)
    l = 1
    curr = 0
    # Iterate over values to compute greedy optimal for MEX
    for x in range(1, len(frequencies)):
        curr += frequencies[x]
        # Reduce window while maintaining the constraint that Bob can block Alice up to l elements
        while l < x and (curr - frequencies[l]) - (x - l) * frequencies[l] >= l * k:
            curr -= frequencies[l]
            l += 1
        temp[x - l] = min(temp[x - l], curr - l * k)
    
    # Process from right to left to refine the greedy estimates
    for x in range(len(frequencies) - 1, 0, -1):
        temp[x - 1] = min(temp[x - 1], (temp[x] - temp[x] // (x + 1)) - k)
    
    # Return whether Alice can achieve a MEX of 0 (i.e., can pick 0)
    return temp[0] > 0


def main():
    import sys
    input = sys.stdin.read
    data = input().split()
    idx = 0
    t = int(data[idx])
    idx += 1
    results = []
    for _ in range(t):
        m = int(data[idx])
        k = int(data[idx + 1])
        idx += 2
        frequencies = list(map(int, data[idx : idx + m + 1]))
        idx += m + 1
        lo = 0
        hi = m + 2
        # Binary search on the answer: what's the maximum MEX Alice can achieve?
        while hi - lo > 1:
            mi = (hi + lo) // 2
            if solve_test_case(mi, k, frequencies[:mi]):
                lo = mi
            else:
                hi = mi
        results.append(lo)
    print("\n".join(map(str, results)))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/