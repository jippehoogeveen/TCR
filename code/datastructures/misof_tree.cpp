struct misof_tree {
	vvi cnt;
	int bits;
	misof_tree(int _bits) : bits(_bits) {
		cnt = vvi(bits, vi(1 << bits, 0)); }
	void change(int x, int d) {
		for (int i=0; i<bits; cnt[i++][x] += d, x >>= 1); }
	void insert(int x) { change(x,1); }
	void erase(int x) { change(x,-1); }
	int nth(int n) {
		int res = 0;
		for (int i = bits-1; i >= 0; i--)
			if (cnt[i][res <<= 1] <= n)
				n -= cnt[i][res], res++;
		return res; } };