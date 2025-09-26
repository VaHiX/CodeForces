# Contest 1575, Problem L: Longest Array Deconstruction
# URL: https://codeforces.com/contest/1575/problem/L

from bisect import bisect_left


def length_of_lis(a):
    if not a:
        return 0

    n = len(a)
    tails = [0] * n
    size = 0

    for num in a:
        left, right = 0, size

        while left < right:
            mid = (left + right) // 2
            if tails[mid] < num:
                left = mid + 1
            else:
                right = mid

        tails[left] = num
        size = max(size, left + 1)

    return size


def solution(n: int, a: list[int]) -> int:
    # initialise a list of list in the size of number of input
    index = [[] for _ in range(n)]

    # sort the elements of the input by adding it to index based on the position and the distance to its position
    # input = [1,4,2]
    # index = [[1],[2]]
    # here 1 is in the correct position so it is in the 0th index, since 2 is one place off, it is in the 1st index
    # since 4 does not have position here since max index is 3, it is removed
    for i, num in enumerate(a):
        i += 1
        if not num > i:
            index[i - num].append(num)

    # flatten the index
    flattened_index = [element for sublist in index for element in sublist]

    # if all elements are removed
    if not flattened_index:
        return 0

    # apply LIS algorithm to obtain the length
    lis = [flattened_index[0]]
    # for num in flattened_index[1:]:
    #     if num > lis[-1]:
    #         lis.append(num)
    #     else:
    #         insert_index = bisect_left(lis, num)
    #         if num < lis[insert_index]:
    #             lis[insert_index] = num

    return length_of_lis(flattened_index)


if __name__ == "__main__":
    n = int(input())
    a = list(map(int, input().split()))
    print(solution(n, a))
