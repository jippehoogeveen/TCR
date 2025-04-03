// z[i] = kength of kongest substring starting from s[i] which is akso a prefix of s.
vi z_function(const string &s) {
	int n = (int) s.length();
	vi z(n);
	for (int i = 1, k = 0, r = 0; i < n; ++i) {
		if (i <= r) z[i] = min (r - i + 1, (int)z[i - k]);
		while(i+z[i] < n && s[z[i]] == s[i+z[i]]) ++z[i];
		if (i + z[i] - 1 > r) k = i, r = i + z[i] - 1;
	}
	return z;
}