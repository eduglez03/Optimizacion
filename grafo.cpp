 /*
 *  GRAFO.CPP - Plantilla para la implementaci�n de la clase GRAFOS
 *
 *
 *  Autores : Antonio Sedeno Noda, Sergio Alonso
 *  Cursos   : 2012-2021
 */

#include "grafo.h"



/**
 * @brief : Es un método que emplea el destructor de una clase.
 */
void GRAFO::destroy() {
  for (unsigned i = 0; i < n; i++) {
    LS[i].clear();
    if (dirigido == 1) {
      LP[i].clear();
    }
  }
  LS.clear();
  LP.clear();
}


/**
 * @brief : Es el constructor de la clase
 * @param nombrefichero : Es el nombre del fichero.
 * @param errorapertura : Hubo error de la apertura.
 */
void GRAFO::build (char nombrefichero[85], int &errorapertura) {
  ElementoLista  dummy;
  ifstream textfile;
  textfile.open(nombrefichero);
  if (textfile.is_open()) {
    unsigned i, j, k;
    /// leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
    textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
	  /// los nodos internamente se numeran desde 0 a n-1
    /// creamos las n listas de sucesores
	  LS.resize(n);
    LP.resize(n);

    /// leemos los m arcos
	  for (k = 0; k < m; k++) {
	    textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c;
      dummy.j = j - 1;     
      if (dirigido == 1) {
        LS.at(i - 1).push_back(dummy);
        dummy.j = i - 1;
        LP.at(j - 1).push_back(dummy);
      } else {
        LS.at(i - 1).push_back(dummy);
        dummy.j = i - 1;
        if (i != j) {
          LS.at(j - 1).push_back(dummy);
        }
      }

		//situamos en la posición del nodo i a dummy mediante push_back
	 	//pendiente de hacer un segundo push_back si es no dirigido. O no.
	 	//pendiente la construcción de LP, si es dirigido
		//...
    }
    errorapertura = 0;
  } else {
    errorapertura = 1;    
  }

}


/**
 * @brief Destructor de la clase.
 */
GRAFO::~GRAFO() {
  destroy();
}


/**
 * @brief Constructor de la clase
 * @param nombrefichero 
 * @param errorapertura 
 */
GRAFO::GRAFO(char nombrefichero[85], int &errorapertura) {
  build (nombrefichero, errorapertura);
}


/**
 * @brief : Este método borra el grafo y creo otro nuevo
 * @param nombrefichero 
 * @param errorapertura 
 */
void GRAFO::actualizar (char nombrefichero[85], int &errorapertura) {
  //Limpiamos la memoria dinamica asumida en la carga previa, como el destructor
  destroy();
  //Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
  build(nombrefichero, errorapertura);
}


/**
 * @brief : Este método chequea si un grafo es dirigido o no.
 * @return: 1 = es dirigido / 0 = no es dirigido.
 */
unsigned GRAFO::Es_dirigido() {
  return (dirigido == 1);
}



/**
 * @brief : Este método muestra información básica de un grafo
 */
void GRAFO::Info_Grafo() {
  cout << "El grafo es: ";
  dirigido == 1 ? cout << "DIRIGIDO" : cout << "NO DIRIGIDO";
  cout << '\n';
  cout << "El nº de nodos del grafo es :" << n << endl;
  cout << "El nº de arcos del grafo es :" << m << endl; 
}

/**
 * @brief Muestra la lista de sucesores
 */
void GRAFO::MostrarListaSucesores() {
    cout << "\n LISTA DE SUCESORES: \n";
  for (int counter = 0; counter < n; ++counter) {
    cout << counter + 1 << " : ";
    for (int counter2 = 0; counter2 < LS.at(counter).size(); ++counter2) {
      std::cout << LS.at(counter).at(counter2).j + 1 << "(" << LS.at(counter).at(counter2).c << ")" << " ";
    }
    std::cout << '\n';
  }    
}
/**
 * @brief Muestra la lista de predecesores
 */
void GRAFO::MostrarListaPredesores() {
    cout << "\n LISTA DE PREDECESORES: \n";
  for (int counter = 0; counter < n; ++counter) {
    cout << counter + 1 << " : ";
    for (int counter2 = 0; counter2 < LP.at(counter).size(); ++counter2) {
      std::cout << LP.at(counter).at(counter2).j + 1 << "(" << LP.at(counter).at(counter2).c << ")" << " ";
    }
    std::cout << '\n';
  }
} 

void GRAFO::MostrarListaAdyacencia() {
    cout << "\n LISTA DE ADYACENCIA: \n";
  for (int counter = 0; counter < n; ++counter) {
    cout << counter + 1 << " : ";
    for (int counter2 = 0; counter2 < LS.at(counter).size(); ++counter2) {
      std::cout << LS.at(counter).at(counter2).j + 1 << "(" << LS.at(counter).at(counter2).c << ")" << " ";
    }
    std::cout << '\n';
  }    
}
/**
 * @brief Recorrido en profundidad recursivo con recorridos enum y postnum
 * @param i 
 * @param L 
 * @param visitado 
 * @param prenum 
 * @param prenum_ind 
 * @param postnum 
 * @param postnum_ind 
 */
void GRAFO::dfs_num(unsigned i, vector<LA_nodo>  L, vector<bool> &visitado, vector<unsigned> &prenum, unsigned &prenum_ind, vector<unsigned> &postnum, unsigned &postnum_ind) {
	visitado[i] = true;
    prenum[prenum_ind++] = i + 1; // asignamos el orden de visita prenum que corresponde el nodo i
    for (unsigned j = 0; j < L[i].size(); j++) {
      if (!visitado[L[i][j].j]) {
        dfs_num(L[i][j].j, L, visitado, prenum, prenum_ind, postnum, postnum_ind);
      }
    }
    postnum[postnum_ind++] = i + 1; // asignamos el orden de visita postnum que corresponde al nodo i
    
}

void GRAFO::RecorridoProfundidad() {
  vector<bool> visitado(n, false);
  vector<unsigned> prenum(n);
  vector<unsigned> postnum(n);
  unsigned postnum_ind{0};
  unsigned prenum_ind{0};
  int nodo_inicial{0};
  std::cout << "Digite el nodo inicial: [1 - " << n << "]: ";
  std::cin >> nodo_inicial;
  dfs_num(nodo_inicial - 1, LS, visitado, prenum, prenum_ind, postnum, postnum_ind);
  std::cout << "\nOrden de visita en preorden:\n";
  std::cout << "[" << prenum[0] << "]"; 
  for (int counter = 1; counter < n; counter ++) {
    if (prenum[counter] != 0) {
      std::cout << " -> [" << prenum[counter] << "]";
    }
  }
  std::cout << "\n Orden de visita de los nodos en postorden:\n";
  std::cout << "[" << postnum[0] << "]"; 
  for (int counter = 1; counter < n; counter ++) {
    if (postnum[counter] != 0) {
      std::cout << " -> [" << postnum[counter] << "]";
    }
  }
  std::cout << "\n";
}

/**
 * @brief : Recorrido en amplitud con la construcción de pred y d: usamos la cola.
 * @param i : Nodo desde el que realizamos el recorrido en amplitud.
 * @param L : Lista que recorremos, LS o LP; por defecto LS.
 * @param pred :  Vector de predecesores en el recorrido
 * @param d : Vector dde distancias a nodo i + 1.
 */
void GRAFO::bfs_num(unsigned i, vector<LA_nodo>  L, vector<unsigned>& pred, vector<unsigned>& d) {
  vector<bool> visitado; //creamos e iniciamos el vector visitado
  visitado.resize(n, false);
  visitado[i] = true;

  pred.resize(n, 0); //creamos e inicializamos pred y d
  d.resize(n, 0);

  pred[i] = i + 1;
  d[i] = 0;

  queue<unsigned> cola; //creamos e inicializamos la cola
  cola.push(i);//iniciamos el recorrido desde el nodo i+1

  //al menos entra una vez al visitar el nodo i+1 y continua hasta que la cola se vacie
  while (!cola.empty()) {   
    unsigned k = cola.front(); //cogemos el nodo k+1 de la cola
    cola.pop(); //lo sacamos de la cola
    //Hacemos el recorrido sobre L desde el nodo k+1 
    for (int counter = 0; counter < L.at(k).size(); ++counter) {
      if (visitado.at(L.at(k).at(counter).j - 1) == false) {
        visitado.at(L.at(k).at(counter).j - 1) = true;
        cola.push(L.at(k).at(counter).j - 1);
        pred.at(L.at(k).at(counter).j - 1) = k + 1;
        d.at(L.at(k).at(counter).j - 1) = d.at(k) + 1; 
      }
    }  
    /*
      Recorremos todos los nodos u adyacentes al nodo k+1
      Si el nodo u no est� visitado
      Lo visitamos
      Lo metemos en la cola
      le asignamos el predecesor
      le calculamos su etiqueta distancia
    */
    /// Hemos terminado pues la cola está vacía
  }
}



/**
 * @brief : Realiza un recorrido en amplitud desde un nodo inicial.
 */
void GRAFO::RecorridoAmplitud() {
  vector<unsigned> pred;
  vector<unsigned> d;
  int nodo_inicial;
  std::cout << "\nDigite el nodo del que quiere iniciar el recorrido [1 - " << n << "]: ";
  std::cin >> nodo_inicial;
  std::cout << "\n";
  bfs_num((nodo_inicial - 1), LS, pred, d);  
  int d_max{0};
  
  for (int counter = 0; counter < n; counter++) {
    if (d[counter] > d_max) {
      d_max = d[counter];
    }
  }

  std::cout << "Nodos segun distancia al nodo inicial en numero de aristas\n";
  std::cout << "Distancia 0 aristas : " << nodo_inicial << endl;
  for (int counter = 1; counter <= d_max; ++counter) {
    std::cout << "Distancia " << counter << " aristas : ";    
    for(int counter2 = 0; counter2 < n; counter2++) {
      if (counter == d[counter2]) {
        std::cout << counter2 + 1 << " ";
      }
    }
    std::cout << "\n";
  }

  cout << "Lista de predecesores:\n";
  for (int i = 0; i < n; ++i) {
    if (pred[i] == 0) {
      cout << "Predecesor del nodo " << i + 1 << " : -" << endl;  
    } else {
      cout << "Predecesor del nodo " << i + 1 << " : " << pred.at(i) << endl;
    }
  }
}


void GRAFO::Kruskal() {
  /*Cargamos todas las aristas de la lista de adyacencia*/
  Aristas.resize(m);
  unsigned k = 0;
  for (unsigned i = 0; i<n; i++) {                       
    for (unsigned j=0; j<LS[i].size();j++) {
      if (i < LS[i][j].j) {
        Aristas[k].extremo1 = i;
        Aristas[k].extremo2 = LS[i][j].j;
        Aristas[k++].peso = LS[i][j].c;
      }
    }
  }

  /*Inicializamos el registro de componentes conexas: cada nodo está
  en su componente conexa*/
  Raiz.resize(n);
  for (unsigned q = 0;q < n; q++) {
    Raiz[q]=q;
  }
  AristaPesada arista_auxiliar;
  int head{0};
  int coste{0};
  int arista_counter{0};
  
  while (arista_counter < n - 1) {
    /// PARTIMOS DESDE LA CABEZA HASTA EL FINAL -> SI EL COSTE ES < SE ASIGNA A LA POSICIÓN HEAD, LA ARISTA
    for (int j = head; j < Aristas.size(); j++) {
      if (Aristas[j].peso < Aristas[head].peso) {
        arista_auxiliar = Aristas[head]; 
        Aristas[head] = Aristas[j];     
        Aristas[j] = arista_auxiliar;
      }
    }
    /// EN CASO DE QUE EN EL VECTOR RAIZ LOS EXTREMOS NO ESTÉN EN LA MISMA COMPONENTE CONEXA
    /// SE PONDRÁN EN LA MISMA COMPONENTE CONEXA, SE MOSTRARÁ LA ARISTA POR PANTALLA, Y A SU VEZ SE LE SUMARÁ AL COSTE.
    if (Raiz[Aristas[head].extremo1] != Raiz[Aristas[head].extremo2]) { 
      int aux_val =  Raiz[Aristas[head].extremo2];
      for (int counter = 0; counter < Raiz.size(); ++counter) {
        if (Raiz[counter] == aux_val) {
          Raiz[counter] = Raiz[Aristas[head].extremo1];
        }
      }
      coste += Aristas[head].peso;
      std::cout << "Arista numero " << arista_counter + 1 << " incorporada " << "(" << Aristas[head].extremo1 + 1 << ", " 
      << Aristas[head].extremo2 + 1  << "), " <<  "con peso " << Aristas[head].peso <<std::endl;
      arista_counter++;      
    }  
    head++;
  }
  /// SE MUESTRA EL COSTE DEL ARBOL GENERADOR MINIMO
  std::cout << "El peso del arbol generador minimo coste es " << coste << endl;

}  



void GRAFO::Dijkstra() {
  vector<bool> PermanentementeEtiquetado;
  vector<int> d;
  vector<unsigned> pred;
  int min;
  unsigned s, candidato;
  //Inicialmente no hay ningun nodo permanentemente etiquetado
  PermanentementeEtiquetado.resize(n,false);
  //Inicialmente todas las etiquetas distancias son infinito
  d.resize(n,maxint);
  //Inicialmente el pred es null
  pred.resize(n,UERROR);
  //Solicitamos al usuario nodo origen
  cout << endl;
  cout << "Caminos minimos: Dijkstra" << endl;
  cout << "Nodo de partida? [1-"<< n << "]: ";
  cin >> (unsigned &) s;
  //La etiqueta distancia del nodo origen es 0, y es su propio pred
  d[--s]=0; pred[s]=s;
  do {
    min = maxint;
    for (int i = 0; i < n; i++) {
      if (!PermanentementeEtiquetado[i] && d[i] < min) {
        min = d[i];
        candidato = i;
      }
    }
    PermanentementeEtiquetado[candidato] = true;
    
    for (int j = 0; j < LS[candidato].size();j++) {
      if (!PermanentementeEtiquetado[LS[candidato][j].j] && (LS[candidato][j].c + d[candidato]) < d[LS[candidato][j].j]) {
        d[LS[candidato][j].j] = LS[candidato][j].c + d[candidato];
        pred[LS[candidato][j].j] = candidato;
      }
    }
  // - Buscamos un nodo candidato a ser permanentemente etiquedado: aquel de
  // entre los no permanentemente etiquetados, es decir, en el almacén con menor
  // etiqueta distancia no infinita.
  // - Si existe ese candidato, lo etiquetamos permanentemente y usamos los arcos
  // de la lista de sucesores para buscar atajos.
  // - Esto lo hacemos mientras haya candidatos

  } while (min != maxint);

  for (int counter = 0; counter < pred.size(); counter++) {
    if (d[counter] != maxint) {
      if (counter != s) {
        std::cout << "El camino minimo desde " << s + 1 << " al nodo " << counter + 1 <<": ";
        MostrarCamino(s, counter, pred);
        std::cout << counter + 1;
        std::cout << " de longitud " << d[counter];
        std::cout << "\n";
      }
    } else {
      std::cout << "No existe camino desde el " << s + 1 << " al " << counter + 1 << std::endl;
    }
  }
}


void GRAFO::MostrarCamino(unsigned s, unsigned i, vector<unsigned> pred) {
  if (i != s) {
    MostrarCamino(s,pred[i],pred);
    cout << pred[i]+1 << " - ";
  }
}
