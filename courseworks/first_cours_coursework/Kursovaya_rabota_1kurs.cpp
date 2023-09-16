#include <iostream>
#include <fstream> // библиотека работы с файлами
using namespace std;

void dfs(int v, int len, bool **graph, bool *usedVertex, int *answer, int n) {
  if (len == 0) { // Если длина пути достигнута, добавляем вершину в ответ
    answer[v]++; // Увеличиваем значение answer для вершины v
    return; // завершаем работу функции
  }
  usedVertex[v] = true; // Помечаем вершину v, как посещенную
  for (int i = 0; i < n; ++i) { // Проходимся по всем вершинам графа
    if (graph[i][v] && !usedVertex[i]) { // Если вершины i и v смежные и вершина
                                         // i не была посещена
      dfs(i, len - 1, graph, usedVertex, answer, n); // Рекурсивно вызываем dfs
                                                     // для вершины i с
                                                     // уменьшенной на 1 длиной
                                                     // пути
    }
  }
  usedVertex[v] = false; // Снимаем метку о посещении текущей вершины v
}

int main() {
  setlocale(LC_ALL, "RU"); // подключение русского языка
  ifstream orgraph;        // создаем объект класса ifstream для работы с файлом
  ifstream need;           // создаем объект класса ifstream для работы с файлом
  ofstream out("result.txt");
  orgraph.open("graph.txt"); // открываем файл graph.txt
  need.open("need.txt");
  int n, m; // количество вершин и ребер в графе
  int sym1, sym2, sym3, sym4, sym5,
      sym6; // переменные для считывания данных с файлов
  for (int i = 0; i < 2; i++) { // считываем первые два числа с файла
    orgraph >> sym1;
    n = sym1; // первое число - количество вершни
    orgraph >> sym2;
    m = sym2; // второе число количество ребер
    break;
  }
  if (n >= 0) {
    bool *usedVertex =
        new bool[n];          // создаем динамический массив, хранящий посещенные вершины
    int *answer = new int[n]; // создаем динамический массив, хранящий ответы
    bool **graph =
        new bool *[n]; // создаем динамический массив - матрицу смежности графа
    for (int i = 0; i < n; i++) {
      graph[i] = new bool[n];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) { // зануляем матрицу смежности
        graph[i][j] = 0;
      }
      usedVertex[i] = false; // зануляем массив, хранящий посещенные вершины
      answer[i] = 0; // зануляем массив, хранящий ответы
    }
    for (int i = 0; i < m; i++) { // считываем ребра графа
      for (int j = 0; j < 2; j++) {
        orgraph >> sym3;
        orgraph >> sym4;
        graph[sym3][sym4] = true; // заполняем матрицу смежности
      }
    }
    int v, len; // нужная вершина и длина
    need >> sym5; // первый элемент в файле need - нужная вершина
    v = sym5;
    if (v >= 0) {
      out << "количество вершин в вашем графе: " << n << endl;
      out << "количество ребер в вашем графе: " << m << endl;
      if (v < n) {
        need >> sym6; // второй элемент в файле need - нужная длина
        len = sym6;
        out << "Заданная вершина: " << v << endl;
        out << "Заданная длина пути: " << len << endl;
        dfs(v, len, graph, usedVertex, answer,
            n); // запускаем агортим обхода в глубину
        out << "Номера вершин из которых существует путь длины " << len
            << " к вершине " << v << ": ";
        for (int i = 0; i < n; i++) {
          if (answer[i] != 0) { // выводим номера вершин из которых существует
                                // путь длины len к вершине v
            out << i << " ";
          }
        }
        if (graph[v][v] == 1) {
          out << v;
        }
        out << endl;
        return 0;
      } else {
        out << "В вашем графе не содержится вершина с номером " << v
            << " (нумерация вершин начинается с 0)" << endl;
        return 0;
      }
    } else {
      out << "Файл need.txt пуст";
      return 0;
    }
  } else {
    out << "Файл orgraph.txt пуст";
    return 0;
  }
}