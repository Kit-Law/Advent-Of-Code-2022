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
		std::vector<std::pair<std::vector<Node*>, Path>*> deapestNodeSets;
	public:
		Graph(const char* path, char startingPoint = 'S')
		{
			std::string buffer;
			std::fstream input(path);
			while (std::getline(input, buffer))
			{
				std::vector<Node*> nodeLine;
				for (char letter : buffer)
				{
					nodeLine.push_back(new Node(letter));
					if (nodeLine.back()->letter == startingPoint)
					{
						std::vector<Node*> root;
						root.push_back(nodeLine.back());
						deapestNodeSets.push_back(new std::pair<std::vector<Node*>, Path>(root, Path(nodeLine.back())));
					}
				}
				nodes.push_back(nodeLine);
			}

			constructEdges();
		}

		inline bool nextDepth()
		{
			for (std::pair<std::vector<Node*>, Path>* deapestNodes : deapestNodeSets)
			{
				std::vector<Node*> nextDeapestNodes;
				
				for (Node* node : deapestNodes->first)
				{
					if (node->letter == 'E')
						return true;
					else
						for (Node* edge : node->edges)
						{
							if ((node->letter == 'S' || (edge->letter <= node->letter + 1 && edge->letter != 'E') ||
								(edge->letter == 'E' && node->letter == 'z')) && !deapestNodes->second.visited(edge))
							{
								nextDeapestNodes.push_back(edge);
								deapestNodes->second.visitNode(edge);
							}
						}
				}

				deapestNodes->first.clear();
				deapestNodes->first = nextDeapestNodes;
			}
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

		Graph graph(path, 'a');
		while (!graph.nextDepth()) { depth++; }

		return depth;
	}

}