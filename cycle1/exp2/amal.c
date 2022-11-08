#include <stdio.h>
#include <string.h>

typedef struct trans {
	char state1[3];
	char input[3];
	char state2[3];
} trans;

char states[10][3], result[10][3], temp[3];

int add_state(char state[3], int k) {
	int flag = 0;
	
	for(int i = 0; i < k; i++) {
		if(!strcmp(result[i], state)) flag = 1;
	}
	
	if(!flag) {
		strcpy(result[k], state);
		k++;
	}
	
	return k;
}

void display(int n){
	printf("Epsilon closure of %s = {", temp);
	
	for(int i = 0; i < n; i++)
		printf(" %s", result[i]);
	
	printf(" }\n");
}

void main() {
	int k, n, m;
	char state[3];
	
	printf("Enter the no of states: ");
	scanf("%d", &n);
	
	printf("Enter the states:\n");
	for(int i = 0; i < n; i++){
		scanf("%s", states[i]);
	}
	
	printf("\nEnter the number of transitions: ");
	scanf("%d", &m);
	
	trans table[m];
	
	printf("Enter the transition table:\n");
	for(int i = 0; i < m; i++) {
		scanf("%s %s %s", table[i].state1, table[i].input, table[i].state2);
	}
	
	printf("\n");
	for(int i = 0; i < n; i++){
		k = 0;
		
		strcpy(temp, states[i]);
		k = add_state(states[i], k);
		
		for(int p = 0; p < k; p++) {			
			strcpy(state, result[p]);

			for(int j = 0; j < m; j++){
				if(!strcmp(state, table[j].state1)){
					if(!strcmp(table[j].input, "e")) {
						k = add_state(table[j].state2, k);
					}
				}
			}
		}
		
		display(k);
	}
}
