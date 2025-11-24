// Problem: CF 2011 G - Removal of a Permutation
// https://codeforces.com/contest/2011/problem/G

/*
G. Removal of a Permutation
Algorithms/Techniques: Recursive decomposition with step tracking, simulation of operations on permutations.

Time Complexity: O(n * log n) per test case due to recursion depth and processing each element in steps.
Space Complexity: O(n) for storing arrays and recursion stack space.

The problem involves simulating removal operations on a permutation. In each operation,
we can remove elements based on increasing or decreasing adjacent pairs. The goal is to
compute how many operations it takes to remove each number (from 1 to n-1).

Approach:
- For each test case, process the permutation by simulating recursive operations.
- At each step, identify positions where an element is smaller than its successor (for removal in increasing order),
  and vice versa for decreasing order.
- Track the minimum steps needed for each position to be removed using a recursive DFS-like approach.

*/
fun next() = readLine()!!
fun nextInt() = next().toInt()
fun nextInts() = next().split(" ").map { it.toInt() }
var tx = IntArray(1000005)

fun main() {
    var T = nextInt()
    while (T > 0) {
        T -= 1
        var n = nextInt()
        var a = nextInts()
        var init = ArrayList<Int>()
        for (i in 0 until n) {
            init.add(a[i] - 1) // Convert to 0-based indexing
        }
        var MAX_STEP = 19
        var ans = IntArray(n - 1)
        for (i in 0 until (n - 1)) {
            ans[i] = MAX_STEP // Initialize with max possible steps
        }

        fun rec(arr: ArrayList<Int>, step: Int) {
            if (step >= MAX_STEP) {
                return
            }
            if (arr.size <= 1) {
                return
            }

            // Process increasing pairs: remove elements where arr[i] < arr[i+1]
            var lower = ArrayList<Int>()
            for (i in 0..(arr.size - 2)) {
                if (arr[i] < arr[i + 1]) {
                    ans[arr[i]] = minOf(ans[arr[i]], step + 1) // Mark this element as removed at 'step+1'
                } else {
                    lower.add(arr[i])
                }
            }
            lower.add(arr[arr.size - 1]) // Add last element to lower list
            rec(lower, step + 1)

            // Process decreasing pairs: remove elements where arr[i-1] > arr[i]
            var upper = ArrayList<Int>()
            upper.add(arr[0]) // Add first element to upper list
            for (i in 1..(arr.size - 1)) {
                if (arr[i - 1] > arr[i]) {
                    ans[arr[i]] = minOf(ans[arr[i]], step + 1) // Mark this element as removed at 'step+1'
                } else {
                    upper.add(arr[i])
                }
            }
            rec(upper, step + 1)
        }

        rec(init, 0)
        println(ans.joinToString(" "))
    }
}


// https://github.com/VaHiX/codeForces/