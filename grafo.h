/*
 *  GRAFO.h - plantilla para los alumnos y alumnas de definicion de la clase GRAFO
 *
 *  Autores : Antonio Sedeno Noda, Sergio Alonso
 *  Cursos  : 2012-2021
 */

/**
 * @ASIGNATURA: Optimización
 * @ALUMNO: Eduardo González Gutiérrez
 * @CORREO: alu0101461588@ull.edu.es
 * @FECHA: 24/05/2022 
 */

/// GUARDS
#ifndef _GRAPH_H
#define _GRAPH_H

/// Librerías adjuntas
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

/// Constantes
const unsigned UERROR = 65000; /// Constante del ERROR 
const int maxint = 1000000; /// El entero máximo. 

/// Definicion de un elemento de la lista de adyacencia
typedef struct {
	unsigned j; /// Nodo
	int      c; /// Atributo para expresar los costes, pesos, las longitudes, las inversiones, etc...
} ElementoLista;

/// 
typedef struct {
  unsigned extremo1, extremo2;
  int peso;
} AristaPesada;

/// definicion del tipo de una lista de adyacencia de un nodo
/// LA_nodo = vector<ElementoLista> 
typedef vector<ElementoLista> LA_nodo;


class GRAFO {
  public:
  /// Constructores
  GRAFO(char nombrefichero[], int &errorapertura);
  /// Destructores
  ~GRAFO();
  /// Operaciones con ficheros  
  void actualizar (char nombrefichero[], int &errorapertura);
  /// Info, Checks, etc..
  unsigned Es_dirigido(); // devuelve 0 si el grafo es no dirigido y 1 si es dirigido
  void Info_Grafo(); // devuelve informaci�n b�sica del grafo
  /// Impresión por pantalla
   void MostrarListaSucesores();  
   void MostrarListaPredesores();  
   void MostrarListaAdyacencia();  
  /// Operaciones - Métodos 
  void RecorridoProfundidad(); //Construye un recorrido en profundidad desde un nodo inicial
  void RecorridoAmplitud(); //Construye un recorrido en amplitud desde un nodo inicial

  
  /// Vaiables
  unsigned            dirigido;  //0 si el grafo es no dirigido y 1 si es dirigido
  unsigned            n;         // Número de NODOS
  unsigned            m;         // Número de ARCOS
  vector<LA_nodo>     LS;        // Lista de adyacencia de los sucesores: es una matriz dónde cada fila posiblemente es posiblemente de distinto tama�o
  vector<LA_nodo>     LP;        // Lista de adyacencia de los predecesores: es una matriz dónde cada fila posiblemente es posiblemente de distinto tama�o
  vector<LA_nodo>     A;         // Matriz de adyacencia, tanto adyacencia como costes
  void destroy();                // Destructor del LS, A, y LP, en su caso
  void build (char nombrefichero[85], int &errorapertura); //Crea LS, A y LP en su caso, desde la lectura del fichero
  void dfs_num(unsigned i, vector<LA_nodo>  L, vector<bool> &visitado, vector<unsigned> &prenum, unsigned &prenum_ind, vector<unsigned> &postnum, unsigned &postnum_ind); //Recorrido en profundidad recursivo con recorridos enum y postnum
  void bfs_num(unsigned i, vector<LA_nodo>  L, vector<unsigned> &pred, vector<unsigned> &d); //Recorrido en amplitud con c�lculo de pred y d
  void Kruskal();
  void Prim();
  vector <AristaPesada> Aristas; // Vector de aristas, con costes
  vector <unsigned> Raiz;
  void QuickSort(std::vector<AristaPesada>& v);
  void Dijkstra();
  void MostrarCamino(unsigned s, unsigned i, vector<unsigned> pred);

};

#endif
