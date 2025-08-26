const char base = 'A';
const int sigma = 26;
struct suffixtree {
	string a;
	vvi t; vi l, r, p, s; // p: parent, s: suffix link
	int tv, tp, ts, la; // edge p[v] -> v, contains a[l[v]..r[v]-1]
	suffixtree(const string& _a) : a(_a) {
		int n = sz(a) * 2; t = vvi(n, vi(sigma, -1));
		t[1] = vi(sigma, 0); r = vi(n, sz(a));
		l = p = s = vi(n); l[0]=l[1]=-1;
		la = tv = tp = r[0] = r[1] = 0; s[0] = 1; ts = 2;
		for (; la < sz(a); la++) ukkadd(a[la] - base);
	}

	void ukkadd(int c) {
		if (r[tv] <= tp) {
			if (t[tv][c] == -1) {
				t[tv][c]=ts; l[ts]=la; p[ts++]=tv;
				tv=s[tv]; tp=r[tv]; ukkadd(c); return;
			}
			tv=t[tv][c]; tp=l[tv];
		}

		if (tp == -1 || c == a[tp]-base) { tp++; return; }

		l[ts+1]=la; p[ts+1]=ts;
		l[ts]=l[tv]; r[ts]=tp; p[ts]=p[tv];
		t[ts][c]=ts+1; t[ts][a[tp]-base]=tv;
		l[tv]=tp; p[tv]=ts; t[p[ts]][a[l[ts]]-base]=ts;
		tv=s[p[ts]]; tp=l[ts];
		while (tp < r[ts])
			tv = t[tv][a[tp]-base], tp += r[tv] - l[tv];
		if (tp == r[ts]) s[ts]=tv;
		else s[ts]=ts+2;
		tp = r[tv] - (tp - r[ts]); ts += 2; ukkadd(c);
	}
	ll max_substr(const string &S) { // O(|S|)
		int v = 0, it = 0, n = sz(S);
		while (it < n) {
			int c = S[it++] - base;
			if ((v = t[v][c]) < 0) return it - 1;
			for (int i = l[v]; it < n && ++i < r[v]; )
				if (S[it++] != a[i]) return it - 1;
		}
		return n;
	}
};