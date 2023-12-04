#include <stdio.h>
#include <stdlib.h>

#define GRID_X 250
#define GRID_Y 50

char grid[GRID_Y][GRID_X];

void initializeGrid(){
	for (int i = 0; i < GRID_Y; i++) {
		for (int j = 0; j < GRID_X; j++) {
			if (j == GRID_X - 1){
				grid[i][j] = '\n';
			}
			else {
				grid[i][j] = ' ';
			}
		}
	}
}

void printGrid(){
	for (int i = 0; i < GRID_Y; i++) {
		for (int j = 0; j < GRID_X; j++) {
			printf("%c", grid[i][j]);
		}
	}
}

struct NODE {
	char value;
	struct NODE *left;
	struct NODE *right;
} *root, *temp; 

// Uses BFS like technique
struct NODE * findNodeWithEmptyLeftOrRight(struct NODE * queue[], int size, int front, int rear) {
	if (front == -1) return NULL; // Empty
	if ((front == rear + 1) || (front == 0 && rear == size - 1)) return NULL; // FULL (TODO make it return something else)
	
	if (queue[front]->left == NULL || queue[front]->right == NULL) {
		return queue[front];
	}

	// EnQueue left and right nodes
	if (queue[front]->left != NULL) {
		rear = (rear + 1) % size;
		queue[rear] = queue[front]->left;
	}
	if (queue[front]->right != NULL) {
		rear = (rear + 1) % size;
		queue[rear] = queue[front]->right;
	}

	// DeQueue
	if (front == rear) {
		front = -1;
		rear = -1;
	}
	else {
		front = (front + 1) % size;
	}

	return findNodeWithEmptyLeftOrRight(queue, size, front, rear);
}

void insertIntoTree(char value) {
	temp = (struct NODE *)malloc(sizeof(struct NODE));
	temp->value = value;
	temp->left = NULL;
	temp->right = NULL;

	if (root == NULL) {
		root = temp;
		return;
	}

	int queueSize = 20;
	struct NODE * queue[queueSize];
	int front = 0, rear = 0;
	queue[rear] = root;
	struct NODE * control = findNodeWithEmptyLeftOrRight(queue, queueSize, front, rear);
	if (control->left == NULL) {
		control->left = temp;
	}
	else if (control->right == NULL) {
		control->right = temp;
	}
}

// Only works for maximum 5 height
void setTreeIntoGrid(int y, int x, int level, struct NODE * control) {
	if (control == NULL) return;
	grid[y][x] = control->value;
	int offset = level * level;
	if (control->left != NULL) {
		grid[y+1][x-offset] = '.'; // ·
		setTreeIntoGrid(y+2, x - 2 * offset, level - 1, control->left);
	}
	if (control->right != NULL) {
		grid[y+1][x+offset] = '.';
		setTreeIntoGrid(y+2, x + 2 * offset, level - 1, control->right);
	}
}

int getTreeHeight(struct NODE * control, int h) {
	int leftHeight = h, rightHeight = h;
	if (control->left != NULL)
		leftHeight = getTreeHeight(control->left, h + 1);
	if (control->right != NULL)
		rightHeight = getTreeHeight(control->right, h + 1);
	if (leftHeight > rightHeight) return leftHeight;
	return rightHeight;
}

int main (int argc, char *argv[]) {
	for (char i = 'a'; i <= 'z'; i++) {
		insertIntoTree(i);
	}
	for (char i = 'A'; i <= 'E'; i++) {
		insertIntoTree(i);
	}
	// TODO Limi the tree to 5 height i.e., 31 nodes
	
	initializeGrid();
	printf("\x1b[2J"); // Clear entire screen
	// while (1) {
		setTreeIntoGrid(20, GRID_X / 2, getTreeHeight(root, 1) - 1, root);
		printGrid();
		// printf("\x1b[H"); // Move cursor to default (0,0)
	// }
	return 0;
}
