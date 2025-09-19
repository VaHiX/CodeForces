# Contest 2038, Problem K: Grid Walk
# URL: https://codeforces.com/contest/2038/problem/K


def gcd_array(length: int, value: int) -> list[int]:
    array = [1 for _ in range(length)]
    for i in range(2, min(length, value) + 1):
        if value % i == 0:
            for j in range(i - 1, length, i):
                array[j] = i
    return array


def max_coprime(gcds: list[int]) -> int:
    for i in range(len(gcds) - 1, 0, -1):
        if gcds[i] == 1:
            return i + 1
    return 1


def min_cost_dp(row_costs: list[int], column_costs: list[int]) -> int:
    n_rows = len(row_costs)
    n_columns = len(column_costs)
    cumulative_costs = [[0 for _ in range(n_columns)] for _ in range(n_rows)]
    for j in range(1, n_columns):
        cumulative_costs[0][j] = cumulative_costs[0][j - 1] + row_costs[0]
    for i in range(1, n_rows):
        cumulative_costs[i][0] = cumulative_costs[i - 1][0] + column_costs[0]
        for j in range(1, n_columns):
            cumulative_costs[i][j] = min(
                cumulative_costs[i][j - 1] + row_costs[i],
                cumulative_costs[i - 1][j] + column_costs[j],
            )
    return cumulative_costs[-1][-1]


n, a, b = map(int, input().split())
row_costs = gcd_array(n, a)
column_costs = gcd_array(n, b)
max_coprime_with_a = max_coprime(row_costs)
max_coprime_with_b = max_coprime(column_costs)
dp_cost = min_cost_dp(
    row_costs[max_coprime_with_a - 1 :], column_costs[max_coprime_with_b - 1 :]
)
min_cost = (
    sum(row_costs)
    + sum(column_costs)
    + (max_coprime_with_a - 1)
    + (max_coprime_with_b - 1)
    + dp_cost
)
print(min_cost)
