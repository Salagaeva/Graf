#include <iostream>     
#include <vector>     
     
struct Edge;     
     
struct Vertex {     
    std::string name;     
    std::vector<Edge*> edges;     
};     
     
struct Edge {     
    int cost;     
    Vertex* start;     
    Vertex* end;     
};     
     
struct Graph {     
    std::vector<Vertex*> vertices;     
};     
     
void addCity(Graph& graph, std::string cityName) {     
    Vertex* newVertex = new Vertex;     
    newVertex->name = cityName;     
    graph.vertices.push_back(newVertex);     
}     
     
void addRoad(Vertex* start, Vertex* end, int cost) {     
    Edge* newEdge = new Edge;     
    newEdge->start = start;     
    newEdge->end = end;     
    newEdge->cost = cost;     
    start->edges.push_back(newEdge);     
}     
     
void printPaths(Vertex* current, Vertex* end, std::vector<std::string> path, int totalCost) {     
    if (current == end) {     
        path.push_back(current->name);     
        std::cout << "Путь: ";     
        for (size_t i = 0; i < path.size() - 1; i++) {     
            std::cout << path[i] << " -> ";
        }
        std::cout << path.back() << " (" << totalCost << ")" << std::endl;     
        return;     
    }     
    path.push_back(current->name);     
    for (Edge* edge : current->edges) {     
        printPaths(edge->end, end, path, totalCost + edge->cost);     
    }     
}     
     
void removeRoad(Vertex* start, Vertex* end) {     
    for (auto it = start->edges.begin(); it != start->edges.end(); ++it) {     
        if ((*it)->end == end) {     
            delete *it;     
            start->edges.erase(it);     
            break;     
        }     
    }     
}     
     
void removeCity(Graph& graph, std::string cityName) {     
    for (auto it = graph.vertices.begin(); it != graph.vertices.end(); ++it) {     
        if ((*it)->name == cityName) {     
            for (Edge* edge : (*it)->edges) {     
                removeRoad(edge->start, edge->end);     
            }     
            delete *it;     
            graph.vertices.erase(it);     
            break;     
        }     
    }     
}

void printGraph(Graph& graph) { 
    for (Vertex* vertex : graph.vertices) { 
        std::cout << "от города " << vertex->name << " идёт путь к: "; 
        for (Edge* edge : vertex->edges) { 
            std::cout << edge->end->name << " (расстояние: " << edge->cost << "), "; 
        } 
        std::cout << std::endl; 
    } 
} 

int main() {     
    Graph graph;     
     
    addCity(graph, "A");     
    addCity(graph, "B");     
    addCity(graph, "C");     
    addCity(graph, "D");     
     
    Vertex* A = graph.vertices[0];     
    Vertex* B = graph.vertices[1];     
    Vertex* C = graph.vertices[2];     
    Vertex* D = graph.vertices[3];     
     
    addRoad(A, B, 3);     
    addRoad(A, C, 2);     
    addRoad(B, D, 5);     
    addRoad(C, D, 4);     
     
    // Find paths from A to D     
    std::cout << "Пути из пункта A в пункт D:\n";     
    printPaths(A, D, {}, 0);     

    std::cout << "\nКак выглядит граф:\n"; 
    printGraph(graph);
     
    return 0;     
}
  
