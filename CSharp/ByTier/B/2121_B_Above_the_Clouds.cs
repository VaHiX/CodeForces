internal class Program
{
    struct LR
    {
        public int l;
        public int r;
    }
    private static void Main(string[] args)
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            List<int> hi_1 = new List<int>() { 0 };
            int n = int.Parse(Console.ReadLine());
            bool flagExit = false;
            string s = Console.ReadLine();
            

            for (int i = 1; i < n - 1; i++) 
            {
                char elem = s[i];
                string temp_s = s.Remove(i, 1);
                if(temp_s.IndexOf(elem) != -1)
                {
                    flagExit = true;
                    break;
                }
            }
            if (flagExit) 
            {
                Console.WriteLine("YES");
            }
            else
            {
                Console.WriteLine("NO");
            }
        }
    }
}