//Classes for the p5
//referenced from the Lab presentation Ashley gave

#include <string>
#include <vector>

typedef enum {SOURCE, SINK, WORD, DICE} Node_Type;

using namespace std;

#ifndef CLASSES_HPP
#define CLASSES_HPP

class Edge {
	public:

		class Node *to;
		class Node *from;

		Edge(class Node *to1, class Node *from1, bool reverse_edge = false); //constructor for edges

		Edge *reverse; //edge going other way
		int original; //original weight per edge
		int residual; //allows for the updated weighting during Edmonds-Karp

};

class Node {
	public:

		Node(Node_Type type, string word = ""); //constructor for nodes

		Node_Type type; //type of node it is (sourse, sink, word, or dice)
		vector<bool> letters; //length 26 w/ letters contained in word set to 1
		int visited; //for BFS
		vector<Edge*> adj; //adjacency list
		Edge *backedge = nullptr; //previous edge for Edmonds-Karp
	
};

class Graph {
	public:

		Graph(); //constructor initailizes graph with source node
		~Graph(); //destructor to deallocate memory of graph
		
		Node *sink; //Permanently keeps track of the SINK node
		vector<Node*> nodes; //holds the nodes
		vector<int> spellingIds; //order of flow to spell word
		int min_nodes; //Number of source + dice nodes

		//member functions
		void add_dice(string die); //add dice nodes to graph
		void add_word(string word); //add word (letter) nodes to graph
		bool BFS(); //bfs for Edmonds-Karp
		bool spell_word(); //runs Edmonds-Karp to see if we can spell the word
		void delete_word(); //deletes the word nodes but leaves dice nodes
		void print_node_order(string word); //print the spelling IDs and word

};

#endif
