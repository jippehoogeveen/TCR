ll primitive_root(ll m) {
	vi div; ll phi = m - 1;
	for (ll i = 2; i*i <= phi; i++)
		if (phi % i == 0) {
			div.pb(i);
			div.pb(phi/i);
		}
	rep(x,2,m) {
		bool ok = true;//gcd-check
		for (ll d : div) if (mod_pow(x, d, m) == 1)
			{ ok = false; break; }
		if (ok) return x;
	}
	return -1;
}
