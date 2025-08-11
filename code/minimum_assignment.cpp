//a[i][j] gives value for 1 <= i <= n and 1 <= j <= m (1-based!)
//pm[j] gives assigned i and pn[i] assigned j
ll minimum_assignment(int n, int m, vvi& a, vi& pm, vi& pn) {
	vi u(n + 1), v(m + 1), way(m + 1); pm = vi(m + 1);
	for (int i = 1; i <= n; i++) {
		pm[0] = i;
		int j0 = 0;
		vi mv(m + 1, INT_MAX);
		vb used(m + 1, false);
		do {
			used[j0] = true;
			int i0 = pm[j0], delta = INT_MAX, j1;
			for (int j = 1; j <= m; j++)
				if (!used[j]) {
					int cur = a[i0][j] - u[i0] - v[j];
					if (cur < mv[j]) mv[j] = cur, way[j] = j0;
					if (mv[j] < delta) delta = mv[j], j1 = j;
				}
			for (int j = 0; j <= m; j++) {
				if(used[j]) u[pm[j]] += delta, v[j] -= delta;
				else mv[j] -= delta;
			}
			j0 = j1;
		} while (pm[j0] != 0);
		do {
			int j1 = way[j0]; pm[j0] = pm[j1]; j0 = j1;
		} while (j0);
	}
	pn = vi(n + 1); rep(i, 1, m + 1) pn[pm[i]] = i;
	return -v[0];
}