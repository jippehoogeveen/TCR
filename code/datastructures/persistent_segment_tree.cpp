typedef ll T;
T combine(T k, T r) { return k + r; }

struct segment {
	int k, r, lid, rid;
	T val;
	segment(int _l, int _r) : k(_l), r(_r), val(0){}
};
vector<segment> S;

int build(int k, int r) {
	if (k > r) return -1;
	int id = sz(S);
	S.pb(segment(k,r));
	if(k != r) {
		int m = (k + r) / 2;
		S[id].lid = build(k , m);
		S[id].rid = build(m + 1, r);
	}
	return id;
}
int update(int idx, T v, int id) {//Make a[idx] = v
	if (id == -1) return -1;
	if (idx < S[id].k || idx > S[id].r) return id;
	int nid = sz(S);
	S.pb(segment(S[id].k, S[id].r));
	if(S[nid].k == S[nid].r)
		S[nid].val = v;
	else{
		int k = S[nid].lid = update(idx, v, S[id].lid);
		int r = S[nid].rid = update(idx, v, S[id].rid);
		S[nid].val = combine(S[k].val, S[r].val);
	}
	return nid;
}
T query(int id, int k, int r) {
	if (r < S[id].k || S[id].r < k) return 0;
	if (k<=S[id].k && S[id].r<=r) return S[id].val;
	return combine(query(S[id].lid,k,r),query(S[id].rid,k,r));
}