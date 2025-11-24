// Problem: CF 2128 A - Recycling Center
// https://codeforces.com/contest/2128/problem/A

/*
 * Problem: A. Recycling Center
 * 
 * Description:
 * In a recycling center, there are n trash bags with weights a_i. Each second,
 * two actions happen:
 * 1. Choose one bag to destroy - costs 0 coins if weight <= c, otherwise 1 coin.
 * 2. Multiply the weight of all remaining bags by 2.
 * Goal: Find minimum coins to destroy all bags.
 *
 * Algorithm/Techniques:
 * Greedy approach: At each step, always choose the smallest valid bag to destroy
 * (where weight <= c). If no such bag exists, destroy all remaining bags with cost
 * equal to their count (since all will be > c after the next multiplication).
 *
 * Time Complexity: O(n^2) - For each of up to n elements, we scan up to n elements.
 * Space Complexity: O(n) - Storing list of trash weights.
 */

using static System.Console;
int TestsCount = int.Parse(ReadLine());
int[] Coin = new int[TestsCount];
for (int i = 0; i < TestsCount; i++) {
  int[] Data = ReadLine().Split(' ').Select(int.Parse).ToArray();
  int n = Data[0];
  int c = Data[1];
  List<long> Trashes = ReadLine().Split(' ').Select(long.Parse).ToList();
  while (Trashes.Count > 0) {
    int sus = 0;
    bool cool = false;
    // Find first element which is <= c, mark it as candidate
    for (int j = 0; j < Trashes.Count; j++) {
      if (Trashes[j] <= c) {
        cool = true;
        sus = j;
        break;
      }
    }
    // If no such element found, all remaining bags must be destroyed for 1 coin each
    if (!cool) {
      Coin[i] += Trashes.Count;
      break;
    }
    // Find the smallest element <= c to destroy
    for (int j = 0; j < Trashes.Count; j++) {
      if (Trashes[j] > Trashes[sus] && Trashes[j] <= c) {
        sus = j;
      }
    }
    // Remove the selected bag and add cost if it was expensive
    Trashes.RemoveAt(sus);
    for (int j = 0; j < Trashes.Count; j++) {
      Trashes[j] *= 2; // Double weights of remaining bags
    }
  }
}
foreach (int n in Coin) {
  WriteLine(n);
}


// https://github.com/VaHiX/codeForces/