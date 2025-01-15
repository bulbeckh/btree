
#include "bt.h"

BTManager::BTManager(MCInstance* a, Node* root) : root(root), mc(a)
{

}


NodeExecutionResult BTManager::run()
{
	// Contains pointer to currently executing leaf node
	LeafNode** lf;

	NodeExecutionResult result;
	
	// Run this in a loop - in actual execution, th
	do {
		result = root->tick(this->mc, lf);
#ifdef BT_DEBUG
		BTManager::printResult(result);
#endif
	} while (result==NodeExecutionResult::RUNNING);
	
	return result;
}

void BTManager::pollInterrupt()
{
	// TODO check for and handle error states
}

#ifdef BT_DEBUG
void BTManager::printResult(NodeExecutionResult result)
{
	switch(result) {
		case NodeExecutionResult::SUCCESS:
			std::cout << "[RESULT] SUCCESS\n";
			break;
		case NodeExecutionResult::RUNNING:
			std::cout << "[RESULT] RUNNING\n";
			break;
		case NodeExecutionResult::FAILURE:
			std::cout << "[RESULT] FAILURE\n";
			break;
		default:
			std::cout << "[RESULT] error with NodeExecutionResult\n";
			break;
	}

	return;
}
#endif

