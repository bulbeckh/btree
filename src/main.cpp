
#include "bt.h"

#include <iostream>


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

	LeafNode a1(&retsuc);
	LeafNode a2(&retsuc);
	LeafNode a3(&retsuc);

	Node* lfarr[] = {&a1,&a2,&a3};

	SequenceNode sn(lfarr, sizeof(lfarr)/sizeof(Node*));

	LeafNode f1(&retfai);
	LeafNode f2(&retsuc);
	Node* fb_arr[] = {&f1, &f2};

	FallbackNode fa(fb_arr, sizeof(fb_arr)/sizeof(Node*));

	LeafNode b2(&retsuc);
	Node* uparr[] = {&b2, &sn, &fa};

	SequenceNode sa(uparr, sizeof(uparr)/sizeof(Node*));

	// Init
	BTManager manager(&g, &sa);

	manager.run();

	std::cout << "Finished\n";

	return 0;
}

