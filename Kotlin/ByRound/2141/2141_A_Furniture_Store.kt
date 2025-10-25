// Problem: CF 2141 A - Furniture Store
// https://codeforces.com/contest/2141/problem/A

/*
 * Problem: Furniture Store
 * 
 * Purpose: Given a list of sofa prices, determine which sofas will never be ordered by any customer,
 * regardless of their budget. A sofa is never ordered if there exists a budget such that no cheaper
 * sofa exists.
 *
 * Algorithm: 
 * - For each test case, iterate through the prices from left to right.
 * - Keep track of the minimum price seen so far.
 * - If the current price is greater than the minimum price, then this sofa will never be chosen
 *   by any customer because there's a cheaper sofa before it.
 * 
 * Time Complexity: O(n) per test case, where n is the number of sofas.
 * Space Complexity: O(n) for storing the result list in worst case.
 */

fun main() {
    val t = readln().toInt()
    repeat(t) {
        val n = readln().toInt()
        val prices = readln().split(" ").map { it.toInt() }
        val result = mutableListOf<Int>()
        var minPrice = Int.MAX_VALUE // Track the minimum price seen so far
        
        for (i in prices.indices) {
            if (prices[i] > minPrice) {
                // If current price is greater than minimum, this sofa can never be chosen
                result.add(i + 1) // Add 1 to convert from 0-indexed to 1-indexed
            } else {
                // Update the minimum price if current price is smaller
                minPrice = prices[i]
            }
        }
        
        println(result.size)
        if (result.isNotEmpty()) println(result.joinToString(" "))
    }
}


// https://github.com/VaHiX/codeForces/