// Problem: CF 1211 F - kotlinkotlinkotlinkotlin...
// https://codeforces.com/contest/1211/problem/F

/*
 * Problem: Reorder strings to form a sequence of "kotlin"
 * Algorithm: Eulerian Path Finding using Hierholzer's Algorithm
 * 
 * Approach:
 * 1. Each string is categorized by its starting character and ending character
 *    - 'k' -> 0, 'o' -> 1, 't' -> 2, 'l' -> 3, 'i' -> 4, 'n' -> 5
 * 2. For each string, we store its start and end state (0-5)
 * 3. Build a graph where edge from state 'a' to state 'b' represents a string
 *    that starts at 'a' and ends at 'b'
 * 4. Find Eulerian Path using Hierholzer's algorithm
 * 
 * Time Complexity: O(n) where n is number of strings
 * Space Complexity: O(n) for storing graph and auxiliary arrays
 */

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readDouble() = readLn().toDouble()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }
private fun readDoubles() = readStrings().map { it.toDouble() }

fun main(args: Array<String>) {
  var m = readInt() // number of strings
  var from = IntArray(m) // from state for each string
  var to = IntArray(m) // to state for each string
  for (i in 0..m - 1) { // process each string
    var s = readLn()
    from[i] = 0
    if (s[0] == 'o') from[i] = 1
    if (s[0] == 't') from[i] = 2
    if (s[0] == 'l') from[i] = 3
    if (s[0] == 'i') from[i] = 4
    if (s[0] == 'n') from[i] = 5
    to[i] = (from[i] + s.length) % 6 // compute to state
  }
  var n = 6 // number of states (k,o,t,l,i,n)
  val g = Array<MutableList<Int>>(n, { i -> mutableListOf() }) // adjacency list
  for (i in 0 until m) {
    g[from[i]].add(i) // build graph
  }
  val used = BooleanArray(m) // track used edges
  val ptr = IntArray(n) // pointer for each state
  val res = IntArray(m) // result array
  var write_ptr = m // pointer for writing result
  var stack_ptr = 0 // stack pointer for DFS
  for (root in 0 until n) { // check all components
    var v = root
    while (true) {
      var found = false
      while (ptr[v] < g[v].size) { // traverse edges from state v
        var id = g[v][ptr[v]++] // get next edge
        if (used[id]) { // skip if already used
          continue
        }
        used[id] = true // mark as used
        res[stack_ptr++] = id // add to stack
        // update state: v = v XOR from[id] XOR to[id]
        // This updates the state based on string's direction
        v = v xor from[id] xor to[id]
        found = true
        break
      }
      if (!found) { // if no more edges from v
        if (stack_ptr == 0) { // if stack is empty, we're done
          break
        }
        var id = res[--stack_ptr] // pop from stack
        res[--write_ptr] = id // place in result
        v = v xor from[id] xor to[id] // update state
      }
    }
  }
  for (i in 0..m - 1) res[i]++ // convert to 1-indexed
  println(res.joinToString(" "))
}


// https://github.com/VaHiX/CodeForces/