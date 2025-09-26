# Contest 774, Problem A: Amusement Park
# URL: https://codeforces.com/contest/774/problem/A

num_people, cost1, cost2 = map(int, input().split())
adults_count = input().count("1")

cost_list = []


for i in range(1, adults_count + 1):
    cost = cost1 * i
    cost += i * cost2 * (((num_people // i) - 1) ** 2)
    cost += cost2 * (num_people % i) * (2 * (num_people // i) - 1)

    cost_list.append(cost)


print(min(cost_list))
