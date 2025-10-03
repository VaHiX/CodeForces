# Contest 1468, Problem L: Prime Divisors Selection
# URL: https://codeforces.com/contest/1468/problem/L

import sys


def find_valid_subset():
    # Read input in Codeforces-style
    N, K = map(int, sys.stdin.readline().split())
    numbers = list(map(int, sys.stdin.readline().split()))

    # Call the function with parsed input
    result = process_data(N, K, numbers)

    # Output the result in the expected format
    if result == 0:
        print(0)
    else:
        print(" ".join(map(str, result)))


def process_data(N, K, numbers):
    from collections import defaultdict

    def smallest_prime_factor(x):
        for i in range(2, int(x**0.5) + 1):
            if x % i == 0:
                while x % i == 0:
                    x //= i
                return i if x == 1 else -1
        return x

    prime_sets = []
    original_numbers = numbers[:]
    prime_indices = defaultdict(list)

    for i in range(N):
        for j in range(N):
            if i != j and numbers[j] % numbers[i] == 0:
                x, y = numbers[i], numbers[j] // numbers[i]
                if x < y:
                    x, y = y, x
                while y != 1:
                    if x % y != 0:
                        break
                    x, y = y, x // y
                    if x < y:
                        x, y = y, x
                if y == 1:
                    prime = smallest_prime_factor(x)
                    if prime >= 2:
                        prime_sets.append(prime)

    prime_sets = sorted(set(prime_sets))
    factor_lists = [[] for _ in range(len(prime_sets))]

    for i in range(N):
        for j, prime in enumerate(prime_sets):
            if numbers[i] % prime == 0:
                while numbers[i] % prime == 0:
                    numbers[i] //= prime
                prime_indices[i].append(j)
        if numbers[i] == 1 and len(prime_indices[i]) == 1:
            factor_lists[prime_indices[i][0]].append(i)

    all_count, remove_count = 0, 0
    valid_prime = [False] * len(prime_sets)

    for i in range(len(prime_sets)):
        if len(factor_lists[i]) >= 2:
            valid_prime[i] = True
            all_count += len(factor_lists[i])
            remove_count += len(factor_lists[i]) - 2

    result_indices = []

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
        grouped_factors = [[] for _ in range(len(prime_sets))]
        for i in range(N):
            if (
                numbers[i] == 1
                and len(prime_indices[i]) == 1
                and valid_prime[prime_indices[i][0]]
            ):
                grouped_factors[prime_indices[i][0]].append(i)

        if all_count - remove_count <= K:
            for i in range(len(prime_sets)):
                if grouped_factors[i]:
                    result_indices.extend(grouped_factors[i][:2])
            for i in range(len(prime_sets)):
                for j in range(2, len(grouped_factors[i])):
                    if len(result_indices) < K:
                        result_indices.append(grouped_factors[i][j])
        elif K % 2 == 0:
            for i in range(len(prime_sets)):
                if grouped_factors[i] and len(result_indices) < K:
                    result_indices.extend(grouped_factors[i][:2])
        elif K >= 3:
            special_factor = -1
            for i in range(len(prime_sets)):
                if len(grouped_factors[i]) >= 3:
                    special_factor = i
            if special_factor >= 0:
                result_indices.extend(grouped_factors[special_factor][:3])
                for i in range(len(prime_sets)):
                    if (
                        i != special_factor
                        and grouped_factors[i]
                        and len(result_indices) < K
                    ):
                        result_indices.extend(grouped_factors[i][:2])
            else:
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

    if len(result_indices) < K:
        return 0
    return [original_numbers[i] for i in result_indices[:K]]


# To run this in Codeforces-style:
# - Call `find_valid_subset()` in `main()` function.
# - Redirect standard input in local testing, or use actual input in the contest.
find_valid_subset()
