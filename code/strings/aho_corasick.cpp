const int sigma = 26;
const char base = 'a';
vi pnr, ploc, sLink, dLink;
vvi to;
vs P;
void makeNode() {
	pnr.pb(-1); sLink.pb(0);
	dLink.pb(0); to.pb(vi(sigma,0));
}
void makeTrie(vs& p) {
	// STEP 1: MAKE A TREE
	P = p;
	pnr.clear(),sLink.clear(),dLink.clear();
    to.clear(),ploc.clear();
	makeNode();
	for (int i = 0; i < sz(p); i++) {
		int cur = 0;
		for (char c : p[i]) {
			int i = c - base;
			if (to[cur][i] == 0) {
				makeNode();
				to[cur][i] = sz(to) - 1;
			}
			cur = to[cur][i];
		}
		pnr[cur] = i; ploc.pb(cur);
	}
	// STEP 2: CREATE SUFFIX_LINKS AND DICT_LINKS
	queue<int> q; q.push(0);
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		for (int c = 0; c < sigma; c++) {
			if (to[cur][c]) {
				int sl = sLink[to[cur][c]] = cur == 0 ? 0 : to[sLink[cur]][c];
				// if all strings have equal length, remove this:
				dLink[to[cur][c]] = pnr[sl] >= 0 ? sl : dLink[sl];
				q.push(to[cur][c]);
			} else to[cur][c] = to[sLink[cur]][c];
		}
	}
}
void traverse(string& s) {
	for (int cur = 0, i = 0, n = sz(s); i < n; i++) {
		cur = to[cur][s[i] - base];
		for (int hit = pnr[cur] >= 0 ? cur : dLink[cur]; hit; hit = dLink[hit]) {
			cerr << P[pnr[hit]] << " found at [" << (i + 1 - P[pnr[hit]].size()) << ", " << i << "]" << endl;
		}
	}
}