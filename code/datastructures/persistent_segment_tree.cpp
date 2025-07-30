typedef int T;
T combine(T l, T r) { return l + r; }

struct segment {
	int l, r, lid, rid;
	T val;
	segment(int _l, int _r) : l(_l), r(_r), val(0){}
};
vector<segment> S;

int build(int l, int r) {
	if (l > r) return -1;
	int id = sz(S);
	S.pb(segment(l,r));
	if(l != r) {
		int m = (l + r) / 2;
		S[id].lid = build(l , m);
		S[id].rid = build(m + 1, r);
	}
	return id;
}
int update(int idx, T v, int id) {//Make a[idx] = v
	if (id == -1) return -1;
	if (idx < S[id].l || idx > S[id].r) return id;
	int nid = sz(S);
	S.pb(segment(S[id].l, S[id].r));
	if(S[nid].l == S[nid].r)
		S[nid].val = v;
	else{
		int l = S[nid].lid = update(idx, v, S[id].lid);
		int r = S[nid].rid = update(idx, v, S[id].rid);
		S[nid].val = combine(S[l].val, S[r].val);
	}
	return nid;
}
T query(int id, int l, int r) {
	if (r < S[id].l || S[id].r < l) return 0;
	if (l<=S[id].l && S[id].r<=r) return S[id].val;
	return combine(query(S[id].lid,l,r),query(S[id].rid,l,r));
}