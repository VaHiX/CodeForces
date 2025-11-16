# Problem: CF 1468 L - Prime Divisors Selection
# https://codeforces.com/contest/1468/problem/L

"""
Problem: Select exactly k integers from a given list such that they form an ideal sequence.
An ideal sequence is one where every suitable prime assignment (each element divisible by a prime) is friendly (no unique primes).

Approach:
1. For each number, find its prime factors.
2. Identify if a subset forms an ideal sequence by checking that all valid prime assignments are friendly.
3. Use greedy and combinatorial logic to select k numbers such that the resulting set satisfies the condition.

Time Complexity: O(N^2 * sqrt(max_value)) where N is the number of elements and max_value is up to 10^18
Space Complexity: O(N * log(max_value)) for storing prime factor information per element

Algorithm Techniques:
- Prime factorization with smallest prime divisor optimization
- Combinatorial selection and constraint checking
- Greedy assignment based on prime counts
"""

import sys


def find_valid_subset():
    N, K = map(int, sys.stdin.readline().split())
    numbers = list(map(int, sys.stdin.readline().split()))
    result = process_data(N, K, numbers)
    if result == 0:
        print(0)
    else:
        print(" ".join(map(str, result)))


def process_data(N, K, numbers):
    from collections import defaultdict

    def smallest_prime_factor(x):
        # Find the smallest prime factor of x
        for i in range(2, int(x**0.5) + 1):
            if x % i == 0:
                while x % i == 0:
                    x //= i
                return i if x == 1 else -1
        return x

    prime_sets = []
    original_numbers = numbers[:]
    prime_indices = defaultdict(list)
    
    # Preprocessing: check divisibility relationships between pairs of numbers
    for i in range(N):
        for j in range(N):
            if i != j and numbers[j] % numbers[i] == 0:
                x, y = numbers[i], numbers[j] // numbers[i]
                # Ensure x >= y for proper factorization check
                if x < y:
                    x, y = y, x
                # Reduce y to see if x is a power of y
                while y != 1:
                    if x % y != 0:
                        break
                    x, y = y, x // y
                    if x < y:
                        x, y = y, x
                if y == 1:
                    # Find the smallest prime that divides this x (assumed to be a prime power)
                    prime = smallest_prime_factor(x)
                    if prime >= 2:
                        prime_sets.append(prime)

    # Unique primes in our set
    prime_sets = sorted(set(prime_sets))
    
    # Initialize factor list for each prime (to store indices of numbers divisible by that prime)
    factor_lists = [[] for _ in range(len(prime_sets))]
    
    for i in range(N):
        # For each number, find primes dividing it
        for j, prime in enumerate(prime_sets):
            if numbers[i] % prime == 0:
                # Divide out all factors of this prime to check if remaining is 1
                while numbers[i] % prime == 0:
                    numbers[i] //= prime
                prime_indices[i].append(j)
        # If after division only 1 remains, then it's a product of primes in our list
        if numbers[i] == 1 and len(prime_indices[i]) == 1:
            factor_lists[prime_indices[i][0]].append(i)

    all_count, remove_count = 0, 0
    valid_prime = [False] * len(prime_sets)
    
    # Compute which primes have at least two numbers associated with them
    for i in range(len(prime_sets)):
        if len(factor_lists[i]) >= 2:
            valid_prime[i] = True
            all_count += len(factor_lists[i])
            remove_count += len(factor_lists[i]) - 2

    result_indices = []
    
    # If total count meets or is under k, try direct inclusion
    if all_count <= K:
        for i in range(N):
            if (
                numbers[i] == 1
                and len(prime_indices[i]) == 1
                and valid_prime[prime_indices[i][0]]
            ):
                result_indices.append(i)
        for i in range(N):
            if (
                numbers[i] == 1
                and len(prime_indices[i]) > 1
                and len(result_indices) < K
            ):
                if all(valid_prime[j] for j in prime_indices[i]):
                    result_indices.append(i)
    else:
        # Group by primes to control how many elements to pick
        grouped_factors = [[] for _ in range(len(prime_sets))]
        for i in range(N):
            if (
                numbers[i] == 1
                and len(prime_indices[i]) == 1
                and valid_prime[prime_indices[i][0]]
            ):
                grouped_factors[prime_indices[i][0]].append(i)
                
        # Check if we can reduce enough elements to meet K limit
        if all_count - remove_count <= K:
            for i in range(len(prime_sets)):
                if grouped_factors[i]:
                    result_indices.extend(grouped_factors[i][:2])
            for i in range(len(prime_sets)):
                for j in range(2, len(grouped_factors[i])):
                    if len(result_indices) < K:
                        result_indices.append(grouped_factors[i][j])
        elif K % 2 == 0:
            # Select pairs from valid primes
            for i in range(len(prime_sets)):
                if grouped_factors[i] and len(result_indices) < K:
                    result_indices.extend(grouped_factors[i][:2])
        elif K >= 3:
            # Try to find a special prime group with at least three elements
            special_factor = -1
            for i in range(len(prime_sets)):
                if len(grouped_factors[i]) >= 3:
                    special_factor = i
            if special_factor >= 0:
                result_indices.extend(grouped_factors[special_factor][:3])
                # Add more from other valid primes while maintaining K limit
                for i in range(len(prime_sets)):
                    if (
                        i != special_factor
                        and grouped_factors[i]
                        and len(result_indices) < K
                    ):
                        result_indices.extend(grouped_factors[i][:2])
            else:
                # Consider combinations with more than one prime factor, if beneficial
                candidate = -1
                for i in range(N):
                    if numbers[i] == 1 and len(prime_indices[i]) > 1:
                        if (
                            all(valid_prime[j] for j in prime_indices[i])
                            and 1 + 2 * len(prime_indices[i]) <= K
                        ):
                            candidate = i
                            break
                if candidate >= 0:
                    result_indices.append(candidate)
                    used_factors = [False] * len(prime_sets)
                    for j in prime_indices[candidate]:
                        used_factors[j] = True
                        result_indices.extend(grouped_factors[j][:2])
                    for i in range(len(prime_sets)):
                        if (
                            not used_factors[i]
                            and grouped_factors[i]
                            and len(result_indices) < K
                        ):
                            result_indices.extend(grouped_factors[i][:2])

    # Return result if valid number of entries selected
    if len(result_indices) < K:
        return 0
    return [original_numbers[i] for i in result_indices[:K]]


find_valid_subset()


# https://github.com/VaHiX/codeForces/