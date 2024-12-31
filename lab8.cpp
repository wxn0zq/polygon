#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <queue>
#include <stack>
#include <cmath>
#include <limits>
#include <chrono>
#include <iomanip>
#include <cassert>

using namespace std;

struct Node {
    double lon = 0.0;
    double lat = 0.0;
    vector<pair<Node*, double>> edges;

    Node(double lon, double lat) : lon(lon), lat(lat) {}
};

class Graph {
public:
    Graph() = default;

    //Метод для поиска или создания узла
    Node* getOrAddNode(double lon, double lat) {
        string key = makeKey(lon, lat);

        auto it = node_map.find(key);
        if (it != node_map.end()) {
            return it->second;
        }

        auto newNode = make_unique<Node>(lon, lat);
        Node* nodePtr = newNode.get();
        nodes.push_back(move(newNode));
        node_map[key] = nodePtr;
        return nodePtr;
    }

    //Метод для получения узла по координатам
    Node* getNode(double lon, double lat) const {
        string key = makeKey(lon, lat);
        auto it = node_map.find(key);
        return it != node_map.end() ? it->second : nullptr;
    }

    //Метод для чтения графа из файла
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Ошибка при открытии файла: " << filename << "\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            processLine(line);
        }
        file.close();
    }

    //Метод для поиска ближайшего узла
    Node* findClosest(double lon, double lat) const {
        Node* closest = nullptr;
        double minDist = numeric_limits<double>::max();

        for (const auto& node : nodes) {
            double dist = calculateDistance(node.get(), lon, lat);
            if (dist < minDist) {
                minDist = dist;
                closest = node.get();
            }
        }
        return closest;
    }

    //Метод для вывода пути
    void displayPath(const vector<Node*>& path) const {
        if (path.empty()) {
            cout << "Путь не найден.\n";
            return;
        }

        double totalWeight = 0.0;
        for (size_t i = 0; i < path.size(); ++i) {
            cout << "(" << path[i]->lat << ", " << path[i]->lon << ")";
            if (i < path.size() - 1) {
                cout << " -> ";
                totalWeight += getEdgeWeight(path[i], path[i + 1]);
            }
        }
        cout << "\nОбщая длина пути: " << totalWeight << "\n";
    }

private:
    vector<unique_ptr<Node>> nodes;
    unordered_map<string, Node*> node_map;

    //Формирует строковый ключ для узла
    string makeKey(double lon, double lat) const {
        ostringstream oss;
        oss << fixed << setprecision(10) << lon << "," << lat;
        return oss.str();
    }

    //Вычисляет расстояние между двумя узлами
    double calculateDistance(Node* node, double lon, double lat) const {
        double dx = node->lon - lon;
        double dy = node->lat - lat;
        return sqrt(dx * dx + dy * dy);
    }

    //Обрабатывает строку файла
    void processLine(const string& line) {
        istringstream lineStream(line);
        string parentData, edgesData;

        if (getline(lineStream, parentData, ':')) {
            replace(parentData.begin(), parentData.end(), ',', ' ');
            istringstream parentStream(parentData);

            double lon1, lat1;
            if (!(parentStream >> lon1 >> lat1)) {
                cerr << "Ошибка в данных узла: " << parentData << "\n";
                return;
            }

            Node* parentNode = getOrAddNode(lon1, lat1);

            while (getline(lineStream, edgesData, ';')) {
                replace(edgesData.begin(), edgesData.end(), ',', ' ');
                istringstream edgeStream(edgesData);

                double lon2, lat2, weight;
                if (!(edgeStream >> lon2 >> lat2 >> weight)) {
                    cerr << "Ошибка в данных рёбер: " << edgesData << "\n";
                    continue;
                }

                Node* childNode = getOrAddNode(lon2, lat2);
                parentNode->edges.emplace_back(childNode, weight);
                childNode->edges.emplace_back(parentNode, weight);
            }
        }
    }

    //Получает вес рёбера между двумя узлами
    double getEdgeWeight(Node* from, Node* to) const {
        for (const auto& edge : from->edges) {
            if (edge.first == to) {
                return edge.second;
            }
        }
        return 0.0; //Если рёбер нет, возвращаем 0
    }
};

vector<Node*> BFS(Node* start, Node* goal);
vector<Node*> DFS(Node* start, Node* goal);
vector<Node*> Dijkstra(Graph& graph, Node* start, Node* goal);
vector<Node*> AStar(Graph& graph, Node* start, Node* goal);

int main() {
    Graph graph;
    graph.loadFromFile("/Users/vikaz/Downloads/spb_graph.txt");

    double startLat = 59.885286, startLon = 30.368213;
    double endLat = 59.957238, endLon = 30.308108;

    Node* startNode = graph.findClosest(startLon, startLat);
    Node* endNode = graph.findClosest(endLon, endLat);

    if (!startNode || !endNode) {
        cerr << "Не удалось найти узлы для старта и финиша.\n";
        return 1;
    }

    //Пример использования алгоритмов
    {
        auto t1 = chrono::high_resolution_clock::now();
        vector<Node*> pathBFS = BFS(startNode, endNode);
        auto t2 = chrono::high_resolution_clock::now();
        graph.displayPath(pathBFS);
        cout << "Время BFS: " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms\n";
    }

    {
        auto t1 = chrono::high_resolution_clock::now();
        vector<Node*> pathDFS = DFS(startNode, endNode);
        auto t2 = chrono::high_resolution_clock::now();
        graph.displayPath(pathDFS);
        cout << "Время DFS: " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms\n";
    }

    {
        auto t1 = chrono::high_resolution_clock::now();
        vector<Node*> pathDijkstra = Dijkstra(graph, startNode, endNode);
        auto t2 = chrono::high_resolution_clock::now();
        graph.displayPath(pathDijkstra);
        cout << "Время Dijkstra: " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms\n";
    }

    {
        auto t1 = chrono::high_resolution_clock::now();
        vector<Node*> pathAStar = AStar(graph, startNode, endNode);
        auto t2 = chrono::high_resolution_clock::now();
        graph.displayPath(pathAStar);
        cout << "Время A*: " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms\n";
    }

    return 0;
}