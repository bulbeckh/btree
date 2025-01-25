

/* 

BTManager should hold a tree of control (sequence/fallback) and action nodes. It should use a design pattern like
visitor to ensure that 

The AP_Scheduler class should schedule the execution of sensor libraries that update sensors with data periodically.

It should then use the remaining time to run the behaviour tree. At any one time, the behaviour tree keeps track of the
	currently executing node and will only change the node 

At 100Hz the following happens, the BTManager will call it's execute function which will execute the currently running node. If
	it returns SUCCESS or FAILURE then the logic to update the Behaviour tree will be handled by


Lets call the copter object MCInstance

- BTManager starts the execution and finds the correct leaf node.
- Then stores the location of this node and calls it's tick function at certain frequency - 100Hz?
- If the node returns success, then it passes it up to the parent node

CRTP pattern can be used here to achieve compile-time polymorphism as whole BT should be known at compile time.
See 'https://en.cppreference.com/w/cpp/language/crtp'

*/

#include <cstdint>

#define BT_DEBUG 1

#ifdef BT_DEBUG
	#include <iostream>
#endif


class MCInstance {
	// TODO
};


enum class NodeExecutionResult {
	SUCCESS,
	RUNNING, 
	FAILURE
};

// forward dec
class LeafNode;

class Node {

	public:

		Node() {};

		/* @brief Base class tick method.
		* @param mc Instance of a MinCopter object storing attitude and sensor readings.
		* @param leafnode A pointer to the leafnode that executed during this tick.
		* @returns result The NodeExecutionResult of this current tick.
		*/
		virtual NodeExecutionResult tick(MCInstance* mc, LeafNode** leafnode) = 0;

		/* @brief Get execution time information for this node
		*/
		float getExecutionTime() { return (float)(_time_sum/(1.0*_time_n)); }

	protected:
		uint32_t _time_sum=0;
		uint32_t _time_n=0;


};

class LeafNode : public Node {

	public:

		/* @brief LeafNode constructor.
		* @param mc The instance of the MinCopter.
		* @param btfunc The function to be run during the call to this LeafNode's tick.
		*/
		LeafNode(NodeExecutionResult (*btfunc)(MCInstance*));

		/*
		*/
		NodeExecutionResult tick(MCInstance* mc, LeafNode** leafnode) override;

	private:
		
		/* @brief bt_func is a function which is called during this nodes 'tick'. It takes an instance of MinCopter
		* and returns a NodeExecutionResult
		*/
		NodeExecutionResult (*bt_func)(MCInstance*);

};

class SequenceNode : public Node {

	public:
		SequenceNode(Node** list, uint32_t n);

		/*
		*/
		// TODO Generalise the first parameter to some sort of context that is passed in
		NodeExecutionResult tick(MCInstance* mc, LeafNode** leafnode) override;

	private:
		/* @brief The index of the child node that we are currently executing or about to execute
		*/
		int idx=0;

		/* @brief An array of child nodes to be executed
		*/
		Node** nodelist;

		/* @brief The number of child nodes in this sequence list. This should be known at compile time
		*/
		uint32_t n_nodes;

};

// NOTE FallbackNode is pretty much identical to SequenceNode except when checking for returns - need to rewrite to minimise code duplication
class FallbackNode : public Node {
	public:
		FallbackNode(Node** list, uint32_t n);

		/*
		*/
		NodeExecutionResult tick(MCInstance* mc, LeafNode** leafnode) override;
		
	private:
		/* @brief 
		*/
		int idx=0;
		
		/* @brief
		*/
		Node** nodelist;
	
		/* @brief
		*/
		uint32_t n_nodes;

};


class BTManager {

	public:
		BTManager(MCInstance* a, Node* root);

		BTManager() = delete;


		/* @brief 
		*/
		MCInstance* mc;


		/* @brief root stores the whole tree structure
		*/
		Node* root;

		// TODO If a leafnode returns running, then just keep calling that nodes subtick function directly
		// 	rather than query the graph again. Avoids using the virtual functions

		/* @brief Commence execution
		*/
		NodeExecutionResult run();

	private:
		void pollInterrupt();

#ifdef BT_DEBUG
		static void printResult(NodeExecutionResult result);
#endif

};



