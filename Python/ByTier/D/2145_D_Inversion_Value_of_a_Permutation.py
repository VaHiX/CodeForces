# Problem: CF 2145 D - Inversion Value of a Permutation
# https://codeforces.com/contest/2145/problem/D

"""
Problem: D. Inversion Value of a Permutation

Purpose:
This code constructs a permutation of length n such that its inversion value equals exactly k.
The inversion value is defined as the number of subsegments [l, r] where there exists at least one inversion (i,j) with l <= i < j <= r and p[i] > p[j].

Approach:
- Precompute all possible inversion values for permutations of lengths 1 to 30 using dynamic programming.
- For each test case:
  - Check if the required inversion value k is achievable for given n.
  - If yes, reconstruct the permutation by reversing the DP process and building the final arrangement from segments.

Time Complexity: O(n^3) preprocessing + O(n^2) per query
Space Complexity: O(n^2) for storing DP and best mappings

Algorithm Techniques:
- Dynamic Programming with memoization
- Greedy reconstruction based on computed inversion values
"""

def main():
    import sys

    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    n_max = 30
    dp = [set() for _ in range(n_max + 1)] # dp[i] stores all achievable inversion values for permutations of length i
    best = [dict() for _ in range(n_max + 1)] # best[i][val] gives the last segment size used to achieve inversion value val for length i
    dp[0].add(0) # base case: empty permutation has 0 inversions
    for i in range(1, n_max + 1):
        for j in range(1, i + 1):
            t_val = j * (j - 1) // 2 # number of inversions in a decreasing segment of length j
            for x in dp[i - j]:
                new_val = x + t_val # total inversion value when appending a decreasing segment of length j to existing arrangement of length i-j
                dp[i].add(new_val)
                best[i][new_val] = j # record which segment size was used
    results = []
    for _ in range(t):
        n = int(data[index])
        k = int(data[index + 1])
        index += 2
        total_segments = n * (n - 1) // 2 # maximum possible inversions for a permutation of length n
        I_needed = total_segments - k # compute needed inversion value to construct desired permutation
        if I_needed not in dp[n]:
            results.append("0")
        else:
            runs = []
            cur_n = n
            cur_I = I_needed
            while cur_n > 0:
                j = best[cur_n][cur_I]
                runs.append(j) # collect the segment lengths used to build up the inversion value
                cur_I -= j * (j - 1) // 2 # subtract the inversions contributed by this segment
                cur_n -= j # reduce problem size
            arr = list(range(1, n + 1)) # initial array [1, 2, ..., n]
            perm = []
            for L in runs:
                segment = arr[-L:] # take last L elements (decreasing)
                perm.extend(segment) # add to result permutation
                arr = arr[:-L] # remove those elements from remaining array
            results.append(" ".join(map(str, perm)))
    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/