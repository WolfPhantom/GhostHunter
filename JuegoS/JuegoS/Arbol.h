#include <functional>
#include <stack>
#include <queue>
#include <algorithm>

#define NONE 0
#define INF 2147483647

template <typename T>
class AVLTree {
	struct Node;

	Node* root;
	std::function<int(T, T)> compare;

	void rotateLeft(Node*& node);
	void rotateRight(Node*& node);
	void balance(Node*& node);

	void add(Node*& node, T element);
	bool remove(Node*& node, T element);
	unsigned int length(Node* node);
	int height(Node* node);
	void update(Node* node);
	T search(Node* node, T key);
	void preorder(Node* node, std::function<void(T)> proc, int& i, int limit);
	void inorder(Node* node, std::function<void(T)> proc, int& i, int limit);
	void postorder(Node* node, std::function<void(T)> proc, int& i, int limit);

public:
	AVLTree();
	AVLTree(std::function<int(T, T)> compare) : compare(compare), root(nullptr) {}
	~AVLTree();

	unsigned int length();
	int height();
	void add(T element);
	bool remove(T element);
	T search(T key);
	void preorder(std::function<void(T)> proc, int limit = INF);
	void inorder(std::function<void(T)> proc, int limit = INF);
	void postorder(std::function<void(T)> proc, int limit = INF);
	void bfs(std::function<void(T)> proc, int limit = INF);
};

template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {
	compare = [](T a, T b) { return a - b; };
}

template <typename T>
AVLTree<T>::~AVLTree() {
	std::stack<Node*> st;
	st.push(root);
	while (!st.empty()) {
		Node* node = st.top();
		st.pop();
		if (node != nullptr) {
			st.push(node->leftChild);
			st.push(node->rightChild);
			delete node;
		}
	}
}

template <typename T>
struct AVLTree<T>::Node {
	T element;
	unsigned int length;
	unsigned int height;
	Node* leftChild;
	Node* rightChild;

	Node(T element = NONE, unsigned int length = 1, unsigned int height = 0,
		Node* leftChild = nullptr, Node* rightChild = nullptr)
		: element(element), length(length), height(height),
		leftChild(leftChild), rightChild(rightChild) {}
};

template <typename T>
unsigned int AVLTree<T>::length() {
	return length(root);
}

template <typename T>
unsigned int AVLTree<T>::length(Node* node) {
	return node != nullptr ? node->length : 0;
}

template <typename T>
int AVLTree<T>::height() {
	return height(root);
}

template <typename T>
int AVLTree<T>::height(Node* node) {
	return node != nullptr ? node->height : -1;
}

template <typename T>
void AVLTree<T>::update(Node* node) {
	if (node != nullptr) {
		node->height = 1 + std::max(height(node->leftChild), height(node->rightChild));
		node->length = 1 + length(node->leftChild) + length(node->rightChild);
	}
}

template <typename T>
void AVLTree<T>::rotateLeft(Node*& node) {
	Node* d = node->rightChild;
	node->rightChild = d->leftChild;
	d->leftChild = node;
	update(d->leftChild);
	update(d);
	node = d;
}

template <typename T>
void AVLTree<T>::rotateRight(Node*& node) {
	Node* b = node->leftChild;
	node->leftChild = b->rightChild;
	b->rightChild = node;
	update(b->rightChild);
	update(b);
	node = b;
}

template <typename T>
void AVLTree<T>::balance(Node*& node) {
	int hl = height(node->leftChild);
	int hr = height(node->rightChild);
	if (hl - hr < -1) {
		hl = height(node->rightChild->leftChild);
		hr = height(node->rightChild->rightChild);
		if (hl > hr) {
			rotateRight(node->rightChild);
		}
		rotateLeft(node);
	}
	else if (hl - hr > 1) {
		hl = height(node->leftChild->leftChild);
		hr = height(node->leftChild->rightChild);
		if (hl < hr) {
			rotateLeft(node->leftChild);
		}
		rotateRight(node);
	}
	else {
		update(node);
	}
}

template <typename T>
void AVLTree<T>::add(T element) {
	add(root, element);
}

template <typename T>
void AVLTree<T>::add(Node*& node, T element) {
	if (node == nullptr) {
		node = new Node(element);
	}
	else {
		if (compare(element, node->element) < 0) {
			add(node->leftChild, element);
		}
		else {
			add(node->rightChild, element);
		}
		balance(node);
	}
}

template <typename T>
bool AVLTree<T>::remove(T element) { return false; }
template <typename T>
bool AVLTree<T>::remove(Node*& node, T element) { return false; }

template <typename T>
T AVLTree<T>::search(T key) {
	return search(root, key);
}

template <typename T>
T AVLTree<T>::search(Node* node, T key) {
	if (node != nullptr) {
		if (compare(key, node->element) == 0) {
			return node->element;
		}
		else if (compare(key, node->element) < 0) {
			return search(key, node->leftChild);
		}
		else {
			return search(key, node->rightChild);
		}
	}
	else {
		return NONE;
	}
}

template <typename T>
void AVLTree<T>::preorder(std::function<void(T)> proc, int limit) {
	int i = 0;
	preorder(root, proc, i, limit);
}

template <typename T>
void AVLTree<T>::preorder(Node* node, std::function<void(T)> proc, int& i, int limit) {
	if (node != nullptr && i < limit) {
		if (i < limit) {
			proc(node->element);
			i++;
		}
		preorder(node->leftChild, proc, i, limit);
		preorder(node->rightChild, proc, i, limit);
	}
}

template <typename T>
void AVLTree<T>::inorder(std::function<void(T)> proc, int limit) {
	int i = 0;
	inorder(root, proc, i, limit);
}

template <typename T>
void AVLTree<T>::inorder(Node* node, std::function<void(T)> proc, int& i, int limit) {
	if (node != nullptr && i < limit) {
		inorder(node->leftChild, proc, i, limit);
		if (i < limit) {
			proc(node->element);
			i++;
		}
		inorder(node->rightChild, proc, i, limit);
	}
}

template <typename T>
void AVLTree<T>::postorder(std::function<void(T)> proc, int limit) {
	int i = 0;
	postorder(root, proc, i, limit);
}

template <typename T>
void AVLTree<T>::postorder(Node* node, std::function<void(T)> proc, int& i, int limit) {
	if (node != nullptr && i < limit) {
		postorder(node->leftChild, proc, i, limit);
		postorder(node->rightChild, proc, i, limit);
		if (i < limit) {
			proc(node->element);
			i++;
		}
	}
}

template <typename T>
void AVLTree<T>::bfs(std::function<void(T)> proc, int limit) {
	int i = 0;
	std::queue<Node*> qu;
	qu.push(root);
	while (!qu.empty() && i++ < limit) {
		Node* node = qu.front();
		qu.pop();
		if (node != nullptr) {
			proc(node->element);
			qu.push(node->leftChild);
			qu.push(node->leftRight);
		}
	}
}