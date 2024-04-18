#include <iostream> // Включение заголовочного файла для использования ввода/вывода
#include <vector> // Включение заголовочного файла для использования контейнера vector

struct Edge; // Объявление структуры Edge

struct Vertex { // Объявление структуры Vertex
    std::string name; // Поле для хранения имени вершины
    std::vector<Edge*> edges; // Вектор указателей на ребра, инцидентные данной вершине
};

struct Edge { // Объявление структуры Edge
    int cost; // Стоимость ребра
    Vertex* start; // Указатель на начальную вершину
    Vertex* end; // Указатель на конечную вершину
};

struct Graph { // Объявление структуры Graph
    std::vector<Vertex*> vertices; // Вектор указателей на вершины
};

void addCity(Graph& graph, std::string cityName) { // Функция для добавления нового города в граф
    Vertex* newVertex = new Vertex; // Создание новой вершины
    newVertex->name = cityName; // Присвоение имени новой вершине
    graph.vertices.push_back(newVertex); // Добавление новой вершины в граф
}

// Функция для добавления нового пути между вершинами с заданной стоимостью
void addRoad(Vertex* start, Vertex* end, int cost) {
    Edge* newEdge = new Edge; // Создание нового ребра
    newEdge->start = start; // Установка начальной вершины для ребра
    newEdge->end = end; // Установка конечной вершины для ребра
    newEdge->cost = cost; // Установка стоимости ребра
    start->edges.push_back(newEdge); // Добавление ребра в список инцидентных ребер начальной вершине
}

// Функция для вывода всех путей от текущей вершины к конечной с общей стоимостью
void printPaths(Vertex* current, Vertex* end, std::vector<std::string> path, int totalCost) {
    if (current == end) { // Если текущая вершина равна конечной
        path.push_back(current->name); // Добавляем имя текущей вершины в путь
        std::cout << "Путь: "; // Выводим сообщение о начале вывода пути
        for (size_t i = 0; i < path.size()-1; i++) { // Цикл для вывода вершин пути
            std::cout << path[i] << " -> "; // Выводим вершину пути
        }
        std::cout << path.back() << " (" << totalCost << ")" << std::endl; // Выводим последнюю вершину пути и общую стоимость
        return; // Завершаем функцию
    }
    path.push_back(current->name); // Добавляем имя текущей вершины в путь
    for (Edge* edge : current->edges) { // Проходим по всем инцидентным ребрам текущей вершины
        printPaths(edge->end, end, path, totalCost + edge->cost); // Рекурсивно вызываем функцию для следующей вершины
    }
}

// Функция для удаления пути между двумя вершинами
void removeRoad(Vertex* start, Vertex* end) {
    for (auto it = start->edges.begin(); it != start->edges.end(); ++it) { // Цикл по всем инцидентным ребрам начальной вершины
        if ((*it)->end == end) { // Если конечная вершина ребра равна заданной вершине
            delete *it; // Удаляем ребро
            start->edges.erase(it); // Удаляем указатель на ребро из списка инцидентных ребер начальной вершины
            break; // Выходим из цикла
        }
    }
}

// Функция для удаления города из графа
void removeCity(Graph& graph, std::string cityName) {
    for (auto it = graph.vertices.begin(); it != graph.vertices.end(); ++it) { // Цикл по всем вершинам графа
        if ((*it)->name == cityName) { // Если имя текущей вершины равно заданному имени города
            for (Edge* edge : (*it)->edges) { // Цикл по всем инцидентным ребрам текущей вершины
                removeRoad(edge->start, edge->end); // Удаляем путь между начальной и конечной вершинами ребра
            }
            delete *it; // Удаляем текущую вершину
            graph.vertices.erase(it); // Удаляем указатель на вершину из списка вершин графа
            break; // Выходим из цикла
        }
    }
}

int main() {
    Graph graph; // Создание графа

    addCity(graph, "A"); // Добавление города "A" в граф
    addCity(graph, "B"); // Добавление города "B" в граф
    addCity(graph, "C"); // Добавление города "C" в граф
    addCity(graph, "D"); // Добавление города "D" в граф
// Получение указателей на вершины A, B, C, Dиз списка вершин графа
    Vertex* A = graph.vertices[0];
    Vertex* B = graph.vertices[1];
    Vertex* C = graph.vertices[2];
    Vertex* D = graph.vertices[3];

    addRoad(A, B, 3); // Добавление пути от вершины A к вершине B с стоимостью 3
    addRoad(A, C, 2); // Добавление пути от вершины A к вершине C с стоимостью 2
    addRoad(B, D, 5); // Добавление пути от вершины B к вершине D с стоимостью 5
    addRoad(C, D, 4); // Добавление пути от вершины C к вершине D с стоимостью 4

    // Поиск всех путей от вершины A к вершине D и вывод на экран
    std::cout << "Пути из пункта А в пункт D:\n";
    printPaths(A, D, {}, 0); 

    return 0; // Возврат нуля как признак успешного завершения программы
}
