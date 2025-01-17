#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include "structure.h"
#include "b_tree.h"
#include "disk_operation.h"

Row* b_tree_search(Page *page, int wanted_element) {
	uint32_t i = 0;
	while (i <= page->elems && wanted_element > page->info[i]->id) {
		i++;	
	}
	if( i <= page->elems && wanted_element == page->info[i]->id ) {
		return page->info[i];
	}
	else if(page->folha) {
		return NULL;
	}

	Page* page_child = disk_read(page, i);
	free(page);

	return b_tree_search(page_child, wanted_element);
}

Page* load_root() {
	return disk_read(NULL, 0);
}

Page* b_tree_create() {
	Page *x = malloc(sizeof(Page));
	x->folha = 1;
	x->elems = 0;
	disk_write(x);
	return x;
}

void static b_tree_split_child(Page *parent_not_full, uint32_t index_child_full) {
	int t = (MAX_ELEMENTS / 2) + 1;
	Page *page_new = malloc(sizeof(Page));
	Page *child_full = parent_not_full->childs[index_child_full];

	page_new->folha = child_full->folha;
	page_new->elems = t - 1;

	for(int j = 1; j <= t - 1; j++) {
		page_new->info[j] = child_full->info[j + t];
	}

	if(!child_full->folha) {
		for(int j = 1; j <= t; j ++) {
			page_new->childs[j] = child_full->childs[j+t];
		}
	}

	child_full->elems = t - 1;
	for(int j = parent_not_full->elems + 1; j < index_child_full + 1; j++) {
		parent_not_full->childs[j+1] = parent_not_full->childs[j];
	}

	parent_not_full->childs[index_child_full+1] = page_new;

	for(int j = parent_not_full->elems; j < index_child_full + 1; j++) {
		parent_not_full->childs[j+1] = parent_not_full->childs[j];
	}

	parent_not_full->info[index_child_full] = child_full->info[parent_not_full->elems];
	parent_not_full->elems ++;

	disk_write(child_full);
	disk_write(page_new);
	disk_write(parent_not_full);
}

void static b_tree_insert_nonfull(Page *page, Row* k) {
	int i = page->elems - 1;

	if(page->folha) {
		while(i >= 0 && k->id < page->info[i]->id) {
			page->info[i+1] = page->info[i];
			i --;
		}
		page->info[i+1] = k;
		page->elems ++;
		disk_write(page);
		free(page); 
	}
	else {
		while(i >= 0 && k->id < page->info[i]->id) {
			i --;
		}
		i ++;

		Page *child = malloc(sizeof(Page));
		child = disk_read(page, i);  

		if(child->elems == MAX_ELEMENTS) {
			b_tree_split_child(page, i);
			if(k->id > page->info[i]->id) {
				i ++;
			}
		}
		b_tree_insert_nonfull(child, k);
	}
}

void b_tree_insert(Page *root, Row *k) {
	if(root->elems == MAX_ELEMENTS) {
		Page *s = malloc(sizeof(Page))	;
		root = s;
		s->folha = 0;
		s->elems = 0;
		s->childs[0] = root;
		b_tree_split_child(s, 1);
		b_tree_insert_nonfull(s, k);
	}
	else {
		b_tree_insert_nonfull(root, k);
	}
}
