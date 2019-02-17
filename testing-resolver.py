import os, sys

from ZarateResolverNreinas import resolver

def test_resolver():
	assert resolver(4) == [[1,3,0,2]]
	assert resolver(5) == [[0,2,4,1,3]]
	assert resolver(7) == [[0,2,4,6,1,3,5]]
	assert resolver(16) == [[0,2,4,1,12,8,13,11,14,5,15,6,3,10,7,9]]
