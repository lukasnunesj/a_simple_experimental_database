#include<stdio.h>
#include<stdint.h>

uint32_t b_tree_search(Page *page, uint32_t wanted_element){
	uint8_t i = 1;
	while (i <= page->elems, && wanted_element > page->info[i]) {
		i++;	
	}
	if( i <= page->elems && wanted_element = page->info[i] ) {
		return page->info[i];
	}
	else if(page->folha) {
		return NULL;
	}

	return b_tree_search(page->filhos[i])
}

Page* b_tree_create() {
	Page *x = malloc(sizeof(Page));
	x->folha = 1;
	x->n = 0;
	return x;
}

void b_tree_split_child(Page *page, uint32_t i) {
		
}

int main () {

}
