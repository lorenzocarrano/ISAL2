#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *fp;
	void *ptr
	fp = fopen(fp_samples.hex);
	if(NULL == fp){
		return -1;
	}
	
	while(EOF != fscanf(fp, "%x", ptr)){
		printf("%p", &ptr);
	
	}

	return 0;
}
