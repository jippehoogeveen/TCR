- Wat is een cartesian tree?
	Antw: een binaire boom waarbij elk vader lager ligt dan zijn kinderen en dfs op de boom de knopen in volgorde geeft. Voor zover ik gezien heb, gebeurt het soms dat je er een DP over moet doen over een Cartesian tree van punten (i, a[i]). De huidige code is daarvoor niet zo nuttig. Misschien willen we korte code maken voor construeren van zo'n boom?
- Bekijk Closest Points in detail
- Werk RMST bij naar compatibel met main code in geometry
- in Polygon isConvex bijwerken voor meerdere punten op 1 lijn!
- Tridiagonal Matrix geeft fouten!
- Heap is misschien niet zo nuttig?
- Dancing links is nu zo te zien gewoon een doubly linked list (die niet werkt als je x verwijderd, x->r verwijderd en x restored). Hij werkt nu met pointers en ik heb variant toegevoegd met vectors. Wat doen we ermee?
- Wat kan je met kd-tree (behalve nearest neighbor)?
- Wat kan je met huidige sqrt decomposition code?
- Wat doet de code IDA*? Hij werkt nu niet en ik heb geen idee wat voor input je erin moet gooien of wat voor output je eruit krijgt.
- Gomory-Hu Tree compileert niet goed met Dinic!
- Minimum Arborescence in O(EV) (versie 1) werkt niet altijd.
- Minimum Arborescence versie 2 kan misschien met vectors in plaats van arrays?
- Suffix array uitbreiden naar willekeurige antitrie?

Gecontroleerd:
	Sectie 1
	Sectie 2
	Sectie 3
	Sectie 4 tot en met 4.9

Acties:
	Dancing links
	Sqrt decomposition weg
	Simpele range tree
	Cartesian tree constructie met arrays
	Find cycle
	