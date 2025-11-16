# Problem: CF 1874 C - Jellyfish and EVA
# https://codeforces.com/contest/1874/problem/C

"""
Algorithm: Dynamic Programming with Optimal Strategy
Technique: Probability calculation using optimal choices for Jellyfish

Time Complexity: O(n^2 + m), where n is the number of cities and m is the number of roads.
Space Complexity: O(n^2), for storing the probability coefficients and the probability array.

The problem is solved using dynamic programming. For each city u, we compute the maximum 
probability of reaching the destination city n from u. Jellyfish chooses a road optimally,
and Asuka chooses randomly among available roads. The optimal choice for Jellyfish is 
computed by considering all possible outcomes of Asuka's random choice and selecting 
the one that maximizes the probability.

The coefficient matrix 'coeff' stores precomputed values for calculating the expected 
probability of success when multiple roads are available. It uses dynamic programming 
to build up coefficients for different numbers of branches.
"""

import sys


def input_general():
    return sys.stdin.readline().rstrip("\r\n")


def input_num():
    return int(sys.stdin.readline().rstrip("\r\n"))


def input_multi(x=int):
    return map(x, sys.stdin.readline().rstrip("\r\n").split())


def input_list(x=int):
    return list(input_multi(x))


# Precomputed coefficients for calculating expected probabilities
coeff = [[], [1.0], [0.5, 0.0], [1 / 3, 1 / 3, 1 / 3]]


def main():
    n, m = input_multi()
    edge_dict = [[] for _ in range(n + 1)]

    # Build adjacency list of roads
    for _ in range(m):
        u, v = input_multi()
        edge_dict[u].append(v)

    # prob[i] stores the probability of reaching city n from city i
    prob = [0.0] * (n + 1)
    prob[n] = 1.0  # Base case: probability of reaching n from n is 1

    # Process cities from n-1 down to 1
    for u in range(n - 1, 0, -1):
        # Get all reachable cities from city u
        nbd = [prob[v] for v in edge_dict[u]]

        if not nbd:
            # If no roads available, probability is 0
            prob[u] = 0
            continue

        # Sort reachable probabilities in descending order
        nbd.sort(reverse=True)
        d = len(nbd)

        # Extend coeff array if needed
        if len(coeff) <= d:
            for nd in range(len(coeff), d + 1):
                if nd % 2 == 1:
                    # For odd number of branches, evenly distribute probability
                    coeff.append([1 / nd] * nd)
                else:
                    # For even number of branches, compute weighted probabilities
                    it = coeff[-2]
                    new = [1 / nd]
                    for i, (p1, p2) in enumerate(zip([0] + it, it + [0])):
                        new.append((p1 * i + p2 * (nd - 2 - i)) / nd)
                    coeff.append(new)

        # Calculate probability of success from city u
        prob[u] = sum(p1 * p2 for p1, p2 in zip(nbd, coeff[d]))

    print(prob[1])


if __name__ == "__main__":
    cases = input_num()

    for _ in range(cases):
        main()


# https://github.com/VaHiX/CodeForces/