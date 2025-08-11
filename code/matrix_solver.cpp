typedef ld NUM;
const NUM EPS = 1e-5;
bool is0(NUM a) { return -EPS < a && a < EPS; }
// finds x such that Ax = b
// A_ij is M[i][j], b_i is M[i][m]
// 0 is no solution, 1 is unique, 2 is multiple
// peq is index of pivot equation
int solveM(int n, int m, vector<vector<NUM>> &M, vector<NUM> &val, vi &peq) {
	int pr = 0, pc = 0;
	while (pc < m) {
		//Pick first nonzero element (ld largest stabler)
		int r = pr, c;
		while (r < n && is0(M[r][pc])) r++;
		if (r == n) { pc++; continue; }
		for (c = 0; c <= m; c++)
			swap(M[pr][c], M[r][c]);
		r = pr++; c = pc++;
		NUM div = 1 / M[r][c]; //mult inv if mod
		for (int col = c; col <= m; col++)
			M[r][col] *= div;
		REP(row, n) {
			if (row == r) continue;
			// F2: if (M[row].test(c)) M[row] ^= M[r];
			NUM times = -M[row][c];
			for (int col = c; col <= m; col++)
				M[row][col] += times * M[r][col];
		}
	} // now M is in RREF

	for (int r = pr; r < n; r++)
		if (!is0(M[r][m])) return 0;
	peq = vi(m, -1);
	val = vector<NUM>(m, 0);
	for (int col = 0, row = 0; col < m && row < n; col++)
		if(!is0(M[row][col])) {
			peq[col] = row;
			val[col] = M[row][m];
			row++;
		}
	REP(i, m) if (peq[i] == -1) return 2;
	return 1; }