#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
FILE *f;
void show_dll_node(Dllist node){	
	fprintf(f,"%d ",jval_i(node->val) );
}
void show_dll_node2(Dllist node){	
	printf("%d ",jval_i(node->val) );
}
int main(int argc, char const *argv[])
{
	FILE *f1,*f2;
	//TEST LOAD:
	JRB g,subtree,ptr,subptr;	
	char in[][16]={"in1.txt","in2.txt","in3.txt","in4.txt"};
	char out[][16]={"out1","out2","out3","out4"};
	char result[][16]={"result1","result2","result3","result4"};
	filecompare tmp;
	for(int i=0;i<4;i++){
		f=fopen(result[i],"w");
		g=Load(in[i]);
		//test load:(gra_insert_int)
		fprintf(f, "test load\n");	
		jrb_traverse(ptr,g){
			fprintf(f,"%d: ",jval_i(ptr->key));
			subtree=(JRB)jval_v(ptr->val);
			jrb_traverse(subptr,subtree){
				fprintf(f,"%d(%0.0f) ",jval_i(subptr->key),jval_d(subptr->val));
			}
			fprintf(f,"\n");
		}
		Dllist ds_dinh,ds_sort,ds_reverse,dptr;
		//test danh sach dinh:(gra_getvertices,dll_size,gra_to_dll,gra_free)
		fprintf(f, "test gra_getvertices\n");
		ds_dinh=GetVertices(g);
		fprintf(f, "%d: ",dll_size(ds_dinh) );
		dll_display(ds_dinh,show_dll_node);
		fprintf(f,"\n");
		//test ham dao nguoc danh sach:(dll_reverse,dll_free)
		fprintf(f, "test dll_reverse\n");
		ds_reverse=dll_reverse(ds_dinh,jval_copy_i);
		dll_display(ds_reverse,show_dll_node);		
		fprintf(f, "\n" );
		//test ham sap xep danh sach:(dll_sort,dll_free)
		fprintf(f, "test dll_sort\n");		
		ds_sort=dll_sort(ds_reverse,jval_copy_i,jval_cmp_i);
						
		dll_display(ds_sort,show_dll_node);		
		fprintf(f,"\n");
		//test ham tim phan tu thu i trong danh sach:(dll_getelement)
		fprintf(f, "test dll_getelement\n" );
		dptr=dll_getelement(ds_sort,i);
		dptr->val=new_jval_i(1000);
		dll_display(ds_reverse,show_dll_node);		
		fprintf(f,"\n");
		dll_display(ds_sort,show_dll_node);		
		fprintf(f,"\n");

		dll_free(ds_reverse);		
		dll_free(ds_sort);
		dll_free(ds_dinh);
		fclose(f);

		printf("Test case : %d\n",i+1 );
		tmp=filecmp(result[i],out[i]);
		switch(tmp.same){
			case -1:
				printf("Cannot open file\n");
				break;
			case 0:
				printf("Load OK \n");
				break;
			default:
				printf("Load FAILED at line %d, column: %d\n",tmp.line,tmp.col );
				break;
		}
		FreeGraph(g);		
	}	

	return 0;
}