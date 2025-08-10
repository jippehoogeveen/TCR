ld gc_distance(ld pLat, ld pLong, ld qLat, ld qLong, ld r) {
	pLat *= PI / 180; pLong *= PI / 180;
	qLat *= PI / 180; qLong *= PI / 180;
	return r * acos(cos(pLat)*cos(qLat)*cos(pLong - qLong) + sin(pLat)*sin(qLat)); }