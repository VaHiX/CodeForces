# Contest 1423, Problem A: Wakanda Forever
# URL: https://codeforces.com/contest/1423/problem/A

def find_optimal_pairing(n, costs):
    min_costs = [min(costs[i]) for i in range(n)]
    pairs = [0] * n

    for i in range(n):
        pairs[i] = costs[i].index(min_costs[i])

    for i in range(n):
        for j in range(n):
            if i != j and (costs[i][j] < min_costs[i] and costs[j][i] < min_costs[j]):
                return [-1] * n

    return [pair + 1 for pair in pairs]

def main():
    n = int(input())
    costs = [list(map(int, input().split())) for _ in range(n)]

    for i in range(n):
        costs[i].insert(i, -1)

    result = find_optimal_pairing(n, costs)
    print(*result)

if __name__ == "__main__":
    main()