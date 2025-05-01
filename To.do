- isOverflown testen (gedaan, kan alleen met add of mul of sub als functie)
- Zoek precisie uit van Numeric Integration (gedaan, Simpson heeft een precisie van EPS^4 voor een vast interval en EPS^5 voor een interval van lengte EPS)
- Voeg uitleg toe van Fast Hadamard Transform
	(code verbeterd, waardoor je nu een simpele convolutiefunctie hebt (zoals bij FFT)).
- Voeg wat standaard primitive roots toe 
	10^9 + 7 : 5
	10^9 + 9 : 13
	10^9 + 21 : 2
	10^9 + 33 : 5
	10^9 + 87 : 3
	36028797018963971 : 2
	(10^9 + 7)^2 : 5
- Probeer fast subset convolution
	Volgens mij wordt het b_i = \sum_{j & i = j} a_j in plaats van b_i = \sum_{j & i = i} a_j. Past rij a aan tot rij b. De inverse code maakt vervolgens van rij b weer rij a.
- Zoek gnu order tree uit en maak duidelijkere code
	De order set kan elementen toevoegen (insert) en verwijderen (erase). Vervolgens kan hij het i-de element teruggeven (find_by_order) en bepalen hoeveel elementen strikt kleiner zijn dan een gegeven element (order_of_key). De volgorde was van groot naar klein en die is omgedraaid. 
- Wat is een cartesian tree?
