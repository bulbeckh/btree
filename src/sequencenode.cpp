
#include "bt.h"



SequenceNode::SequenceNode(Node** list, uint32_t n) : Node(), nodelist(list), n_nodes(n) {
#ifdef BT_DEBUG
	std::cout << "[INIT] Sequence node at " << this << " with " << n << " nodes\n";
#endif
}

NodeExecutionResult SequenceNode::tick(MCInstance* mc, LeafNode** leafnode)
{
#ifdef BT_DEBUG
	std::cout << "[CALL] Tick - SequenceNode at " << this << " with idx " << this->idx << " and n_nodes " << this->n_nodes << "\n";
#endif

	// Call to virtualised tick function for each child node
	NodeExecutionResult result = this->nodelist[this->idx]->tick(mc, leafnode);

	// On FAILURE of SequenceNode, reset this node and return failure
	if (result==NodeExecutionResult::FAILURE) {
		this->idx=0;
		return NodeExecutionResult::FAILURE;
	}

	// On RUNNING
	if (result==NodeExecutionResult::RUNNING) {
		return NodeExecutionResult::RUNNING;
	}

	// On Success, check if this is the last node and reset and return success if so
	if (result==NodeExecutionResult::SUCCESS) {
		if (this->idx==this->n_nodes-1) {
			this->idx=0;
			return NodeExecutionResult::SUCCESS;
		}
		
		this->idx++;
		return NodeExecutionResult::RUNNING;
	}

	// TODO this will throw compiler error for no return of non-void function

}


