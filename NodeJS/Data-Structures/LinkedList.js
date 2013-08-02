// The header of the Linked List
function LinkedList() {
	this.head = null;
	this.length = 0;
};

// Adding a node to the Linked List
LinkedList.prototype.add = function(value){
	
	// The current_node Node
	var current = this.head;
	var repeat = false;

	// Checking if the element is already there
	if(this.length != 0 && current == null){
		do{
			// If the element is in the area, set "repeat" to true
			if(current.value == value){
				repeat = true;
			}	
			current = current.next;
		} while(current);
	}
	// If repeat is false, then proceed
	if(repeat == false){
		// Declaring and creating a new Node
		var new_node = {
			value: value,
			next: null
		};

		// The current_node Node
		var current_node;

		// Traversal through the Linked List
		if(this.head === null){
			this.head = new_node;
		} else {
			current_node = this.head;
			// While there is a next node
			while(current_node.next){
				current_node = current_node.next;
			}
			// Set the next node of the last element 
			// to the newly created Node
			current_node.next = new_node;
		}
		// Increases length of the Linked List
		this.length++;
		// Returns the new Node
		return new_node;
	} else {
		// Else if repeat is true, then element is already there
		console.log("Element is already there");
	}
};

LinkedList.prototype.remove = function(node){
	// Sets current node and value to the node's value
	var current_node, value = node.value;

	if(this.head !== null){
		// If the "Head" is the Node to remove
		if(this.head === node){
			// sets Head to next Node
			this.head = this.head.next;
			node.next = null;
			return value;
		}
		// Traversing through the Linked List
		current_node = this.head;
		while(current_node.next){
			// If the current node equals the Node
			if(current_node.next === node){
				current_node.next = node.next;
				return value;
			}
			current_node = current_node.next;
		}
	}
};