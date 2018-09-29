#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Node.h"

using namespace std;

class AnimalTree{

public:
	AnimalTree();
	AnimalTree(string filename);
	virtual ~AnimalTree();

	virtual Node* getCurrent();
	virtual void resetCurrent();

	virtual void currentGoYes();
	virtual void currentGoNo();

	virtual void learnNewAnimal(string newAnimal, string newQuestion);

	virtual void save(string filename);
	virtual Node* load(string filename);

private:
	virtual Node* defaultStartup();

	virtual void saveRecursion(Node* currentRec, string& savetext);
	Node* loadRecursion(vector<string>& fileText, int currentLine, int& bottom, Node* previousNode);

	string saveFilename;

	Node* root;
	Node* current;

};

