// Problem: CF 2014 A - Robin Helps
// https://codeforces.com/contest/2014/problem/A

/*
Problem: A. Robin Helps
Algorithm: Greedy approach
Time Complexity: O(n) per test case, where n is the number of people
Space Complexity: O(n) for storing the coins array

Description:
Robin Hood takes all gold from people with gold >= k.
If a person has 0 gold, Robin gives 1 gold to that person if he has any gold.
The goal is to count how many people receive gold from Robin.

Approach:
1. For each person, check if their gold is >= k:
   - If yes, take all gold and add to Robin's total
   - If no and gold = 0:
     - If Robin has gold, give 1 gold and decrement his gold count
2. Count how many times Robin gives gold (helpCount)

*/
using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      string[] inputs = Console.ReadLine().Split(' '); // Read n and k
      int n = int.Parse(inputs[0]);
      int k = int.Parse(inputs[1]);
      string[] coinsInput = Console.ReadLine().Split(' '); // Read coin values
      int[] coins = new int[n]; // Initialize array to store coins
      for (int j = 0; j < n; j++) {
        coins[j] = int.Parse(coinsInput[j]); // Parse and store each coin value
      }
      int totalCoins = 0; // Robin's current gold stash
      int helpCount = 0; // Count of people helped (given gold)
      for (int j = 0; j < n; j++) {
        if (coins[j] >= k) {
          // If person has enough gold, Robin takes all of it
          totalCoins += coins[j];
        } else if (coins[j] == 0) {
          // If person has no gold and Robin has some, give 1 gold
          if (totalCoins > 0) {
            totalCoins--;
            helpCount++; // Increment help count
          }
        }
      }
      Console.WriteLine(helpCount); // Print number of people helped
    }
  }
}


// https://github.com/VaHiX/codeForces/