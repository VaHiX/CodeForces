// Problem: CF 2133 B - Villagers
// https://codeforces.com/contest/2133/problem/B

/*
B. Villagers

Algorithm:
This problem involves connecting all villagers into one friendship component by pairing them optimally.
The key insight is to greedily pair the highest grumpiness villagers to minimize total emeralds spent.
We sort the grumpiness values in descending order and then take every second element (starting from index 0).
Each selected villager contributes their grumpiness value to the total emeralds needed.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the array

Problem: Minimize emeralds spent to make all villagers friends.
Techniques: Greedy algorithm with sorting.
*/

fun solve() {
    val n = readLine()!!.toInt()
    val arr = readLine()!!.split(" ").map {
        it.toInt()
    }.sortedDescending() // Sort grumpiness in descending order
    var ans = 0L
    for (i in 0 until n step 2) { // Take every second element starting from index 0
        ans += arr[i] // Add the grumpiness of selected villager
    }
    println(ans)
}

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        solve()
    }
}


// https://github.com/VaHiX/codeForces/