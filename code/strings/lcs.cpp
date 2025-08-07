vvi dp; // DP problem

int lcs(const string &w1, const string &w2) {
	int n1 = w1.size(), n2 = w2.size();
	dp = vvi(n1 + 1,vi(n2 + 1,0));
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++) {
			if (w1[i] == w2[j])
				dp[i + 1][j + 1] = dp[i][j]+1;
			else dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
		}
	}
	return dp[n1][n2];
}

// backtrace
string getLCS(const string &w1, const string &w2) {
	int i = w1.size(), j = w2.size(); string ret = "";
	while (i > 0 && j > 0) {
		if (w1[i - 1] == w2[j - 1]) ret += w1[--i], j--;
		else if (dp[i][j - 1] > dp[i - 1][j]) j--;
		else i--;
	}
	reverse(ret.begin(), ret.end());
	return ret;
}