# btree
Behaviour Tree Library for AVR Microcontrollers

## \#TODO
- [ ] Implement remaining node types (fallback, decorators)
- [ ] Add .pc interface and CMake interface to library code

## Usage
TODO

## Node Types

### `LeafNode`
Node that runs a callback function when ticked. Callback must return a `NodeExecutionResult`.

### `SequenceNode`
Node that holds a list of other nodes. Will iterate through child nodes until a child node returns `NodeExecutionResult::FAILURE` or the end is reached.

### `FallbackNode`
TODO





