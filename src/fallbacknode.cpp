
#include "bt.h"

FallbackNode::FallbackNode(Node** list, uint32_t n) : Node(), nodelist(list), n_nodes(n) {
#ifdef BT_DEBUG
	std::cout << "[INIT] Fallback node at " << this << " with " << n << " nodes\n";
#endif
}

NodeExecutionResult FallbackNode::tick(MCInstance* mc, LeafNode** leafnode)
{
#ifdef BT_DEBUG
	std::cout << "[CALL] Tick - Fallback node at " << this << " with idx " << this->idx << " and n_nodes " << this->n_nodes << "\n";
#endif

	// Call to virtualised tick function for each child node
	NodeExecutionResult result = this->nodelist[this->idx]->tick(mc, leafnode);

	// On FAILURE of FallbackNode, move to next node or return failure
	if (result==NodeExecutionResult::FAILURE) {
		if (this->idx==this->n_nodes-1) {
			this->idx=0;
			return NodeExecutionResult::FAILURE;
		}
		
		this->idx++;
		return NodeExecutionResult::RUNNING;
	}

	// On RUNNING
	if (result==NodeExecutionResult::RUNNING) {
		return NodeExecutionResult::RUNNING;
	}

	// On Success, check if this is the last node and reset and return success if so
	// On Success, reset node and return success
	if (result==NodeExecutionResult::SUCCESS) {
		this->idx=0;
		return NodeExecutionResult::SUCCESS;
	}
		
	// TODO this will throw compiler error for no return of non-void function
}


