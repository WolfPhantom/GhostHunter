#pragma once

#include "Mapa.h"

struct Node {

	CMapa *elem;
	Node* prev;
	Node* next;

	Node(CMapa * elem = nullptr, Node* next = nullptr, Node* prev = nullptr)
		: elem(elem), prev(prev), next(next) {}
};

class DLList {

	unsigned int n;

public:

	Node *last;
	Node *first;
	Node *aux;

	DLList() : first(nullptr), last(nullptr), n(0) {}
	~DLList() {
		while (last != nullptr) {
			Node* aux = last;
			last = last->prev;
			delete aux;
		}
	}
	void add(CMapa * elem, unsigned int p)
	{
		if (p > n) return;
		if (n == 0) //vacio
		{
			first = new Node(elem);
			last = first;
		}
		else if (p == 0)//inicio
		{
			first->prev = new Node(elem, first);
			if (first->prev != nullptr) {
				first = first->prev;
			}
		}
		else if (p == n)  //final
		{
			last->next = new Node(elem, nullptr, last);
			if (last->next != nullptr) {
				last = last->next;
			}
		}
		else {
			Node* aux = first;
			for (int i = 0; i < n; i++) {
				aux = aux->next;
			}
			Node* newest = new Node(elem, aux, aux->prev);
			if (newest != nullptr) {
				aux->prev = newest;
				newest->prev->next = newest;
			}
		}
		aux = first;
		n++;
	}
	void push_back(CMapa * elem) {
		add(elem, n);
	}

	CMapa* Elemento(int p)
	{
		Node* aux = first;
		for (int i = 0; i < p; i++) {
			aux = aux->next;
		}
		return aux->elem;

	}

	Node *nodo_actual(int p)
	{
		Node* aux = first;
		for (int i = 0; i < p; i++) {
			aux = aux->next;
		}
		return aux;
	}
};