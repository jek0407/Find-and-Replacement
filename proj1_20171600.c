#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> // �ٸ� ��� ������ ������� ����

char data[4000]; // �Է� �޴� ������ ������ data�� ����
int len; // �Է� ���� ������ ���� ���� ����ϴµ� ���
int word_list[4000]; // ���������� ǥ���ؾ��ϴ� ������ index�� ����
int list_len; // ���� �迭�� ��ȿ���� ����
char word[20]; // operation�� �����Ҷ� �Էµ� �ܾ ����
int word_len; // ���� �Էµ� �ܾ��� ����
int idx; // �ʿ��� �ε���( eg) replace index)�� ����

int word_index[2000]; // operation ����� �Էµ� �ܾ� ù ������ index�� ����

void print_text(); // ���Ŀ� �°� ���. (������ ��� ��� ����)
int check_in_list(int i, int j); // ���������� ��� ���θ� �����Ҷ� �ʿ�
int find_word(); // Ư�� �ܾ ã�� word_list�� ���� ���ش�, Ư�� �ܾ��� ������ return
void insert_word(int key); // Ư�� �ܾ Ư�� index�� ����
void delete_word(int i, int key); // Ư��index��  �ܾ ����

void select_delete(); // delete_word �Լ����� recursion�� ���� �� �� ���
void save_quit();

int main(void) {
	// TODO: init variables
	char operation;
	int i = 0, res;
	char file_name[100];
	FILE* ifile = NULL;

	// TODO: fileopen, print text, character information...
	printf("### Enter the text file name: ");
	scanf("%s", file_name);

	ifile = fopen(file_name, "r");
	if (ifile == NULL) {
		printf("Input File Open Error!\n");
		return 1;
	}
	while (!feof(ifile)) {
		data[++i] = fgetc(ifile);
	}
	len = i - 1;
	print_text();
	printf("[%d characters]\n", len);

	while (1) {
		printf("\n### [1]Find [2]Insert [3]Delete [4]Replace [0]Save&Quit\n");
		printf("### Enter the operation: ");
		scanf(" %c", &operation);
		getchar();

		switch (operation) {
		case '1': // Find
			find_word();
			break;
		case '2': // Insert
			insert_word(1);
			break;
		case '3': // Delete
			printf("### Enter the text to delete: ");
			for (i = 0;; i++) {
				scanf("%c", &word[i]);
				if (word[i] == '\n') break;
			}
			delete_word(i, 1);
			break;
		case '4': // Replace
			printf("### Enter the text to replace: ");
			for (i = 0;; i++) {
				scanf("%c", &word[i]);
				if (word[i] == '\n') break;
			}
			delete_word(i, 2);
			insert_word(2);
			break;
		case '0': // Save&Quit
			save_quit();
			fclose(ifile);
			return 1;
		default: break;
		}
	}
	fclose(ifile);
	res = fclose(ifile);
	if (res != 0) {
		printf("File not closed\n");
		return 1;
	}
	return 0;
}

void print_text() {
	// TODO: init variables
	int i = 0, j = 0;

	printf("\n");
	printf("==============================================================\n");
	// TODO: print the text according to the format
	for (i = 0; i <= len; i++) {
		if (!check_in_list(i, j)) {
			printf("\033[31m%c\033[0m", data[i]);
			j++;
		}
		else
			printf("%c", data[i]);
	}
	printf("\n==============================================================\n");

}

int check_in_list(int i, int j) {
	// TODO: check whether the index exists in the list
	if (word_list[j] == i) {
		return 0;
	}
	else return 1;
}

int find_word() {
	// TODO: find the word in the text
	int check = 0, i = 0, j = 0, k = 0, flag = 0;
	list_len = 0;
	for (i = 0; i < 4000; i++)
		word_list[i] = 4001;
	for (i = 0; i < 20; i++)
		word[i] = '\0';
	printf("### Enter the text to find: ");
	for (i = 0;; i++) {
		scanf("%c", &word[i]);
		if (word[i] == ' ') continue;
		if (word[i] == '\n') break;
	}
	word_len = i;
	for (i = 0; i <= len; i++) {
		if (data[i] == word[j]) {
			check = i;
			for (j = 0; j < word_len; j++) {
				if (data[i] != word[j]) {
					j = 0;
					i = check;
					break;
				}
				i++;
			}
			i = check;
			if (j == word_len) {
				list_len++;
				word_index[flag++] = i;
				for (j = 0; j < word_len; j++) {
					if (word_list[k - 1] < i)
						word_list[k++] = i;
					i++;
				}
			}
			i = check;
			j = 0;
		}
	}
	
	if (list_len == 0) {
		printf("There is no such a text.\n");
		return 0;
	}
	else
		print_text();
	// save the index list and return the length of the list
	return list_len;
}

void insert_word(int key) {
	// TODO: insert the word to the text at the index
	int i = 0, j = 0, insert_index, flag;
	for (i = 0; i < 4000; i++)
		word_list[i] = 4001;
	for (i = 0; i < 20; i++)
		word[i] = '\0';

	if (key == 1) {
		printf("### Enter the text to insert: ");
		for (i = 0;; i++) {
			scanf("%c", &word[i]);
			if (word[i] == '\n') break;
		}
	}
	else {
		printf("### Enter the text replace with: ");
		getchar();
		for (i = 0;; i++) {
			scanf("%c", &word[i]);
			if (word[i] == '\n') break;
		}
	}

	word_len = i;
	len += i;

	if (key == 1) {
		printf("### Enter the index to insert: ");
		scanf("%d", &insert_index);
		getchar();
	}
	else
		insert_index = idx;

	flag = insert_index;

	for (i = 0; i < word_len; i++)
		word_list[i] = ++flag;

	for (i = len; i > insert_index; i--) {
		data[i + word_len] = data[i];
	}
	for (i = insert_index + 1; i <= insert_index + word_len; i++)
		data[i] = word[j++];

	print_text();
}

void delete_word(int i, int key) {
	// TODO: delete the word in the text
	int check = 0, j = 0, k = 0, flag = 0;

	list_len = 0;
	word_len = i;

	for (i = 0; i < 4000; i++)
		word_list[i] = 4001;

	for (i = 0; i <= len; i++) {
		if (data[i] == word[j]) {
			check = i;
			for (j = 0; j < word_len; j++) {
				if (data[i] != word[j]) {
					j = 0;
					i = check;
					break;
				}
				i++;
			}
			i = check;
			if (j == word_len) {
				list_len++;
				word_index[flag++] = i;
				for (j = 0; j < word_len; j++) {
					if(word_list[k-1] < i)
						word_list[k++] = i;
					i++;
				}
			}
			i = check;
			j = 0;
		}
	}
	print_text();
	
	if (list_len <= 0) {
		printf("There is no such a text.\n");
		return;
	}
	else {
		j = 0;
		for (i = 0; i < list_len; i++) {
			printf("### %d) %d\n", i + 1, word_index[j++] - 1);
		}

		select_delete(key);

		len -= word_len;

		for (i = 0; i < 4000; i++)
			word_list[i] = 4001;
	}
	if (key == 1)
		print_text();
}

void select_delete(int key) {
	int i, j, count = 0, delete_index;

	if (key == 1)
		printf("### Select the index you want to delete: ");
	else
		printf("### Select the index you want to replace: ");

	scanf("%d", &delete_index);

	if (key == 2)
		idx = delete_index;

	j = 0;
	for (i = 0; i < list_len; i++) {
		if (delete_index != word_index[i] - 1) {
			count++;
		}
	}

	if (count == list_len) {
		printf("### Please enter the index in the list.\n");
		select_delete(key);
	}
	else if (count < list_len) {
		for (i = delete_index + 1; i <= len + 1; i++) {
			data[i] = data[i + word_len];
		}
	}
	else
		printf("Wrong index!\n");
}

void save_quit() {
	int i, res;
	char file_name[100];
	FILE* ofile = NULL;

	for (i = 0; i < 4000; i++)
		word_list[i] = 4001;

	print_text();
	printf("[%d characters]\n", len);
	printf("### Save as: ");
	scanf("%s", file_name);

	ofile = fopen(file_name, "w");
	if (ofile == NULL) {
		printf("Output File Open Error!\n");
	}
	for (i = 1; i <= len; i++)
		fputc(data[i], ofile);

	res = fclose(ofile);
	if (res != 0) {
		printf("File not closed\n");
	}
}