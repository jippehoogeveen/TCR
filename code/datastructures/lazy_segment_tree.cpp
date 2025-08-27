struct node {
	int k, r, x, lazy;
	node() {}
	node(int _l, int _r) : k(_l), r(_r), x(INT_MAX), lazy(0){}
	node(int _l, int _r, int _x) : node(_l,_r){x=_x;}
	node(node a,node b):node(a.k,b.r){x=min(a.x,b.x);}
	void update(int v) { x = v; }
	void range_update(int v) { lazy = v; }
	void apply() { x += lazy; lazy = 0; }
	void push(node &u) { u.lazy += lazy; }
};

struct segment_tree {
	int n;
	vector<node> arr;
	segment_tree() { }
	segment_tree(const vi &a) : n(sz(a)), arr(4*n) {
		mk(a,0,0,n-1); }
	node mk(const vi &a, int i, int k, int r) {
		int m = (k+r)/2;
		return arr[i] = k > r ? node(k,r) :
			k == r ? node(k,r,a[k]) :
			node(mk(a,2*i+1,k,m),mk(a,2*i+2,m+1,r));
	}
	node update(int at, ll v, int i=0) {
		propagate(i);
		int hl = arr[i].k, hr = arr[i].r;
		if (at < hl || hr < at) return arr[i];
		if (hl == at && at == hr) {
			arr[i].update(v); return arr[i]; }
		return arr[i] =
			node(update(at,v,2*i+1),update(at,v,2*i+2));
	}
	node query(int k, int r, int i=0) {
		propagate(i);
		int hl = arr[i].k, hr = arr[i].r;
		if (r < hl || hr < k) return node(hl,hr);
		if (k <= hl && hr <= r) return arr[i];
		return node(query(k,r,2*i+1),query(k,r,2*i+2));
	}
	node range_update(int k, int r, ll v, int i=0) {
		propagate(i);
		int hl = arr[i].k, hr = arr[i].r;
		if (r < hl || hr < k) return arr[i];
		if (k <= hl && hr <= r) {
			arr[i].range_update(v);
			propagate(i);
			return arr[i];
		}
		return arr[i] = node(range_update(k,r,v,2*i+1),
				range_update(k,r,v,2*i+2));
	}
	void propagate(int i) {
		if (arr[i].k < arr[i].r) {
			arr[i].push(arr[2*i+1]);
			arr[i].push(arr[2*i+2]);
		}
		arr[i].apply();
	}
};