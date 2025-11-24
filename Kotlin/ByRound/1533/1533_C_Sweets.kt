// Problem: CF 1533 C - Sweets
// https://codeforces.com/contest/1533/problem/C

/*
 * Purpose: Simulate a game where Anya eats sweets from a circle based on a rule involving
 *          skipping k sweets clockwise each turn. The goal is to count how many sweets
 *          she eats that she likes.
 *
 * Algorithm:
 *   - Use a mutable list to represent the remaining sweets.
 *   - Start at index 0 (first sweet) and remove it (eat it).
 *   - For the next round, count k sweets clockwise starting from the next sweet.
 *   - This is done using modular arithmetic: (current_index + k - 1) % size.
 *   - Continue until no sweets left that Anya likes.
 *
 * Time Complexity: O(n^2)
 *   - In the worst case, each sweet is removed once from the list.
 *   - Removing from a list is O(n) in the worst case (due to shifting elements).
 *   - Total is O(n) for the inner loop times O(n) outer loop = O(n^2).
 *
 * Space Complexity: O(n)
 *   - We store all n sweets in a list initially.
 *
 * Techniques:
 *   - Modular arithmetic for circular indexing
 *   - Simulation using a mutable list
 */

fun main() {
  repeat(readLine()!!.toInt()) {
    val (n, k) = readLine()!!.split(' ').map { it.toInt() }
    val s = readLine()!!.map { it == '1' }.toMutableList() // Convert string to boolean list indicating liked sweets
    var i = 0 // Start index for the current round
    while (s.any { it }) { // Continue while there are sweets Anya likes
      s.removeAt(i) // Eat the sweet at index i
      if (s.isNotEmpty()) i = (i + k - 1) % s.size // Calculate index of next sweet to eat
    }
    println(n - s.size) // Number of eaten sweets = total - remaining (which is 0)
  }
}


// https://github.com/VaHiX/CodeForces/