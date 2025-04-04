ll primitive_root(ll m) {
	vector<ll> div; ll phi = m - 1;
	for (ll i = 1; i*i < phi; i++)
		if (phi % i == 0) {
			if (i < phi) div.pb(i);
			if (phi/i < phi) div.pb(phi/i);
		}
	rep(x,2,m) {
		bool ok = true;
		for (ll d : div) if (mod_pow(x, d, m) == 1)
			{ ok = false; break; }
		if (ok) return x;
	}
	return -1;
}
