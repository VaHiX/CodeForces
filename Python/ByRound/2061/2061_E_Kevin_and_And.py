# Contest 2061, Problem E: Kevin and And
# URL: https://codeforces.com/contest/2061/problem/E

import io, os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def main():
    m, n, k = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))

    MAX = (1 << 30) - 1

    b = [MAX - num for num in b]

    costs = [[] for _ in range(n + 1)]

    def getnext(index, pre, curr):
        if index == n:
            if len(pre) > 0:
                costs[len(pre) - 1].append(curr)
            return
        getnext(index + 1, pre, curr)
        pre.append(b[index])
        getnext(index + 1, pre, curr | b[index])
        pre.pop()

    getnext(0, [], 0)
    save = []

    for num in a:
        nums = [num]
        for i in range(n):
            minimum = num
            for sub in costs[i]:
                minimum = min(minimum, (~sub) & num)
            nums.append(minimum)
        diff = [nums[i] - nums[i + 1] for i in range(len(nums) - 1)]
        save.extend(diff)

    save.sort(reverse=True)
    #    print(save)
    print(sum(a) - sum(save[:k]))


T = int(input())
t = 1
while t <= T:
    main()
    t += 1
