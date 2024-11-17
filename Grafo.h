#ifndef GRAFO_H
#define GRAFO_H
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <limits>

template<class T>
class Grafo {
    private:
        std::vector<T> vertices;
        double** aristas;
    public:
        Grafo();
        void fijarVertices(std::vector<T> vertices);
        void fijarAristas (double** aristas);
        const std::vector<T>& obtenerVertices() const;
        double** obtenerAristas();
        double** obtenerAristasCpy();
        int cantVertices();
        int cantAristas();
        int buscarVertice(T ver);
        bool insertarVertice(T ver);
        bool insertarArista(T ori, T des, double cos);
        bool insAristaNoDir(T ori, T des, double cos);
        double buscarArista(T origen, T destino);
        bool eliminarVertice(T ver);
        bool eliminarArista (T origen, T destino);
        bool elimAristaNoDir(T ori, T des);
        std::vector<T> vecinosVertice(T ver);
        void plano();
        std::vector<T> DFS(T ver_inicial);
        std::vector<T> BFS(T ver_inicial);
        std::vector<T*> Dijkstra(T ver_inicial);
        std::vector<T> caminoDijkstra(T ver_destino, std::vector<T*> predecesores);
        void mostrarMatrizAdyacencia();    
};

#include "Grafo.hxx"
#endif