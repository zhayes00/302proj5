#include "classes.hpp"
#include <queue>
#include <iostream>

using namespace std;

//Edge Stuff~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Edge::Edge(class Node *to1, class Node *from1, bool reverse_edge) {

	//Setting parameters to data members
	this->to = to1;
	this->from = from1;
		
	//If this is not the reverse edge, we need to create it and set its "to" and "from"
	//nodes to the opposite if this instance. Also, we set both edges' "reverse" pointers
	//to each other.
	if (!reverse_edge) {
		this->original = 1;
		this->residual = 0;
		
		this->reverse = new Edge(from, to, 1);
		this->reverse->reverse = this;
	}
	else {
		this->original = 0;
		this->residual = 1;

	}
}




//Node Stuff~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Node::Node(Node_Type type, string word) {

	/* need to:
	- DONE: Set "type" data member with value of parameter
	- DONE: letters.resize(26, 0);
	- DONE: Process "word" parameter into "letters" vector
	- DONE: Set Node::visited to 0
	- Do we figure out the adjacency list here, or somewhere else?
	
	*/
	
	//Set "type" data member with value of parameter
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

	//Create SOURCE node, which will always be at index 0 in "nodes" vector
		this->nodes.push_back(new Node(SOURCE));
		this->min_nodes = 1; //we just have the source node right now
		
	//Create SINK node, which is not in "nodes" vector
		this->sink = new Node(SINK);
}

Graph::~Graph(){

	//delete edges first, then nodes
	
	//for each node
	for (vector<Node*>::size_type i=0; i < this->nodes.size(); ++i) {
		//for each edge in this node's adj list
		for (vector<Edge*>::size_type j=0; j < this->nodes.at(i)->adj.size(); ++j) {
			//delete it
			delete this->nodes.at(i)->adj.at(j);
		}
	}
	
	//for each node again (to delete it this time)
	for (vector<Node*>::size_type i=0; i < this->nodes.size(); ++i) {
		// delete this->nodes.at(i)->backedge;
		delete this->nodes.at(i);
	}
	
	//we have not deleted SINK since it is not in the vector "nodes", however, we need to make sure its member "adj" is clear before we delete it
	for (vector<Node*>::size_type i=0; i < this->sink->adj.size(); ++i) {
		delete this->sink->adj.at(i);
	}
	this->sink->adj.clear();
	delete this->sink->backedge;
	delete this->sink;
	
}

void Graph::add_dice(string die) {
	/*
		1. Create a new DICE node.
		2. Create an edge from SOURCE to this new node
		3. Add new edge to adjacency list of SOURCE
		4. Add new edge->reverse to adj. list of new DICE node
		5. Add 1 to this->min_nodes
	*/
	
	this->nodes.push_back(new Node(DICE, die)); //1
	Edge *tempEdge = new Edge(this->nodes.back(), this->nodes.front()); //2
	this->nodes.front()->adj.push_back(tempEdge); //3
	this->nodes.back()->adj.push_back(tempEdge->reverse); //4
	this->min_nodes += 1; //5
	
}

void Graph::add_word(string word){
	/*
		For each letter:
			1. Create a new WORD node
			2. For each DICE node that contains the letter we're looking at:
				1. Create an edge from the DICE node to the WORD node
				2. Add the new edge to the adjacency list of the DICE node
				3. Add new edge->reverse to adj. list of new WORD node
			3. Create a new edge from the new WORD node to the SINK node
			4. Add edge to adj. list of both its' nodes.
	*/
	
	for (string::size_type i=0; i < word.size(); ++i) { //for each letter in the word
		this->nodes.push_back(new Node(WORD, string(1, word.at(i)))); //create a new WORD node with this letter
		
		for (vector<Node*>::size_type j=0; j < this->nodes.size(); ++j) { //for each existing DICE node (below we skip the ones we don't need)
			//continue if this is not a DICE node, or it doesn't have this letter.
			if ( (this->nodes.at(j)->type != DICE) || (!(this->nodes.at(j)->letters.at(word.at(i)-65))) ) continue;
			
			//Create an edge from the DICE node to the WORD node, updating adjacency lists.
			Edge *tempEdge = new Edge(this->nodes.back(), this->nodes.at(j));
			this->nodes.at(j)->adj.push_back(tempEdge);
			this->nodes.back()->adj.push_back(tempEdge->reverse);
		}
		
		//Creating a new edge from new WORD node to SINK node, and updating adj. lists.
		Edge *tempEdge = new Edge(this->sink, this->nodes.back());
		this->nodes.back()->adj.push_back(tempEdge);
		this->sink->adj.push_back(tempEdge->reverse);
	}
}

bool Graph::BFS() {

	//set up queue w/ source node inside
	//
	//while loop until queue is empty
	//clear backedges & visited aspects
	//read in connections (& set their backedges) and store them into queue
	//	do not read in any that are visited or who's edge's Original = 0
	//set visited to current & remove it from the queue
	//go to next in queue
	//break when current finds Sink
	//	if no path is found and while loop breaks naturally, then return false
	//
	//follow backedges for path from sink to source
	//	set the Original & Residuals while following
	//		as well as the reverse edges' as well
	//return true if all is well
	
	
	//Setting up Queue for BFS usage, starting with the source node
	queue<Node*> bfsq; //'bfs' 'q'ueue
	bfsq.push(this->nodes.at(0)); //push in the source node

	bool found_sink = false;


	//Clear Backedges & Visited on all Nodes
	for (vector<Node*>::size_type i = 0; i < this->nodes.size(); ++i) {
		this->nodes.at(i)->visited = 0;
		this->nodes.at(i)->backedge = nullptr;
	}
	this->sink->visited = 0;
	this->sink->backedge = nullptr;


	//Main Action Loop
	while (!bfsq.empty()) {

		if (bfsq.front()->type == SINK) {
			found_sink = true;
			break;
		}

		//Read in adjacencies into the queue
		for (vector<Edge*>::size_type i = 0; i < bfsq.front()->adj.size(); ++i) {

			if ( (bfsq.front()->adj.at(i)->to->visited == 0) && (bfsq.front()->adj.at(i)->original == 1) ) {

				//Push the adjacent node into the queue
				bfsq.push( bfsq.front()->adj.at(i)->to );
				//set the adjacent node's backedge
				bfsq.back()->backedge = bfsq.front()->adj.at(i)->reverse;
				
				bfsq.front()->adj.at(i)->to->visited = 1;
			}
		}

		//Set the current node's visited to 1 & remove it from the bfsq
		if (!bfsq.empty()) {
			// bfsq.front()->visited = 1;
			bfsq.pop();
		}
	}

	//BFS Path Checking
	if (found_sink == false) {
		return false;
	}
	else {

		//Follow Backedges from SINK to SOURCE
		//Change Original & Residual along the way
		//	including Rev-Edges
		
		Node* temp = this->sink;


		//Loop to trace back edges from SINK to SOURCE
		while (temp->type != SOURCE) {

			//Set the (Normal & Reverse) edge's O & R
			//Set "Reverse"/Backedges
			temp->backedge->original = !temp->backedge->original;
			temp->backedge->residual = !temp->backedge->residual;
			//Set Standard Edge's
			temp->backedge->reverse->original = !temp->backedge->reverse->original;
			temp->backedge->reverse->residual = !temp->backedge->reverse->residual;

			/*
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TESTER
			// cout << "Edge from " << temp->type << " to " << temp->backedge->to->type << " with O = " << temp->backedge->original  << endl;
			printf("Temp == %p\n", temp);
			printf("SINK == %p\n", this->sink);
			printf("SINK->backedge->to == %p\n", this->sink->backedge->to);
			printf("SINK->backedge->to->backedge->to == %p\n", this->sink->backedge->to->backedge->to);
			// exit(1);
			*/

			//Trace back the backedge
			temp = temp->backedge->to;

		}


		return true;

	}


}

bool Graph::spell_word() {

	//Call BFS until it returns false
	//	put in while
	//
	//Check WORD nodes' edges, if Residual = 1 for all edges from WORD -> SINK, then word is spelled
	//	While checking there...
	//		look @ WORD node & use the edge that has an Original = 1 (it's reverse edge to the DICE node)
	//			store this "used" DICE node's "ID" into spellingIds for output
	//	
	//	if all is well, return true
	

	//Run BFS until it cannot find anymore paths
	while(BFS());

	//Check Sink's backedges' reverses' Residuals
	for (vector<Edge*>::size_type i = 0; i < this->sink->adj.size(); ++i) {

		//if the original is 1, then is was never "traveled" and therefore, the word was not spelled
		if ( this->sink->adj.at(i)->reverse->original == 1 ) {
			return 0;
		}

		//Checking to see what die were used for each letter
		for (vector<Edge*>::size_type j = 0; j < this->sink->adj.at(i)->to->adj.size(); ++j) {

			//If the WORD node has an edge with O = 1, then it should track back to the DICE node used
			if ( this->sink->adj.at(i)->to->adj.at(j)->original == 1 ) {

				//Acquire the relative DICE id for the output
				for (vector<Node*>::size_type k = 0; k < this->nodes.size(); ++k) {

					if ( (this->nodes.at(k)->type == DICE) && (this->nodes.at(k) == this->sink->adj.at(i)->to->adj.at(j)->to) ) {
						spellingIds.push_back( k - 1 );
					}
				}
			}
		}
	}
	
	return 1;
}

/*BROKEN do not use.
void Graph::delete_word() {
//deletes word nodes and all edges between them and dice nodes, and sink node
//delete edges first, then nodes, then resize vector to min_nodes
	
	//for each node
	for (vector<Node*>::size_type i=0; i < this->nodes.size(); ++i) {
		//for each edge in this node's adj list
		for (vector<Edge*>::size_type j=0; j < this->nodes.at(i)->adj.size(); ++j) {
			//if this edge is going to or from a WORD or SINK node, delete it
			if ( (this->nodes.at(i)->adj.at(j)->to->type == WORD) ||
				 (this->nodes.at(i)->adj.at(j)->to->type == SINK) ||
				 (this->nodes.at(i)->adj.at(j)->from->type == WORD) ||
				 (this->nodes.at(i)->adj.at(j)->from->type == SINK) ) {
				delete this->nodes.at(i)->adj.at(j);
			} //wow, I probably should have used vector iterators instead of whatever the hell this is. Too late!
		}
	}
	
	//for each node again (to delete it this time if it is a WORD)
	for (vector<Node*>::size_type i=0; i < this->nodes.size(); ++i) {
		if (this->nodes.at(i)->type == WORD)
			delete this->nodes.at(i);
	}
	
	//we do not delete SINK since it is not in the vector, however, we need to make sure its members "visited", "adj" and "backedge" are clear
	this->sink->visited = 0;
	for (vector<Node*>::size_type i=0; i < this->sink->adj.size(); ++i) {
		delete this->sink->adj.at(i);
	}
	this->sink->adj.clear();
	this->sink->backedge = nullptr;
	
	//resize vector
	this->nodes.resize(this->min_nodes);
}

void Graph::print_node_order(string word) {


} */
