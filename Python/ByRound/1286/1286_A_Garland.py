# Contest 1286, Problem A: Garland
# URL: https://codeforces.com/contest/1286/problem/A

n = int(input())
nums = list(map(int, input().split()))

if max(nums) == 0:
    print(1 if n > 1 else 0)
else:
    odd_count = n - n // 2
    even_count = n // 2
    for i in range(n):
        if nums[i]:
            if nums[i] % 2:
                odd_count -= 1
            else:
                even_count -= 1

    start_count = 0
    startEven = False
    for i in range(n):
        if nums[i]:
            startEven = nums[i] % 2 == 0
            idx1 = i
            break
        else:
            start_count += 1

    end_count = 0
    endEven = False
    for i in range(n - 1, -1, -1):
        if nums[i]:
            endEven = nums[i] % 2 == 0
            idx2 = i
            break
        else:
            end_count += 1

    ans = 2
    v = idx1
    odd_lst = []
    even_lst = []
    for i in range(idx1 + 1, idx2 + 1):
        if nums[i]:
            if (nums[i] - nums[v]) % 2:
                ans += 1
            else:
                if nums[i] % 2:
                    odd_lst.append(i - v - 1)
                else:
                    even_lst.append(i - v - 1)
                ans += 2
            v = i

    odd_lst.sort()
    even_lst.sort()

    for x in odd_lst:
        if odd_count >= x:
            odd_count -= x
            ans -= 2

    for x in even_lst:
        if even_count >= x:
            even_count -= x
            ans -= 2

    if startEven:
        if even_count >= start_count:
            even_count -= start_count
            ans -= 1
    else:
        if odd_count >= start_count:
            odd_count -= start_count
            ans -= 1

    if endEven:
        if even_count >= end_count:
            even_count -= end_count
            ans -= 1
    else:
        if odd_count >= end_count:
            odd_count -= end_count
            ans -= 1

    print(ans)
