#include "Graph.hpp"

namespace ariel {

    Graph::Graph() {}

    void Graph::cleanGraph(){
        this->adjacencyMatrix.clear();
        this->cycle.erase();
        this->isDirected = false;
        this->hasNegativeEdges = false;
        this->hasNegativeCycle = false;
        this->edges = 0;
        this->cycle;
    }

    void checkSquareMatrix(const std::vector<std::vector<int>>& matrix){
        for (size_t i = 0; i < matrix.size(); i++)
        {
            if (matrix[i].size() != matrix.size())
            {
                throw std::invalid_argument("Error: Matrix is not square!");
            }
        }
    }

    void Graph::setDirected(const std::vector<std::vector<int>>& matrix){
        for (size_t i = 0; i < matrix.size(); i++)
        {
            for (size_t j = 0; j < matrix.size(); j++)
            {
                if (matrix[i][j] != matrix[j][i])
                {
                    this->isDirected = true;
                    break;
                }
            }
            if (this->isDirected) {
                break;
            }
        }
    }

    void Graph::setNegativeEdges(const std::vector<std::vector<int>>& matrix)
    {
        for (size_t i = 0; i < matrix.size(); i++)
        {
            for (size_t j = 0; j < matrix.size(); j++)
            {
                if (matrix[i][j] < 0)
                {
                    this->hasNegativeEdges = true;
                    break;
                }
            }
            if (this->hasNegativeEdges) {
                break;
            }
        }
    }

    void Graph::loadGraph(const std::vector<std::vector<int>>& matrix){
        cleanGraph();
        checkSquareMatrix(matrix);
        setDirected(matrix);
        setNegativeEdges(matrix);

        v = matrix.size();

        adjacencyMatrix = matrix;

        for(size_t i = 0; i < matrix.size(); ++i){
            for(size_t j = 0; j < matrix.size(); ++j){
                if(adjacencyMatrix[i][j] != 0){
                    edges++;
                }
            }
        }

        if(!isDirected){
            edges /= 2;
        }
    }

    void Graph::printGraph() const
    {
        std::cout << "Graph with " << v << " vertices and " << edges << " edges." << std::endl;
    }

    Graph Graph::operator+(const Graph& other) const
    {
        Graph newGraph;
        newGraph.v = this->v + other.v;
        newGraph.edges = this->edges + other.edges;

        newGraph.adjacencyMatrix = this->adjacencyMatrix;
        newGraph.adjacencyMatrix.insert(newGraph.adjacencyMatrix.end(), other.adjacencyMatrix.begin(), other.adjacencyMatrix.end());

        return newGraph;
    }

    Graph Graph::operator*(const Graph& other) const
    {
        Graph newGraph;
        newGraph.v = this->v;
        newGraph.edges = this->edges;

        for(size_t i = 0; i < this->adjacencyMatrix.size(); ++i){
            std::vector<int> row;
            for(size_t j = 0; j < this->adjacencyMatrix.size(); ++j){
                int sum = 0;
                for(size_t k = 0; k < this->adjacencyMatrix.size(); ++k){
                    sum += this->adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j];
                }
                row.push_back(sum);
            }
            newGraph.adjacencyMatrix.push_back(row);
        }

        return newGraph;
    }

    Graph& Graph::operator+=(const Graph& other)
    {
        this->v += other.v;
        this->edges += other.edges;

        this->adjacencyMatrix.insert(this->adjacencyMatrix.end(), other.adjacencyMatrix.begin(), other.adjacencyMatrix.end());

        return *this;
    }

    Graph& Graph::operator*=(int num)
    {
        this->v *= num;
        this->edges *= num;

        for(size_t i = 0; i < this->adjacencyMatrix.size(); ++i){
            for(size_t j = 0; j < this->adjacencyMatrix.size(); ++j){
                this->adjacencyMatrix[i][j] *= num;
            }
        }

        return *this;
    }

    Graph& Graph::operator/=(int num)
    {
        this->v /= num;
        this->edges /= num;

        for(size_t i = 0; i < this->adjacencyMatrix.size(); ++i){
            for(size_t j = 0; j < this->adjacencyMatrix.size(); ++j){
                this->adjacencyMatrix[i][j] /= num;
            }
        }

        return *this;
    }

    bool Graph::operator==(const Graph& other) const
    {
        if(this->v != other.v || this->edges != other.edges){
            return false;
        }

        for(size_t i = 0; i < this->adjacencyMatrix.size(); ++i){
            for(size_t j = 0; j < this->adjacencyMatrix.size(); ++j){
                if(this->adjacencyMatrix[i][j] != other.adjacencyMatrix[i][j]){
                    return false;
                }
            }
        }

        return true;
    }

    bool Graph::operator>(const Graph& other) const
    {
        return this->v > other.v;
    }

    Graph Graph::operator-(const Graph& other) const
    {
        Graph newGraph;
        newGraph.v = this->v - other.v;
        newGraph.edges = this->edges - other.edges;

        newGraph.adjacencyMatrix = this->adjacencyMatrix;
        newGraph.adjacencyMatrix.insert(newGraph.adjacencyMatrix.end(), other.adjacencyMatrix.begin(), other.adjacencyMatrix.end());

        return newGraph;
    }

    Graph& Graph::operator-=(const Graph& other)
    {
        this->v -= other.v;
        this->edges -= other.edges;

        this->adjacencyMatrix.insert(this->adjacencyMatrix.end(), other.adjacencyMatrix.begin(), other.adjacencyMatrix.end());

        return *this;
    }

    Graph& Graph::operator+()
    {
        for(size_t i = 0; i < this->adjacencyMatrix.size(); ++i){
            for(size_t j = 0; j < this->adjacencyMatrix.size(); ++j){
                this->adjacencyMatrix[i][j] = abs(this->adjacencyMatrix[i][j]);
            }
        }

        return *this;
    }

    Graph& Graph::operator-()
    {
        for(size_t i = 0; i < this->adjacencyMatrix.size(); ++i){
            for(size_t j = 0; j < this->adjacencyMatrix.size(); ++j){
                this->adjacencyMatrix[i][j] = -this->adjacencyMatrix[i][j];
            }
        }

        return *this;
    }

    Graph& Graph::operator++()
    {
        this->v++;
        this->edges++;

        return *this;
    }

    Graph Graph::operator++(int)
    {
        Graph temp = *this;
        this->v++;
        this->edges++;

        return temp;
    }

    Graph& Graph::operator--()
    {
        this->v--;
        this->edges--;

        return *this;
    }

    Graph Graph::operator--(int)
    {
        Graph temp = *this;
        this->v--;
        this->edges--;

        return temp;
    }

    Graph &Graph::operator-=(const Graph &other)
    {
        this->v -= other.v;
        this->edges -= other.edges;

        this->adjacencyMatrix.insert(this->adjacencyMatrix.end(), other.adjacencyMatrix.begin(), other.adjacencyMatrix.end());

        return *this;
    }

    std::ostream &operator<<(std::ostream &os, const Graph &graph)
    {
        for(size_t i = 0; i < graph.adjacencyMatrix.size(); ++i){
            for(size_t j = 0; j < graph.adjacencyMatrix.size(); ++j){
                os << graph.adjacencyMatrix[i][j] << " ";
            }
            os << std::endl;
        }

        return os;
    }
}
