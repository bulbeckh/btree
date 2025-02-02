
#include "bt.h"

#include <iostream>

// NOTE Use a namespace here for these global variables
#define LEAF(name, func) LeafNode name(func)

/* NOTE There are a couple of options here for the sequence/fallback macros.
* We could define as SEQUENCE(name, numberElements, ...) but that introduces
* potential uncaught errors if the numberElements is incorrect.
*
* The alternative is to ..
*/
#define SEQUENCE(name, numelements, ...) SequenceNode name((Node*[]){__VA_ARGS__}, numelements)

#define FALLBACK(name, numelements, ...) FallbackNode name((Node*[]){__VA_ARGS__}, numelements)

NodeExecutionResult retsuc(MCInstance* b) {
	std::cout << "[CALL] In retsec\n";
	return NodeExecutionResult::SUCCESS;
}

NodeExecutionResult retfai(MCInstance* b) {
	std::cout << "[CALL] In retfai\n";
	return NodeExecutionResult::FAILURE;
}

int main(int argc, char** argv)
{

	MCInstance g;

	/* Construction of the following bt

	- SequenceNode (sa)
		- LeafNode (b2)
		- SequenceNode (sn)
			- LeafNode (a1)
			- LeafNode (a2)
			- LeafNode (a3)
		- FallbackNode (fa)
			- LeafNode (f1)
			- LeafNode (f2)
	*/

	// TODO This is what needs to be fixed - intitialisation of nodes in tree
	
	LEAF(a1, &retsuc);
	LEAF(a2, &retsuc);
	LEAF(a3, &retsuc);

	/*
	LeafNode a1(&retsuc);
	LeafNode a2(&retsuc);
	LeafNode a3(&retsuc);
	*/

	SEQUENCE(sn,3, &a1, &a2, &a3);
	/*
	Node* lfarr[] = {&a1,&a2,&a3};
	SequenceNode sn(lfarr, sizeof(lfarr)/sizeof(Node*));
	*/

	LEAF(f1, &retfai);
	LEAF(f2, &retsuc);
	/*
	LeafNode f1(&retfai);
	LeafNode f2(&retsuc);
	*/

	FALLBACK(fa, 2, &f1, &f2);
	/*
	Node* fb_arr[] = {&f1, &f2};
	FallbackNode fa(fb_arr, sizeof(fb_arr)/sizeof(Node*));
	*/

	LEAF(b2, &retsuc);
	/*
	LeafNode b2(&retsuc);
	*/

	SEQUENCE(sa, 3, &b2, &sn, &fa);
	/*
	Node* uparr[] = {&b2, &sn, &fa};
	SequenceNode sa(uparr, sizeof(uparr)/sizeof(Node*));
	*/

	// Init
	BTManager manager(&g, &sa);

	manager.run();

	std::cout << "Finished\n";

	return 0;
}

