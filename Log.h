#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> IPcount(17000, 0);

struct Log {
  std::string month;
  int day;
  std::string hour;
  std::string ip;
  std::vector<int> splittedIP;
  std::string error;

  void print() {
    std::cout << month << " " << day << " " << hour << " " << ip << " " << error
              << "\n";
  }

  void splitIP();
  void operator=(Log &);
};
// parte cada una linea y devuelve un std::vector con los elementos que se
// consiguieron a partir del delimitador
// o(n)
std::vector<std::string> split(std::string str, char delimitador) {
  // declaramos el std::string temporal que almacena la palabra que tenemos
  // formada
  std::string temp = "";
  std::vector<std::string> splittedString;

  for (int i = 0; i < (int)str.size(); i++) {
    // si todavia no se encuentra el delimitador, agrega el caracter actual a
    // temp si se encuentra el delimitador, entonces agrega al std::vector
    if (str[i] != delimitador) {
      temp += str[i];
    } else {
      splittedString.push_back(temp);
      temp = "";
    }
  }
  splittedString.push_back(temp);
  return splittedString;
}

// Parte el ip en un std::vector de ints
// o(n)
void Log::splitIP() {
  std::vector<int> splitted;
  std::stringstream ss1(ip);
  std::string octet;

  while (getline(ss1, octet, '.')) {
    splitted.push_back(stoi(octet));
  }
  splittedIP = splitted;
}

// compara dos ips y devuelve un bool si ip1 es mas grande q ip2
//  o(n)
bool compareIP(std::vector<int> &ip1, std::vector<int> &ip2) {

  // Compara los octetos de las direcciones IP
  for (int i = 0; i < 4; i++) {
    if (ip1[i] < ip2[i]) {
      return true; // ip1 es menor que ip2
    } else if (ip1[i] > ip2[i]) {
      return false; // ip1 es mayor que ip2
    }
  }

  return true; // Las IP son iguales o ip1 es menor que ip2
}

// el mensaje de error tiene espacios asi que la funcion split los parte
//  en esta funcion juntamos el mensaje
std::string joinErrorLog(std::vector<std::string> log, int beginning) {
  std::string error;

  // beginning es el indice de la primera palabra del mensaje de error
  for (int i = beginning; i <= log.size() - 1; i++) {
    error += log[i] + " ";
  }
  return error;
}

// Función personalizada para comparar direcciones IP con puertos
// o(1)
bool compareIPWithPort(const std::string &ip1, const std::string &ip2) {
  return ip1.compare(ip2) < 0;
}

void Log::operator=(Log &other) {
  month = other.month;
  day = other.day;
  hour = other.hour;
  ip = other.ip;
  splittedIP = other.splittedIP;
  error = other.error;
}
#endif
