
# ​Autoria:
#     Fabiano S. Oliveira
#     Paulo E. D. Pinto
#
# ​A correção e a análise de complexidade deste programa
# encontram-se no livro
#
# Teoria Computacional de Grafos, Elsevier, 2018
# ​    ​Jayme L. Szwarcfiter

#Algoritmo 4.2: Busca em Profundidade

from Grafo import GrafoMatrizAdj
from Grafo import GrafoListaAdj

def Visitar(v, w):
	print("visitado ({0},{1})".format(v, w))
	
#Dado: grafo conexo G
def BuscaProfundidade(G):
	def P(v):
		G.Marcado[v], G.EmQ[v] = True, True
		Q.append(v)
		for w in G.N(v):
			if not G.Marcado[w]:
				Visitar(v, w) 		#arestas visitadas (I)
				P(w)
			else:
				if G.EmQ[w] and w != Q[-2]:
					Visitar(v, w)	#arestas visitadas (II)
		G.EmQ[v] = False		
		Q.pop()

	G.Marcado, G.EmQ = [False]*(G.n+1), [False]*(G.n+1)
	Q = []
	s = 1
	P(s)

for i in range(2):
	if i == 0:
		print("Exemplo Matriz de Adjacencia")
		G = GrafoMatrizAdj(orientado = False)
	else:
		print("Exemplo Lista de Adjacencia")
		G = GrafoListaAdj(orientado = False)

	G.DefinirN(6)
	G.AdicionarAresta(1,2)
	G.AdicionarAresta(1,4)
	G.AdicionarAresta(1,5)
	G.AdicionarAresta(1,6)
	G.AdicionarAresta(2,3)
	G.AdicionarAresta(2,4)
	G.AdicionarAresta(3,4)
#	G.AdicionarAresta(3,5)
	G.AdicionarAresta(4,5)
	G.AdicionarAresta(5,6)

	BuscaProfundidade(G)

	print()

