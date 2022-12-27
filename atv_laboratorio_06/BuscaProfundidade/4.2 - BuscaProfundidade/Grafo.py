# -*- coding: utf-8 -*-


# ​Autoria:
#     Fabiano S. Oliveira
#     Paulo E. D. Pinto
#
# ​A correção e a análise de complexidade deste programa
# encontram-se no livro
#
# Teoria Computacional de Grafos, Elsevier, 2018
# ​    ​Jayme L. Szwarcfiter


import math
import os
import subprocess

""" Version: v2.5 (livro Jayme) """

class Grafo(object):
	"""
	Classe base para as classes GrafoListaAdj e GrafoMatrizAdj
	"""	
	def __init__(self, orientado = False):
		"""
		Grafo se orientado=False ou Digrafo se orientado=True.
		"""
		self.n, self.m, self.orientado = None, None, orientado
		
	def DefinirN(self, n):
		"""
		Define o número n de vértices.
		"""	
		self.n, self.m = n, 0

	def V(self):
		"""
		Retorna a lista de vértices.
		"""
		for i in range(1,self.n+1):
			yield i

	def E(self, IterarSobreNo=False):
		"""
		Retorna lista de arestas uv, onde u é um inteiro e v é um inteiro se o grafo é GrafoMatrizAdj
		ou IterarSobreNo=False; v é GrafoListaAdj.NoAresta, caso contrário.
		"""
		for v in self.V():
			for w in self.N(v, Tipo = "+" if self.orientado else "*", IterarSobreNo=IterarSobreNo):
				enumerar = True
				if not self.orientado:
					wint = w if isinstance(w, int) else w.Viz
					enumerar = v < wint
				if enumerar:
					yield (v, w)		

class GrafoMatrizAdj(Grafo):

	def DefinirN(self, n):
		"""
		Define o número n de vértices.
		"""	
		super(GrafoMatrizAdj, self).DefinirN(n)
		self.M = [None]*(self.n+1)
		for i in range(1, self.n+1):
			self.M[i] = [0]*(self.n+1)
			
	def RemoverAresta(self, u, v):
		"""
		Remove a aresta uv.
		"""
		self.M[u][v] = 0
		if not self.orientado:
			self.M[v][u] = 0 
		self.m = self.m-1		

	def AdicionarAresta(self, u, v):
		"""
		Adiciona aresta uv.
		"""
		self.M[u][v] = 1 
		if not self.orientado:
			self.M[v][u] = 1
		self.m = self.m+1		
			
	def SaoAdj(self, u, v):
		"""
		Retorna True se e somente se uv é uma aresta.
		"""
		return self.M[u][v] == 1

	def N(self, v, Tipo = "*", Fechada=False, IterarSobreNo=False):
		"""
		Retorna lista de vértices vizinhos do vértice v. Se Fechada=True, o próprio v é incluido na lista.
		Tipo="*" significa listar todas as arestas incidentes em v. Se G é orientado, 
		Tipo="+" (resp. "-") significa listar apenas as arestas de saída (resp. entrada) de v.
		IterarSobreNo não tem uso para Matriz de Adjacências.
		"""
		if Fechada:
			yield v
		w = 1
		t = "+" if Tipo == "*" and self.orientado else Tipo
		while w <= self.n:
			if t == "+":
				orig, dest, viz = v, w, w
			else:
				orig, dest, viz = w, v, w
			if self.SaoAdj(orig, dest):
				yield w
			w = w+1
			if w > self.n and t == "+" and Tipo == "*":
				t, w = "-", 1	


class GrafoListaAdj(Grafo):
	class NoAresta(object):
		"""
		Objeto nó da lista de adjacência.
		Atributos:
		- Viz (vizinho)
		- e (Aresta)
		- Prox (próxima aresta na lista de adjacência)
		- Ant (aresta anterior na lista de adjacência (se a lista for duplamente encadeada))
		"""	

		def __init__(self):
			self.Viz = None
			self.e = None
			self.Prox = None

	class Aresta(object):
		"""
		Objeto único para representar a aresta.
		Atributos:
		- v1, No1 (um dos vértices desta aresta e seu respectivo nó, isto é, v1 == No1.Viz)
		- v2, No2 (análogo em relação ao segundo vértice)
		"""
		def __init__(self):
			self.v1, self.No1 = None, None
			self.v2, self.No2 = None, None

	def DefinirN(self, n, VizinhancaDuplamenteLigada=False):
		"""
		Define o número n de vértices.
		Se VizinhancaDuplamenteLigada=True, a lista encadeada dos vizinhos de um vértice é duplamente ligada (permitindo remoção de arestas de tempo constante). 
		"""	
		super(GrafoListaAdj, self).DefinirN(n)
		self.L = [None]*(self.n+1)
		for i in range(1,self.n+1):
			self.L[i] = GrafoListaAdj.NoAresta() #nó cabeça
		self.VizinhancaDuplamenteLigada = VizinhancaDuplamenteLigada

	def AdicionarAresta(self, u, v):
		"""
		Adiciona aresta uv.
		"""
		def AdicionarLista(u,v,e,Tipo):
			No = GrafoListaAdj.NoAresta()
			No.Viz, No.e, No.Prox, self.L[u].Prox = v, e, self.L[u].Prox, No
			if self.VizinhancaDuplamenteLigada:
				self.L[u].Prox.Ant = self.L[u]
				if self.L[u].Prox.Prox != None:				
					self.L[u].Prox.Prox.Ant = self.L[u].Prox
			if self.orientado:
				No.Tipo = Tipo
			return No

		e = GrafoListaAdj.Aresta()
		e.v1, e.v2 = u, v
		e.No1 = AdicionarLista(u,v,e,"+")
		e.No2 = AdicionarLista(v,u,e,"-")
		self.m = self.m+1
		return e


	def RemoverAresta(self, uv):
		"""
		Remove a aresta uv.
		"""
		def RemoverLista(No):
			No.Ant.Prox = No.Prox
			if No.Prox != None:
				No.Prox.Ant = No.Ant
		RemoverLista(uv.No1)
		RemoverLista(uv.No2)

	def SaoAdj(self, u, v):
		"""
		Retorna True se uv é uma aresta e False, caso contrário.
		"""
		Tipo = "+" if self.orientado else "*"
		for w in self.N(u, Tipo):
			if w == v:
				return True
		return False

	def N(self, v, Tipo = "*", Fechada=False, IterarSobreNo=False):
		"""
		Retorna lista de Grafo.NoAresta representando os vizinhos do vértice v. 
		Se Fechada=True, o próprio v é incluido na lista.
		Tipo="*" significa listar todas as arestas incidentes em v. Se G é orientado, 
		Tipo="+" (resp. "-") significa listar apenas as arestas de saída (resp. de entrada) de v.
		IterarSobreNo=False indica que a lista de vizinhos deve constituir da lista de vértices. Caso
		contrário, a lista é dos nós da lista encadeada de vizinhos (NoAresta).
		"""
		if Fechada:
			No = GrafoListaAdj.NoAresta()
			No.Viz, No.e, No.Prox = v, None, None
			yield No if IterarSobreNo else No.Viz
		w = self.L[v].Prox
		while w != None:
			if Tipo == "*" or w.Tipo == Tipo:
				yield w if IterarSobreNo else w.Viz
			w = w.Prox
			
			
			
			
			
