#include <stdio.h>

int main(){
	
	float a[2] = {0.5, 0.5};
	int data;
	FILE *file = fopen("heart_beat.txt", "r");
	for (int i=0; i<4; i++){
		fscanf (file, "%d", &data);
		printf("%d\n", data);
	}
}
