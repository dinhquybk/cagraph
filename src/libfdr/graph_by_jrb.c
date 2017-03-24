#include <stdio.h>
#include "jrb.h"

int main(int argc, char const *argv[])
{
	JRB tree, ptr, subptr, subtree,s[13];
	tree=make_jrb();

	for(int i=0;i<13;i++){		
		s[i]=make_jrb();
		jrb_insert_int(tree,i+1,new_jval_v(s[i]));
	}
	
	jrb_insert_int(s[0], 1, JNULL);	
	jrb_insert_int(s[0], 2, JNULL);
	jrb_insert_int(s[0], 5, JNULL);
	jrb_insert_int(s[0], 6, JNULL);
	
	jrb_insert_int(s[1], 0, JNULL);	
	jrb_insert_int(s[2], 0, JNULL);

	jrb_insert_int(s[3], 4, JNULL);
	jrb_insert_int(s[3], 5, JNULL);

	jrb_insert_int(s[4], 3, JNULL);
	jrb_insert_int(s[4], 5, JNULL);
	jrb_insert_int(s[4], 6, JNULL);	

	jrb_insert_int(s[5], 0, JNULL);
	jrb_insert_int(s[5], 3, JNULL);
	jrb_insert_int(s[5], 4, JNULL);
	
	jrb_insert_int(s[6], 0, JNULL);
	jrb_insert_int(s[6], 4, JNULL);

	jrb_insert_int(s[7], 8, JNULL);

	jrb_insert_int(s[8], 7, JNULL);

	jrb_insert_int(s[9], 10, JNULL);
	jrb_insert_int(s[9], 11, JNULL);
	jrb_insert_int(s[9], 12, JNULL);

	jrb_insert_int(s[10], 9, JNULL);

	jrb_insert_int(s[11], 9, JNULL);
	jrb_insert_int(s[11], 12, JNULL);

	jrb_insert_int(s[12], 9, JNULL);
	jrb_insert_int(s[12], 1, JNULL);
	
	jrb_traverse(ptr , tree ){
		printf("%2d:  ", jval_i(ptr->key) );
			subtree=(JRB)jval_v(ptr->val);
			jrb_traverse( subptr , subtree ){
				printf("%2d ", jval_i(subptr->key) );				
			}			
			printf("\n");
	}

	//FREE:
	jrb_traverse(ptr , tree ){		
		jrb_free_tree((JRB)jval_v(ptr->val));		
	}
	jrb_free_tree(tree);
	return 0;
}