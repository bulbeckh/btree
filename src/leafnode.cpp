

#include "bt.h"

LeafNode::LeafNode(NodeExecutionResult (*bt_func)(MCInstance*)) : Node(), bt_func(bt_func)
{ 

#ifdef BT_DEBUG
	std::cout << "[INIT] LeafNode at " << this << "\n";
#endif
}

NodeExecutionResult LeafNode::tick(MCInstance* mc, LeafNode** leafnode)
{
#ifdef BT_DEBUG
	std::cout << "[CALL] Tick - LeafNode at " << this << "\n";
#endif

	// Call function
	NodeExecutionResult result = (this->bt_func)(mc);

	// Update the leafnode pointer to itself
	// TODO Change BTManager so that it does not traverse the tree everytime, only when the leafnode returns a SUCCESS or FAILURE
	(*leafnode) = this;
	
	return result;
}

