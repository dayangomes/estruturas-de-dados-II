
# ​Autoria:
#     Fabiano S. Oliveira
#     Paulo E. D. Pinto
#
# ​A correção e a análise de complexidade deste programa
# encontram-se no livro
#
# Teoria Computacional de Grafos, Elsevier, 2018
# ​    ​Jayme L. Szwarcfiter

#Algoritmo 4.6: Busca em Largura

from Grafo import GrafoMatrizAdj
from Grafo import GrafoListaAdj
from collections import deque

def Visitar(v, w):
	print("visitado ({0},{1})".format(v, w))
	
def BuscaLargura(G):
	"""G: grafo conexo"""
	G.Marcado, G.EmQ = [False]*(G.n+1), [False]*(G.n+1)
	s = 1
	Q = deque()
	G.Marcado[s], G.EmQ[s] = True, True
	Q.append(s)
	while len(Q) > 0:
		v = Q[0]
		for w in G.N(v):
			if not G.Marcado[w]:
				Visitar(v, w) 		#arestas visitadas (I)
				G.Marcado[w], G.EmQ[w] = True, True
				Q.append(w)
			else:
				if G.EmQ[w]:
					Visitar(v, w)	#arestas visitadas (II)
		G.EmQ[v] = False
		v = Q.popleft()

for i in range(2):
	if i == 0:
		print("Exemplo Matriz de Adjacencia")
		G = GrafoMatrizAdj(orientado = False)
	else:
		print("Exemplo Lista de Adjacencia")
		G = GrafoListaAdj(orientado = False)
	
	for j in range(2):
		if j==0:
			G.DefinirN(6)
			E = [(1,2),(1,4),(1,5),(1,6),(2,3),(2,4),(3,4),(4,5),(5,6)]
		else:
			G.DefinirN(13)
			E = [(1,2),(1,3),(2,4),(2,6),(6,10),(6,3),(10,5),(10,11),(10,13),(3,5),(3,7),(3,8),(5,11),(5,12),(11,12),(9,11),(9,13),(8,13)]
		for (u,v) in E:
			G.AdicionarAresta(u,v)

		BuscaLargura(G)

		print()


