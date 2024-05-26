#include "Graph.hpp"
#include "Algorithms.hpp"

namespace ariel
{

const int INFINITY = std::numeric_limits<int>::max();

void Algorithms::bfs(Graph& g, int v, std::vector<bool>& visited)
{
	std::queue<int> q;
	q.push(v);
	visited[static_cast<size_t>(v)] = true;

	while (!q.empty())
	{
		int current = q.front();
		q.pop();

		for (size_t i = 0; i < g.adjacencyMatrix[static_cast<size_t>(current)].size(); i++)
		{
			if (g.adjacencyMatrix[static_cast<size_t>(current)][i] != 0 && !visited[i])
			{
				q.push(i);
				visited[i] = true;
			}
		}
	}
}

int Algorithms::isConnected(Graph& g)
{
	if (g.isDirected)
	{
		std::vector<bool> visited(g.getSize(), false);

		for (size_t i = 0; i < g.getSize(); i++)
		{
			std::vector<bool> tempVisited(g.getSize(), false);
			bfs(g, i, tempVisited);

			for (size_t j = 0; j < visited.size(); j++)
			{
				visited[j] = visited[j] && tempVisited[j];
			}
		}

		for (bool v : visited)
		{
			if (!v) return 0;
		}
		return 1;
	}
	else
	{
		std::vector<bool> visited(g.getSize(), false);

		bfs(g, 0, visited);

		for (bool v : visited) {
			if (!v) return 0;
		}
		return 1;
	}
}

std::string Algorithms::shortestPath(Graph& g, size_t start, size_t end) {
	size_t n = g.getSize();
	std::vector<int> prev(n, -1);
	std::vector<int> dist(n, INFINITY);
	bellmanFord(g, start, prev, dist);
	for (size_t u = 0; u < n; u++)
	{
		for (size_t v = 0; v < n; v++)
		{
			if (g.adjacencyMatrix[u][v] != 0 && dist[v] > dist[u] + g.adjacencyMatrix[u][v])
			{
				g.hasNegativeCycle = true;
				std::vector<size_t> negativeCycle;
				size_t current = u;
				while(std::find(negativeCycle.begin(), negativeCycle.end(), current) == negativeCycle.end())
				{
					negativeCycle.push_back(current);
					current = (size_t)prev[current];
				}
				std::reverse(negativeCycle.begin(), negativeCycle.end());
				std::string cycleString = std::to_string(current);
				for(size_t i = 0; i < negativeCycle.size() - 1; ++i){
					cycleString += "->" + std::to_string(negativeCycle[i]);
				}
				g.setCycle(cycleString);
				return "-1";
			}
		}
	}
	if (dist[end] != INFINITY)
	{
		return printPath(prev, start, end);
	}
	else
	{
		return "-1";
	}
}

void Algorithms::bellmanFord(Graph& g, size_t start, std::vector<int>& previous, std::vector<int>& distance)
{
	distance[start] = 0;
	for (size_t i = 0; i < g.getSize() - 1; i++)
	{
		for (size_t u = 0; u < g.getSize(); u++)
		{
			for (size_t v = 0; v < g.getSize(); v++)
			{
				if (g.adjacencyMatrix[u][v] != 0) {
					relax(u, v, g.adjacencyMatrix[u][v], previous, distance);
				}
			}
		}

	}
}

void Algorithms::relax(size_t u, size_t v, int w, std::vector<int>& prev, std::vector<int>& dist) {
	if (dist[u] != INFINITY && (dist[v] > dist[u] + w)) {
		dist[v] = dist[u] + w;
		prev[v] = u;
	}
}

std::string Algorithms::printPath(std::vector<int>& prev,  size_t start, size_t end) {
	std::string path;
	if (prev[end] == -1) {
		return "-1"; // No path found
	}

	std::vector<int> vec;
	size_t i = end;
	while(i != start){
		vec.push_back(i);
		i = static_cast<size_t>(prev[i]);
	}
	vec.push_back(i);


	for(size_t j = vec.size() - 1; j > 0; j--){
		path += std::to_string(vec[j]) + "->";
	}
	path += std::to_string(vec[0]); // Add the start vertex at the end

	return path;
}


bool Algorithms::isContainsCycle(Graph& g) {

	std::string potentialCycle = g.getCycle();

	if (!potentialCycle.empty()) {
		return true;
	} else {
		if(g.getSize() > 0){
			bool hasCycle = false;
			size_t n = (size_t)g.getSize();
			std::vector<int> color(n, 1);
			std::vector<int> path(n, -1);
			for(size_t i = 0; i < n; i++)
			{
				hasCycle = DFSCycle(g, color, path, i);
				if(hasCycle)
				{
					return true;
				}
			}

		}
	}
	return false;
}


bool Algorithms::DFSCycle(Graph& g, std::vector<int>& color, std::vector<int>& path, size_t v) {


	for(size_t i = 0; i < g.getSize(); i++) {
		if(g.adjacencyMatrix[v][i]) {
			if(color[i] == 1) {
			   color[i] = -1;
			   path[i] = v;
			   return DFSCycle(g, color, path, i);
		}
		else if (color[i] == -1)
			g.setCycle(getCycle(path, v, i));
			return true;

			}
		}
		return false;
}

std::string Algorithms::getCycle(std::vector<int> path, size_t start, size_t end){
			std::string ans;
			std::vector<int> oppositePath;
			size_t i = end;
			oppositePath.push_back(i);
			while (i != start)
			{
				i = (size_t)path[i];
				oppositePath.push_back(i);
			}
			for (size_t i = oppositePath.size() - 1; i > 0; i--)
			{
				ans += oppositePath[i] + 48;
				ans += "->";
			}
			ans += oppositePath[0] + 48;
			return ans;
		}

std::string Algorithms::isBipartite(Graph& g) {
	size_t n = g.getSize();
	std::vector<std::vector<int>> edges(n);

	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			if (g.adjacencyMatrix[i][j] != 0) {
				edges[i].push_back(j);
			}
		}
	}

	std::vector<int> visited(g.getSize(), -1);
	bool res = true;
	std::unordered_set<int> first_set, second_set;

	for (size_t i = 0; i < g.getSize(); i++) {
		if (visited[i] == -1) {
			if (!bipartite(g, edges, i, visited, first_set, second_set)) {
				res = false;
				break;
			}
		}
	}

	std::string result;
	if (res) {
		result += "The graph is bipartite: A={";
		bool firstA = true;
		for (auto elem : first_set) {
			if (!firstA) {
				result += ", ";
			}
			result += std::to_string(elem);
			firstA = false;
		}
		result += "}, B={";
		bool firstB = true;
		for (auto elem : second_set) {
			if (!firstB) {
				result += ", ";
			}
			result += std::to_string(elem);
			firstB = false;
		}
		result += "}";
	} else {
		result += "Not bipartite";
	}
	return result;
}


bool Algorithms::bipartite(Graph& g, std::vector<std::vector<int>>& edges, int start, std::vector<int>& visited, std::unordered_set<int>& setA, std::unordered_set<int>& setB) {
	std::queue<int> q;
	q.push(start);

	visited[(size_t)start] = 1;
	setA.insert(start); // Add starting node to set A

	while (!q.empty()) {
		int curr = q.front();
		q.pop();
		for (int elem : edges[(size_t)curr]) {
			if (visited[(size_t)elem] == visited[(size_t)curr]) {
				return false;
			}
			if (visited[(size_t)elem] == -1) {
				visited[(size_t)elem] = 1 - visited[(size_t)curr];
				if (visited[(size_t)elem] == 1) {
					setA.insert(elem); // Add to set A if assigned color 1
				} else {
					setB.insert(elem); // Add to set B if assigned color 0
				}
				q.push(elem);
			}
		}
  	}
	return true;
	}

int Algorithms::negativeCycle(Graph& g) {
	if(g.hasNegativeEdges)
	{
		if(g.hasNegativeCycle)
		{
			return 1;
		}

		size_t n = g.getSize();
		std::vector<int> prev(n, -1);
		std::vector<int> dist(n, INFINITY);
		bellmanFord(g, 0, prev, dist);
		for (size_t u = 0; u < n; ++u) {
			for (size_t v = 0; v < n; ++v) {
				if (g.adjacencyMatrix[u][v] != 0 && dist[v] > dist[u] + g.adjacencyMatrix[u][v]) {
						g.hasNegativeCycle = true;
						std::vector<size_t> negativeCycle;
						size_t current = u;
						while(std::find(negativeCycle.begin(), negativeCycle.end(), current) == negativeCycle.end()){
							negativeCycle.push_back(current);
							current = (size_t)prev[current];
						}
						std::reverse(negativeCycle.begin(), negativeCycle.end());
						std::string cycleString = std::to_string(current);
						for(size_t i = 0; i < negativeCycle.size() - 1; ++i){
							cycleString += "->" + std::to_string(negativeCycle[i]);
					}
						g.setCycle(cycleString);
						return 1;
				}
			}
		}

	}
	else
	{
		return 0;
	}
	return 0;
	}
}
