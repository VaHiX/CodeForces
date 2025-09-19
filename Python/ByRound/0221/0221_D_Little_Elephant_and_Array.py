# Contest 221, Problem D: Little Elephant and Array
# URL: https://codeforces.com/contest/221/problem/D

import math

n, m = map(int, input().split())

arr = list(map(int, input().split()))
queries = []
for i in range(m):
    u, v = map(int, input().split())
    queries.append([u - 1, v - 1, i])

queries = sorted(queries, key=lambda x: (x[0] // (int(math.sqrt(n))), x[1]))

freq = [0 for i in range(n + 1)]

curr_l = 0
curr_r = 0

answer = 0
final_ans = [0 for i in range(m)]

if arr[0] <= n:
    freq[arr[0]] = 1
    answer += 1 if arr[0] == 1 else 0

for l, r, idx in queries:

    while curr_l > l:
        curr_l -= 1
        if arr[curr_l] <= n:
            freq[arr[curr_l]] += 1
            if freq[arr[curr_l]] == arr[curr_l]:
                answer += 1
            if freq[arr[curr_l]] == arr[curr_l] + 1:
                answer -= 1

    while curr_r < r:
        curr_r += 1
        if arr[curr_r] <= n:
            freq[arr[curr_r]] += 1
            if freq[arr[curr_r]] == arr[curr_r]:
                answer += 1
            if freq[arr[curr_r]] == arr[curr_r] + 1:
                answer -= 1

    while curr_l < l:
        if arr[curr_l] <= n:
            freq[arr[curr_l]] -= 1
            if freq[arr[curr_l]] == arr[curr_l]:
                answer += 1
            if freq[arr[curr_l]] == arr[curr_l] - 1:
                answer -= 1
        curr_l += 1

    while curr_r > r:
        if arr[curr_r] <= n:
            freq[arr[curr_r]] -= 1
            if freq[arr[curr_r]] == arr[curr_r]:
                answer += 1
            if freq[arr[curr_r]] == arr[curr_r] - 1:
                answer -= 1
        curr_r -= 1

    final_ans[idx] = answer

for i in range(m):
    print(final_ans[i])
