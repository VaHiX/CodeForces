# Problem: CF 1928 D - Lonely Mountain Dungeons
# https://codeforces.com/contest/1928/problem/D

"""
Algorithm: 
This problem involves maximizing the strength of an army formed by distributing creatures of different races into squads. 
Key concepts include:
1. Each pair of creatures from the same race in different squads contributes 'b' to the strength.
2. The army strength decreases by (k-1)*x for k squads.
3. For each possible number of squads k, we calculate the maximum possible strength by optimally distributing creatures.
4. The approach uses a mathematical insight to evaluate the distribution efficiently instead of brute-force.

Time Complexity: O(max(c_i) * n) where n is the number of races and max(c_i) is the maximum number of creatures of any race.
Space Complexity: O(max(c_i)) for storing the count of pairs within squads.

Approach:
- We iterate over all possible numbers of squads (from 1 to max(c_i)).
- For each k (number of squads), we calculate how many pairs of creatures within the same race get clustered together (and thus don't contribute to the strength).
- We subtract those pairs from the total and multiply by 'b'.
- We subtract the penalty (k-1)*x.
- Keep track of the maximum strength over all values of k.
"""

import sys


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        b = int(data[index])
        index += 1
        x = int(data[index])
        index += 1
        c = list(map(int, data[index : index + n]))
        index += n
        # Calculate the total number of pairs possible from all creatures combined
        total_pairs = 0
        for num in c:
            total_pairs += num * (num - 1) // 2
        if n == 0:
            results.append("0")
            continue
        # Find maximum number of creatures in any race
        max_c = max(c)
        # Create an array to store number of intra-cluster pairs for each k (number of squads)
        val = [0] * (max_c + 1)
        for num in c:
            # For each possible number of squads k, compute how many pairs are clustered
            # within the same squad for a group of num creatures
            for k in range(1, num + 1):
                cnt = num // k  # How many full groups of size k
                rem = num % k   # Remaining creatures after grouping
                # Compute the number of pairs within a group, considering remainders
                within = rem * (cnt + 1) * cnt // 2 + (k - rem) * cnt * (cnt - 1) // 2
                if k <= max_c:
                    val[k] += within
        best = -(10**18)
        # Iterate over possible number of squads k
        for k in range(1, max_c + 1):
            within_total = val[k]
            # Calculate strength for k squads
            strength = b * (total_pairs - within_total) - (k - 1) * x
            if strength > best:
                best = strength
        # Consider case of max_c squads (default if all creatures are in separate squads)
        strength_inf = b * total_pairs - (max_c) * x
        if strength_inf > best:
            best = strength_inf
        results.append(str(best))
    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/