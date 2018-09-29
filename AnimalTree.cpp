#include "AnimalTree.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Node.h"

using namespace std;

AnimalTree::AnimalTree(){ // default constructor
	saveFilename = "defaultAnimalSave.txt"; // default save file

	root = defaultStartup();

	current = root;
}

AnimalTree::AnimalTree(string filename) {
	saveFilename = filename;

	root = load(filename);

	current = root;
}

AnimalTree::~AnimalTree(){
}

// creates a tree with a default setup
Node* AnimalTree::defaultStartup() {
	Node* newRoot = new Node("Does your animal swim underwater?", 0, 0, 0);

	Node* newYes = new Node("Shark", 0, 0, newRoot);
	Node* newNo = new Node("Horse", 0, 0, newRoot);

	newRoot->setYes(newYes);
	newRoot->setNo(newNo);

	return newRoot;
}

Node* AnimalTree::getCurrent() {
	return current;
}

void AnimalTree::resetCurrent() {
	current = root;
}

void AnimalTree::currentGoYes() {
	if (!current->isLeaf()) {
		current = current->getYes();
	}
}

void AnimalTree::currentGoNo() {
	if (!current->isLeaf()) {
		current = current->getNo();
	}
}

// insert a new question and answer into the tree
void AnimalTree::learnNewAnimal(string newAnimal, string newQuestion) {
	Node* originalGuess = current;
	Node* originalParent = current->getParent();

	Node* newQuestionNode = new Node(newQuestion, 0, 0, originalParent);
	Node* newAnimalNode = new Node(newAnimal, 0, 0, newQuestionNode);

	newQuestionNode->setNo(originalGuess);
	originalGuess->setParent(newQuestionNode);

	newQuestionNode->setYes(newAnimalNode);

	// if the originalGuess was on the 'yes' side of the parent
	if (originalParent->getYes() == originalGuess) {
		originalParent->setYes(newQuestionNode);
	}
	else { // if it was on the 'no' side
		originalParent->setNo(newQuestionNode);
	}
}

// save the tree to a file
void AnimalTree::save(string filename) {
	// basically just does DFS and saves to a text file as it goes

	ofstream out;
	out.open(filename);

	string savetext;

	saveRecursion(root, savetext); // launch recursive funcion that does the real work

	out << savetext;
	out << "END";
	out.close();
}

void AnimalTree::saveRecursion(Node* currentRec, string& savetext) {
	savetext = savetext + currentRec->getText() + "\n";

	// if this node is a leaf
	if (currentRec->isLeaf()) {
		savetext = savetext + "LEAF\n";
	}
	else { // not a leaf
		savetext = savetext + "NOTLEAF\n";

		saveRecursion(currentRec->getNo(), savetext);
		saveRecursion(currentRec->getYes(), savetext);
	}
}

// load a tree from a file
Node* AnimalTree::load(string filename) {
	ifstream in;
	in.open(filename);

	// put all the file text into a vector split by newline
	vector<string> fileText = vector<string>();

	string currentLine;
	bool readingLines = true;

	while (readingLines) {

		getline(in, currentLine);

		if (currentLine == "END") {
			readingLines = false; // stop and quit
		}
		else {
			fileText.push_back(currentLine);
		}
	}

	in.close();

	int bottom = 0;
	return loadRecursion(fileText, 0, bottom, 0); // launch the recursive function that does the real work
}

Node* AnimalTree::loadRecursion(vector<string>& fileText, int currentLine, int& bottom, Node* previousNode) {

	if (fileText[currentLine + 1] == "NOTLEAF") {
		//cout << "NOTLEAF: " << fileText[currentLine] << endl;

		Node* node = new Node(fileText[currentLine], 0, 0, previousNode);

		node->setNo(loadRecursion(fileText, currentLine + 2, bottom, node));

		node->setYes(loadRecursion(fileText, bottom, bottom, node));

		return node;
	}
	else { // otherwise, leaf
		//cout << "LEAF: " << fileText[currentLine] << endl;

		bottom = currentLine + 2;
		return new Node(fileText[currentLine], 0, 0, previousNode);
	}
}
