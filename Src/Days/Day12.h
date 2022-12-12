#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>

namespace Day12 {

	struct Node
	{
		char letter;
		std::vector<Node*> edges;

		Node(char letter__) : letter(letter__) { }
		inline void addEdge(Node* edge) { edges.push_back(edge); }
	};

	class Path
	{
	private:
		std::vector<Node*> vistedNodes;

	public:
		Path() { }
		Path(Node* root) { vistedNodes.push_back(root); }
		Path(Node* root, Path* path) { vistedNodes = path->vistedNodes; vistedNodes.push_back(root); }

		inline Node* getCurrentNode() { return vistedNodes.back(); }

		inline void visitNode(Node* node) { vistedNodes.push_back(node); }
		inline bool visited(Node* node) { return std::find(vistedNodes.begin(), vistedNodes.end(), node) != vistedNodes.end(); }
	};

	class Graph
	{
	private:
		std::vector<std::vector<Node*>> nodes;
		std::pair<std::vector<Node*>, Path> deapestNodeSet;
	public:
		Graph(const char* path, char endPoint = 'E')
		{
			std::string buffer;
			std::fstream input(path);
			while (std::getline(input, buffer))
			{
				std::vector<Node*> nodeLine;
				for (char letter : buffer)
				{
					nodeLine.push_back(new Node(letter));
					if (nodeLine.back()->letter == endPoint)
					{
						std::vector<Node*> root;
						root.push_back(nodeLine.back());
						deapestNodeSet = std::pair<std::vector<Node*>, Path>(root, Path(nodeLine.back()));
					}
				}
				nodes.push_back(nodeLine);
			}

			constructEdges();
		}

		inline bool nextDepth(char startingPoint = 'S')
		{
			std::vector<Node*> nextDeapestNodes;
				
			for (Node* node : deapestNodeSet.first)
				if (node->letter == startingPoint)
					return true;
				else
					for (Node* edge : node->edges)
						if (((node->letter == 'E' && edge->letter == 'z') || (edge->letter + 1 >= node->letter && node->letter != 'E') ||
							(edge->letter == startingPoint && node->letter == 'a')) && !deapestNodeSet.second.visited(edge))
						{
							nextDeapestNodes.push_back(edge);
							deapestNodeSet.second.visitNode(edge);
						}
				
			deapestNodeSet.first = nextDeapestNodes;
		
			return false;
		}
	private:
		inline void constructEdges()
		{
			for (size_t i = 0; i < nodes.size(); i++)
				for (size_t j = 0; j < nodes.at(i).size(); j++)
				{
					if (i > 0) nodes[i][j]->addEdge(nodes[i - 1][j]);
					if (i < nodes.size() - 1) nodes[i][j]->addEdge(nodes[i + 1][j]);
					if (j > 0) nodes[i][j]->addEdge(nodes[i][j - 1]);
					if (j < nodes.at(i).size() - 1) nodes[i][j]->addEdge(nodes[i][j + 1]);
				}
		}
	};

	inline long star1(const char* path) noexcept
	{
		long depth = 0;

		Graph graph(path);
		while (!graph.nextDepth()) { depth++; }

		return depth;
	}

	inline long star2(const char* path) noexcept
	{
		long depth = 0;

		Graph graph(path);
		while (!graph.nextDepth('a')) { depth++; }

		return depth;
	}

}