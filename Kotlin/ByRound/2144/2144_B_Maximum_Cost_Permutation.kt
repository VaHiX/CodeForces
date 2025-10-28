// Problem: CF 2144 B - Maximum Cost Permutation
// https://codeforces.com/contest/2144/problem/B

/*
B. Maximum Cost Permutation
Algorithms/Techniques: Greedy, Sorting, Set operations

Time Complexity: O(n log n) per test case due to sorting and set operations
Space Complexity: O(n) for storing the array and auxiliary data structures

Recall that a permutation of length n is a sequence of length n such that each integer from 1 to n appears in it exactly once.
Let's define the cost of a permutation as the minimum length of its contiguous subsegment (possibly empty) that needs to be sorted so that the entire permutation becomes sorted in ascending order.
You are given an integer array p consisting of integers from 0 to n, where no positive (strictly greater than zero) integer appears more than once. You should replace zeros with integers so that the array p becomes a permutation.
Your task is to calculate the maximum possible cost of the resulting permutation.

Input:
The first line contains a single integer t (1 ≤ t ≤ 10^4) — the number of test cases.
The first line of each test case contains a single integer n (1 ≤ n ≤ 2*10^5).
The second line contains n integers p_1, p_2, ..., p_n (0 ≤ p_i ≤ n). No positive integer appears more than once in this sequence.
Additional constraint on the input: the sum of n over all test cases doesn't exceed 2*10^5.

Output:
For each test case, print a single integer — the maximum possible cost of the resulting permutation.
*/

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val n = readLine()!!.toInt()
        val p = readLine()!!.split(" ").map { it.toInt() }.toMutableList()
        val used = mutableSetOf<Int>()
        for (num in p) {
            if (num != 0) used.add(num)
        }
        val missing = mutableListOf<Int>()
        for (i in n downTo 1) {
            if (!used.contains(i)) {
                missing.add(i)
            }
        }
        var j = 0
        for (i in 0 until n) {
            if (p[i] == 0) {
                p[i] = missing[j] // Replace zeros with unused numbers to form permutation
                j++
            }
        }
        val sortedP = p.sorted()
        var l = 0
        while (l < n && p[l] == sortedP[l]) l++ // Find leftmost position where elements differ
        var r = n - 1
        while (r >= 0 && p[r] == sortedP[r]) r-- // Find rightmost position where elements differ
        val cost = if (r >= l) r - l + 1 else 0 // Cost is the length of differing segment
        println(cost)
    }
}


// https://github.com/VaHiX/codeForces/