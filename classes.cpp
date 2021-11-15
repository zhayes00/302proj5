#include "classes.hpp"

using namespace std;

//Edge Stuff~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Edge::Edge(class Node *to, class Node *from, bool reverse_edge) {

	//Setting parameters to data members
	Edge::to = to;
	Edge::from = from;
		

}




//Node Stuff~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Node::Node(int id, Node_Type type, string word) {

	/* need to:
	- DONE: Set "id" and "type" data members with value of parameters
	- DONE: letters.resize(26, 0);
	- DONE: Process "word" parameter into "letters" vector
	- DONE: Set Node::visited to 0
	- Do we figure out the adjacency list here, or somewhere else?
	
	*/
	
	//Set "id" and "type" data members with value of parameters
	Node::id = id;
	Node::type = type;
	
	Node::visited = 0;
	
	//Process "word" parameter into "letters" vector
	Node::letters.resize(26,0);
	for (string::size_type i=0; i < word.size(); ++i) {
		Node::letters.at( word.at(i) - 65 ) = 1;
	}
}




//Graph Stuff~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Graph::Graph(){

	//Construct
	
}

Graph::~Graph(){

	//Destruct
	
}

void Graph::add_dice(string die, int id) {
	
	
}

void Graph::add_word(string word, int id){


}

bool Graph::BFS() {


}

bool Graph::spell_word() {


}

void Graph::delete_word() {


}

void Graph::print_node_order(string word) {


}
