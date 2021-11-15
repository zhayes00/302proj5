//Classes for the p5
//referenced from the Lab presentation Ashley gave

#ifndef CLASSES_HPP
#define CLASSES_HPP

class Edge {
	public:

		class Node *to;
		class Node *from;

		Edge(class Node *to, class Node *from, bool reverse_edge = false); //constructor for edges
		~Edge(){}; //default destruct

		Edge *reverse; //edge going other way
		int original; //original weight per edge
		int residual; //allows for the updated weighting during Edmonds-Karp

};

class Node {
	public:

		Node(int id, Node_Type type, string word = ""); //constructor for nodes
		~Node(){}; //default destruct

		int id;
		Node_Type type; //type of node it is (sourse, sink, word, or dice)
		vector<bool> letters; //length 26 w/ letters contained in word set to 1
		int visited; //for BFS
		vector<Edge*> adj; //adjacency list
		Edge *backedge; //previous edge for Edmonds-Karp
	
};

class Graph {
	public:

		Graph(); //constructor initailizes graph with source node
		~Graph(); //destructor to deallocate memory of graph

		Node *source; //source node
		vector<Node*> nodes; //holds the nodes
		vector<int> spellingIds; //order of flow to spell word
		int min_nodes; //min number of dice nodes

		//member functions
		void add_dice(string die, int id); //add dice nodes to graph
		void add_word(string word, int id); //add word (letter) nodes to graph
		bool BFS(); //bfs for Edmonds-Karp
		bool spell_word(); //runs Edmonds-Karp to see if we can spell the word
		void delete_word(); //deletes the word nodes but leaves dice nodes
		void print_node_order(string word); //print the spelling IDs and word

}

#endif
