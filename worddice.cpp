//Project 5: Word Dice

#include <cstdio>
#include <vector>
#include <string>
#include "classes.hpp"
// #pragma once

using namespace std;

vector<string> ReadInFile(string filePath);

int main(int argc, char **argv) {
	
	//Variable decalration
		vector<string> inDice, inWords; //Holds the parsed lists of dice and words taken in
	
	//Checking arguments
		if (argc != 3) {
			fprintf(stderr, "Usage: ./worddice Dice_File Words_File\n");
			return 1;
		}
	
	//Processing input files
		inDice = ReadInFile(string(argv[1]));
		inWords = ReadInFile(string(argv[2]));
		
	//Creating graph and populating it with dice
		Graph myGraph;
		for (vector<string>::size_type i=0; i < inDice.size(); ++i)
			myGraph.add_dice(inDice.at(i));

	//add classes from piazza?
	//use edmonds-karp
	//find max flow will solve
	
	//pieces:							|	"anticipated weight"
	//	class & member function setup	|	medium?
	//	edmonds-karp & BFS				|	heavy
	//	input/output					|	light
	//	

	return 0;
}

vector<string> ReadInFile(string filePath) {
	vector<string> returnVec; //Holds the values read in
	FILE *fPtr = fopen(filePath.c_str(), "r"); //our file pointer
	
	if (fPtr == NULL) { //checking that the file was opened
		fprintf(stderr, "%s%s%s\n", "Failed to read file \"", filePath.c_str(), "\"");
		exit(1);
	}
	
	//Main loop to read in the file
	for (char garb; fscanf(fPtr, " %1c", &garb) >0; garb = '\0') { //Is there another non-whitespace character past the current position?
		fseek(fPtr, -1, SEEK_CUR); //If so, we just moved forward to check, so we need to move back now
		char tmpStr[100] = "";
		fscanf(fPtr, " %s ", tmpStr);
		returnVec.emplace_back(tmpStr);
	}
	
	fclose(fPtr);
	return returnVec;
}
