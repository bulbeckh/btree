
#include "bt.h"

#include <iostream>


NodeExecutionResult newfunc(MCInstance* b) {
	std::cout << "[CALL] In newfunc\n";
	return NodeExecutionResult::SUCCESS;
}

NodeExecutionResult otherfunc(MCInstance* b) {
	std::cout << "[CALL] In otherfunc\n";
	return NodeExecutionResult::FAILURE;
}

int main(int argc, char** argv)
{

	MCInstance g;

	LeafNode a1(&newfunc);
	LeafNode a2(&newfunc);
	LeafNode a3(&newfunc);
	Node* lfarr[] = {&a1,&a2,&a3};

	SequenceNode sn(lfarr, sizeof(lfarr)/sizeof(Node*));

	LeafNode b2(&newfunc);
	Node* uparr[] = {&b2, &sn};

	SequenceNode sa(uparr, sizeof(uparr)/sizeof(Node*));

	// Init
	BTManager manager(&g, &sa);

	manager.run();

	std::cout << "Finished\n";

	return 0;
}

