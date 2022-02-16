#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> // 다른 헤더 파일을 사용하지 않음

char data[4000]; // 입력 받는 파일의 내용을 data에 저장
int len; // 입력 받은 파일의 글자 수를 출력하는데 사용
int word_list[4000]; // 빨간색으로 표시해야하는 글자의 index를 저장
int list_len; // 위의 배열의 유효값의 길이
char word[20]; // operation을 수행할때 입력된 단어를 저장
int word_len; // 위의 입력된 단어의 길이
int idx; // 필요한 인덱스( eg) replace index)를 저장

int word_index[2000]; // operation 수행시 입력된 단어 첫 글자의 index를 저장

void print_text(); // 형식에 맞게 출력. (빨간색 출력 경우 포함)
int check_in_list(int i, int j); // 빨간색으로 출력 여부를 결정할때 필요
int find_word(); // 특정 단어를 찾아 word_list에 저장 해준다, 특정 단어의 개수를 return
void insert_word(int key); // 특정 단어를 특정 index에 삽입
void delete_word(int i, int key); // 특정index의  단어를 삭제

void select_delete(); // delete_word 함수에서 recursion을 구현 할 때 사용
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