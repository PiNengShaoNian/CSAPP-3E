int print_times(int n) {
   int *dp = (int*)malloc(sizeof(int) * (n + 1));
   //dp[i]表示当n为i时打印的条数
   dp[0] = 1;
   for(int i = 1; i <= n; ++i) {
      dp[i] = 1;
      for(int j = 0; j < i; ++j) {
         dp[i] += dp[j];
      }
   }

   return dp[n];
}


//从上面的打印次数计算程序不难看出当fork次数为n时打印次数dp[n] = 1 + dp[n - 1] + ... + dp[1] + dp[0]  
//其中n>=3,dp[n + 1] = 1 + dp[n] + dp[n - 1] + ... + dp[0]
//所以dp[n + 1] - dp[n] = 1 + dp[n - 1] + ... + dp[0]
//                      = dp[n]
//所以dp[n + 1] = 2 * dp[n]
//且dp[0] = 1,由此可得dp[n] = 2 ^ n

