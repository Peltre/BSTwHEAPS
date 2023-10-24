/*
Este codigo sirve para organizar los registros por ip que se encuentran en un
archivo llamado bitacora.txt

Primero se almacenan los datos de bitacora.txt en vectores y depsues se utiliza
el algortimo Merge Sort para organizarlos
*/

#include "BST-2.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// O(n)
//  Función para encontrar las 3 IPs con más apariciones
void findTop3IPs(vector<int> &IPcount, BST &tree) {
  // Crear un montículo máximo para almacenar pares (apariciones, IP)
  priority_queue<pair<int, int>> maxHeap;

  // Llenar el montículo con los valores de IPcount
  for (int i = 0; i < IPcount.size(); ++i) {
    maxHeap.push({IPcount[i], i});
  }

  // Imprimir las 3 IPs con más apariciones
  for (int i = 0; i < 3; ++i) {
    if (!maxHeap.empty()) {
      cout << "----------------------------------------------------------------"
              "---"
           << endl;
      pair<int, int> topIP = maxHeap.top();
      maxHeap.pop();
      cout << "Direccion IP: " << topIP.second
           << " - Apariciones: " << topIP.first << endl;
      tree.rangePrint(topIP.second);
    } else {
      break; // En caso de que no haya suficientes IPs en el montículo
    }
  }
}

// funcion main
// o(n^2)
int main() {
  ifstream miArchivo;
  miArchivo.open("bitacora.txt");

  BST tree;
  vector<int> IPcount(1000, 0);

  string linea;
  char delimitador = ' ';
  string error;

  int totalLogs = 0;

  if (miArchivo.is_open()) {
    while (getline(miArchivo, linea)) {
      Log record;
      vector<string> splittedString = split(linea, delimitador);

      // guardamos el valor de las lineas de bitacora.txt en la struct
      record.month = splittedString[0];
      record.day = stoi(splittedString[1]);
      record.hour = splittedString[2];
      record.ip = splittedString[3];
      record.splitIP();
      error = joinErrorLog(splittedString, 4);
      record.error = error;

      tree.add(record);
      IPcount[record.splittedIP[0]]++;
      totalLogs += 1;
    }
  } else {
    // mensaje error
    cout << "No se pudo abrir el archivo\n";
    return 1;
  }

  tree.print(inorder);
  printf("Numero total de registros: %d\n", totalLogs);

  cout << "Las 3 direcciones IP con mas apariciones son:\n " << endl;

  findTop3IPs(IPcount, tree);

  miArchivo.close();

  // mergeSort(logs);

  // string start, end;
  // cout << "Ingrese la IP de inicio de búsqueda : ";
  // cin >> start;
  // cout << "Ingrese la IP de fin de búsqueda : ";
  // cin >> end;
  //
  // LinkedList<Log> filteredLogs;
  // for (int i = 0; i < logs.getSize(); i++) {
  //   if (compareIP(start, logs.get(i).ip) && compareIP(logs.get(i).ip, end)) {
  //     filteredLogs.addLast(logs.get(i));
  //   }
  // }
  //
  // cout << "Registros correspondientes a las IPs de búsqueda:\n";
  // filteredLogs.printLog();
  //
  // ofstream outputFile;
  // outputFile.open("resultados_ordenados.txt");
  // if (outputFile.is_open()) {
  //   for (int i = 0; i < filteredLogs.getSize(); i++) {
  //     outputFile << filteredLogs.get(i).month << " " <<
  //     filteredLogs.get(i).day
  //                << " " << filteredLogs.get(i).hour << " "
  //                << filteredLogs.get(i).ip << " " <<
  //                filteredLogs.get(i).error
  //                << "\n";
  //   }
  //   outputFile.close();
  //   cout << "Resultados ordenados almacenados en
  //   'resultados_ordenados.txt'.\n";
  // } else {
  //   cout << "No se pudo abrir el archivo de salida.\n";
  // }
  //
  return 0;
}
