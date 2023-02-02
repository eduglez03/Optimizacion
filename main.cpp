 /*
 *  Programa principal.
 *
 *
 *               Autores : Antonio Sedeno Noda, Sergio Alonso.
 *               Cursos  : 2012-2021
 */
#include "grafo.h"

//Expresion del menu de opciones segun sea un grafo dirigido o no dirigido
void menu (unsigned dirigido, char &opcion) {
  cout << "Optimiza!cion en Grafos, 2021-2022 Eduardo González Gutiérrez" << endl;
  cout << "c. [c]argar grafo desde fichero" << endl;
  if (dirigido == 0) { //Grafo no dirigido
    cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
    cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
    cout << "m. Realizar un recorrido en a[m]plitud del grafo desde un nodo" << endl;
    cout << "r. Realizar un recorrido en p[r]ofundidad del grafo desde un nodo" << endl;
    cout << "k. [k]rukal" << endl;
	//Aqu� se a�aden m�s opciones al men� del grafo no dirigido
  } else {
    cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
    cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
    cout << "p. Mostrar la lista de [p]redecesores del grafo" << endl;
    cout << "m. Realizar un recorrido en a[m]plitud del grafo desde un nodo por sucesores" << endl;
    cout << "r. Realizar un recorrido en p[r]ofundidad del grafo desde un nodo por sucesores" << endl;
    cout << "j. D[j]istra" << endl;


	//Aqu� se a�aden m�s opciones al men� del grafo dirigido
  }
  cout << "q. Finalizar el programa" << endl;
  cout << "Introduce la letra de la accion a ejecutar  > ";
  cin >> opcion;
}


/// El principal es simplemente un gestor de menu, diferenciando acciones para dirigido y para no dirigido, y un men� inicial si no hay un grafo cargado
int main(int argc, char *argv[]) {
  int error_apertura;
  char nombrefichero[85], opcion;
//  //clrscr();
  /// Si tenemos el nombre del primer fichero por argumento, es una excepcion, y lo intentamos cargar, si no, lo pedimos desde teclado
  if (argc > 1) {
    cout << "Cargando datos desde el fichero dado como argumento" << endl;
    strcpy(nombrefichero, argv[1]);
  } else {
    cout << "Introduce el nombre completo del fichero de datos" << endl;
    cin >> nombrefichero;
  }

  GRAFO G(nombrefichero, error_apertura);
  if (error_apertura == 1) {
    cout << "Error en la apertura del fichero desde argumento: revisa nombre y formato" << endl;
    system("pause");
  //  clrscr();
  } else {
    cout << "Grafo cargado desde el fichero " << nombrefichero << endl;
    system("pause");
  // clrscr();
    do {
      menu(G.Es_dirigido(), opcion);
      switch (opcion) {        
        case 'c' :
         // clrscr();
          cout << "Introduce el nombre completo del fichero de datos" << endl;
          cin >> nombrefichero;
          G.actualizar(nombrefichero, error_apertura);
            if (error_apertura == 1) {
              cout << "Error en la apertura del fichero: revisa nombre y formato : puedes volver a intentarlo" << endl;
            } else {
              cout << "Fichero cargado correctamente desde " << nombrefichero << endl;
            }
          system("pause");
          system("cls");
          break;

        case 'i' :
		      cout << "Grafo cargado desde " << nombrefichero << endl;
          G.Info_Grafo();
          system("pause");
          system("cls");
          break;
      
        case 'a' :
		      cout << "Grafo cargado desde " << nombrefichero << endl;
          G.MostrarListaAdyacencia();
          system("pause");
          system("cls");
          break;
        
        case 's' :
          G.MostrarListaSucesores();
          std::cout << "\n";
          system("pause");
          system("cls");
        break;

        case 'p' :
          G.MostrarListaPredesores();
          std::cout << "\n";
          system("pause");
          system("cls");
        break;

        case 'r' :
          G.RecorridoProfundidad();
          std::cout << "\n";
          system("pause");
          system("cls");
        break;

        case 'm' :
          G.RecorridoAmplitud();
          std::cout << "\n";
          system("pause");
          system("cls");
        break;
        
        case 'k':
          G.Kruskal();
          system("pause");
          system("cls");
        break;
        
        case 'j':
          G.Dijkstra();
          system("pause");
          system("cls");
        break;

		 //Situar aqu� el resto de opciones del men�
     }
    }
    while (opcion != 'q');
  }
  cout << "Fin del programa" << endl;
  return(0);
}
