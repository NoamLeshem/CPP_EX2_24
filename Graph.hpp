#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <limits>
#include <unordered_set>

namespace ariel {
    class Graph {
    public:
        std::vector<std::vector<int>> adjacencyMatrix;
        std::vector<std::vector<int>> shortestPaths;
        bool isDirected;
        bool hasNegativeCycle;
        bool hasNegativeEdges;
        std::string cycle;
        size_t v;
        int edges;
        std::unordered_set<int> sets[2];

        Graph();
        void loadGraph(const std::vector<std::vector<int>>& matrix);
        void printGraph() const;
        void cleanGraph();
        void setDirected(const std::vector<std::vector<int>>& matrix);
        void setNegativeEdges(const std::vector<std::vector<int>>& matrix);
        inline size_t getSize() const{ return adjacencyMatrix.size(); };
        inline std::string getCycle(){ return cycle; }
        inline void setCycle(std::string foundCycle) { cycle = foundCycle;}

        Graph operator+(const Graph &) const;
        Graph &operator+=(const Graph &);
        Graph &operator+();
        Graph &operator++();
        Graph operator++(int);

        Graph operator-(const Graph &) const;
        Graph &operator-=(const Graph &);
        Graph &operator-();
        Graph &operator--();
        Graph operator--(int);

        Graph operator*(const Graph &) const;
        Graph &operator*=(int);
        Graph &operator/=(int);

        bool operator==(const Graph &) const;
        bool operator!=(const Graph &other) const { return !(*this == other); };
        bool operator>(const Graph &) const;
        bool operator<(const Graph &other) const { return (other > *this); };
        bool operator>=(const Graph &other) const { return (*this > other) || (*this == other); };
        bool operator<=(const Graph &other) const { return (*this < other) || (*this == other); };

        friend std::ostream &operator<<(std::ostream &os, const Graph &graph);
    };
}

#endif