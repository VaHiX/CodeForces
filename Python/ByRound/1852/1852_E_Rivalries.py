# Problem: CF 1852 E - Rivalries
# https://codeforces.com/contest/1852/problem/E

import sys


class SegmentTree:
    """
    A segment tree data structure supporting:
      - Initialization from a list of values.
      - Range queries using a specified merge function (default is max).
      - Single-element updates.
      
    Time Complexity: O(n) for initialization, O(log n) for updates and queries
    Space Complexity: O(n)
    """

    def __init__(self, initialData, defaultValue=0, mergeFunction=max):
        """
        Initializes the segment tree.

        Args:
            initialData: A list of numerical values to build the tree from.
            defaultValue: The neutral element for the merge function.
            mergeFunction: A function that merges two child values (e.g. max).
        """
        self.defaultValue = defaultValue
        self.mergeFunction = mergeFunction
        self.length = len(initialData)
        self.treeSize = 1 << (self.length - 1).bit_length()

        self.treeData = [defaultValue] * (2 * self.treeSize)
        self.treeData[self.treeSize : self.treeSize + self.length] = initialData

        for i in reversed(range(self.treeSize)):
            leftChild = self.treeData[i * 2]
            rightChild = self.treeData[i * 2 + 1]
            self.treeData[i] = mergeFunction(leftChild, rightChild)

    def __getitem__(self, idx):
        """
        Gets the value at index idx in the original array.
        """
        return self.treeData[idx + self.treeSize]

    def __setitem__(self, idx, value):
        """
        Sets the value at index idx in the original array, updating the tree.
        """
        idx += self.treeSize
        self.treeData[idx] = value
        idx >>= 1
        while idx:
            self.treeData[idx] = self.mergeFunction(
                self.treeData[idx << 1], self.treeData[(idx << 1) + 1]
            )
            idx >>= 1

    def rangeQuery(self, leftIndex, rightIndex):
        """
        Merges values in the range [leftIndex, rightIndex) using mergeFunction.

        Args:
            leftIndex: The start of the query range (inclusive).
            rightIndex: The end of the query range (exclusive).

        Returns:
            The merged value from leftIndex to rightIndex-1.
        """
        leftIndex += self.treeSize
        rightIndex += self.treeSize

        resultLeft = self.defaultValue
        resultRight = self.defaultValue

        while leftIndex < rightIndex:

            if leftIndex & 1:
                resultLeft = self.mergeFunction(resultLeft, self.treeData[leftIndex])
                leftIndex += 1

            if rightIndex & 1:
                rightIndex -= 1
                resultRight = self.mergeFunction(self.treeData[rightIndex], resultRight)
            leftIndex >>= 1
            rightIndex >>= 1

        return self.mergeFunction(resultLeft, resultRight)


def solveAllTests():
    """
    Reads multiple test cases from standard input and processes each case.

    For each test:
      - Reads n and a list of size n.
      - Performs specialized operations using segment trees and arrays.
      - Computes a specific arrangement with maximum sum under constraints.
      - Collects the resulting configuration and prints it.
      
    Time Complexity: O(n log n) per test case
    Space Complexity: O(n)
    """
    inputData = sys.stdin.read().strip().split()
    testCases = int(inputData[0])
    indexInput = 1

    results = []

    for _ in range(testCases):
        arraySize = int(inputData[indexInput])
        indexInput += 1

        initialList = list(map(int, inputData[indexInput : indexInput + arraySize]))
        indexInput += arraySize

        extendedList = initialList + [max(1, val - 1) for val in initialList]

        extendedList = sorted(set(extendedList))
        mappedSize = len(extendedList)

        extendedList.append(float("inf"))

        indexMap = {}
        for i in range(mappedSize - 1, -1, -1):
            indexMap[extendedList[i]] = i

        transformedList = [indexMap[val] for val in initialList]

        leftMostOccur = [-1] * mappedSize
        rightMostOccur = [-1] * mappedSize

        for i in range(arraySize):
            rightMostOccur[transformedList[i]] = i
            if leftMostOccur[transformedList[i]] == -1:
                leftMostOccur[transformedList[i]] = i

        segmentMax = SegmentTree([0] * mappedSize, defaultValue=-1, mergeFunction=max)

        remainTree = SegmentTree(list(range(arraySize)), defaultValue=-1)

        isImportant = [0] * arraySize
        countRemaining = arraySize
        totalSum = 0

        specialFlag = [0] * mappedSize

        for i in range(arraySize):
            if i == rightMostOccur[transformedList[i]]:

                if (
                    segmentMax.rangeQuery(transformedList[i], mappedSize)
                    <= leftMostOccur[transformedList[i]]
                ):
                    segmentMax[transformedList[i]] = leftMostOccur[transformedList[i]]
                    specialFlag[transformedList[i]] = 1
                    isImportant[leftMostOccur[transformedList[i]]] = 1
                    isImportant[rightMostOccur[transformedList[i]]] = 1

                    if remainTree[leftMostOccur[transformedList[i]]] != -1:
                        remainTree[leftMostOccur[transformedList[i]]] = -1
                        countRemaining -= 1
                        totalSum += extendedList[transformedList[i]]

                    if remainTree[rightMostOccur[transformedList[i]]] != -1:
                        remainTree[rightMostOccur[transformedList[i]]] = -1
                        countRemaining -= 1
                        totalSum += extendedList[transformedList[i]]

        takenTree = SegmentTree(
            [mappedSize] * arraySize, defaultValue=mappedSize, mergeFunction=min
        )

        stackForSegments = []
        possibleArrangements = []

        for i in range(mappedSize - 1, -1, -1):
            if specialFlag[i] == 0:

                while stackForSegments:
                    leftPos, rightPos = stackForSegments.pop()
                    penalty = 0

                    if remainTree.rangeQuery(0, leftPos) == -1:
                        minIndexLeft = takenTree.rangeQuery(0, leftPos)
                        penalty += extendedList[minIndexLeft] - extendedList[i]

                    if remainTree.rangeQuery(rightPos, arraySize) == -1:
                        minIndexRight = takenTree.rangeQuery(rightPos, arraySize)
                        penalty += extendedList[minIndexRight] - extendedList[i]

                    currentScore = countRemaining * extendedList[i] + totalSum - penalty
                    possibleArrangements.append((currentScore, i, leftPos, rightPos))
            else:

                indexToCheck = remainTree.rangeQuery(
                    leftMostOccur[i], rightMostOccur[i]
                )
                while indexToCheck != -1:
                    totalSum += extendedList[i]
                    remainTree[indexToCheck] = -1
                    takenTree[indexToCheck] = i
                    countRemaining -= 1

                    indexToCheck = remainTree.rangeQuery(
                        leftMostOccur[i], rightMostOccur[i]
                    )

                stackForSegments.append((leftMostOccur[i], rightMostOccur[i]))

        if countRemaining == 0:
            possibleArrangements.append((totalSum, mappedSize, -1, -1))

        bestVal, bestIndex, leftBoundary, rightBoundary = max(possibleArrangements)

        takenData = takenTree.treeData[
            takenTree.treeSize : takenTree.treeSize + takenTree.length
        ]
        remainData = remainTree.treeData[
            remainTree.treeSize : remainTree.treeSize + remainTree.length
        ]
        originalList = transformedList

        if bestIndex < mappedSize:

            changedLeft = False
            for i in range(leftBoundary):
                if takenData[i] < bestIndex or remainData[i] != -1:
                    changedLeft = True
                    takenData[i] = bestIndex
            if not changedLeft:

                wantIndexLeft = min(takenData[:leftBoundary])
                for i in range(leftBoundary):
                    if takenData[i] == wantIndexLeft:
                        takenData[i] = bestIndex
                        break

            changedRight = False
            for i in range(rightBoundary, arraySize):
                if takenData[i] < bestIndex or remainData[i] != -1:
                    changedRight = True
                    takenData[i] = bestIndex
            if not changedRight:
                wantIndexRight = min(takenData[rightBoundary:arraySize])
                for i in range(rightBoundary, arraySize):
                    if takenData[i] == wantIndexRight:
                        takenData[i] = bestIndex
                        break

        for i in range(arraySize):
            if takenData[i] == mappedSize:
                if isImportant[i]:
                    takenData[i] = originalList[i]

        finalList = [extendedList[valueIndex] for valueIndex in takenData]
        assert (
            sum(finalList) == bestVal
        ), "Final sum does not match the best arrangement."

        results.append(" ".join(map(str, finalList)))

    print("\n".join(results))


def main():
    """
    The main entry point.
    Reads input from stdin, processes all test cases, and prints the results.
    """
    solveAllTests()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/