/*
 * Составить программу создания графа и реализовать процедуру для работы с
 * графом, определенную индивидуальным вариантом задания.
 *
 * Самостоятельно выбрать и реализовать способ представления графа в памяти.
 * В программе предусмотреть ввод с клавиатуры произвольного графа. В
 * вариантах построения остовного дерева также разработать доступный способ
 * (форму) вывода результирующего дерева на экран монитора.
 *
 *
 * Нахождение кратчайшего пути методом Дейкстра
 *
 * https://blog.skillfactory.ru/glossary/algoritm-dejkstry/
 */


#include <iostream>
#include <utility>
#include <vector>

using namespace std;

const int INF = 1000000000;


// Класс для хранения графа
class Graph {
    int size;
    vector<vector<int>> graph;
public:
    Graph(int size) {
        this->size = size;
        graph.resize(size);
        for (int i = 0; i < size; i++) {
            graph[i].resize(size);
            for (int j = 0; j < size; j++) {
                graph[i][j] = INF;
            }
        }
    }

    void addEdge(int from, int to, int weight) {
        graph[from][to] = weight;
    }

    void printGraph() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << graph[i][j] << " ";
            }
            cout << endl;
        }
    }

    void dijkstra(int start) {
        /*
         *  Алгоритм Дейкстры
         */
        vector<int> dist(size, INF); // Массив расстояний
        vector<int> prev(size, -1); // Массив предков
        vector<bool> used(size, false); // Массив посещенных вершин
        dist[start] = 0; // Начальная вершина

        // Перебираем все вершины
        for (int i = 0; i < size; i++) {
            int v = -1;

            // Ищем ближайшую непосещенную вершину
            for (int j = 0; j < size; j++) {

                // Если вершину еще не посещали и она ближе, чем предыдущая
                if (!used[j] && (v == -1 || dist[j] < dist[v])) {
                    v = j;
                }
            }

            // Если ближайшая вершина бесконечно далека, то выходим
            if (dist[v] == INF) {
                break;
            }

            // Помечаем вершину как посещенную
            used[v] = true;

            // Перебираем все ребра из вершины v
            for (int j = 0; j < size; j++) {

                // Если ребро существует и до вершины j еще не дошли
                if (graph[v][j] != INF) {
                    int to = j;
                    int len = graph[v][j];
                    if (dist[v] + len < dist[to]) {
                        dist[to] = dist[v] + len;
                        prev[to] = v;
                    }
                }
            }
        }

        // Выводим кратчайшие расстояния
        for (int i = 0; i < size; i++) {
            cout << dist[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < size; i++) {
            cout << prev[i] << " ";
        }
        cout << endl;
    }

    void printGraphviz() {
        /*
         *  Вывод графа в формате Graphviz
         */
        cout << "graph {" << endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (graph[i][j] != INF) {
                    cout << i << " -- " << j << " [label=" << graph[i][j] << "]" << endl;
                }
            }
        }
        cout << "}" << endl;
    }

};


int main() {
    Graph graph(6);

    graph.printGraph();
    graph.dijkstra(0);
    graph.printGraphviz();
    return 0;

}
