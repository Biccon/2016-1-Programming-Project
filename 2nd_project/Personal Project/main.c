#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 27
#define BUFF 1000

typedef struct Node Node;
typedef struct LinkedList LinkedList;
typedef struct Offset Offset;
typedef enum boolean boolean;

struct Node {
    Node *prev;
    Node *next;
    char data[30];
};

struct LinkedList {
    Node *header;
    Node *trailer;
};

struct Offset {
    int row;
    int col;
};

enum boolean { false, true };

// 문자 관련 함수
int get_first_char(char *word);
int get_index(char *word);
char * string_to_lower(char *word);

// 노드 추가 함수
Node * add_after(Node *node, char *data);
Node * add_before(Node *node, char *data);
Node * add_first(LinkedList *list, char *data);
Node * add_last(LinkedList *list, char *data);

// 노드 얻는 함수
Node * get_first(LinkedList *list);
Node * get_last(LinkedList *list);
Node * get_node_by_data(LinkedList *list, char *data);
Node * get_node_by_index(LinkedList *list, int index);

// 노드 지우는 함수(LinkedList에서 링크 삭제)
void remove_node(Node *node);

// 리스트 관련 함수
void init_list(LinkedList *list);
void set_list(LinkedList *list);
void print_lists(LinkedList *list);
void print_list(LinkedList *list);
Node * insert(LinkedList *list, char *data);

// 사용자 입력 함수
Node * insert_node(LinkedList *lists, char *data);
Node * search_node(LinkedList *lists, char *data);
Offset * delete_node(LinkedList *lists, char *data);
Offset * get_offset(LinkedList *lists, Node *n);

char * string_to_lower(char *word){
    int i;
    for(i=0;i<strlen(word);i++){
        *(word + i) = tolower(*(word + i));
    }
    return word;
}

//
int get_first_char(char *word){
    return word[0];
}

int get_index(char *word){
    return get_first_char(word) - 97;
}

// size
int get_size(LinkedList *list){
    int size = 0;
    Node *temp = list -> header -> next;
    while(temp != list -> trailer){
        size ++;
        temp = temp -> next;
    }
    return size;
}

// add
Node * add_after(Node *node, char *data){
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode -> data, data);
    newNode -> prev = node;
    newNode -> next = node -> next;
    
    node -> next -> prev = newNode;
    node -> next = newNode;
    return newNode;
}

Node * add_before(Node *node, char *data){
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode -> data, data);
    newNode -> prev = node -> prev;
    newNode -> next = node;
    
    node -> prev -> next = newNode;
    node -> prev = newNode;
    return newNode;
}

Node * add_first(LinkedList *list, char *data){
    return add_after(list -> header, data);
}

Node * add_last(LinkedList *list, char *data){
    return add_before(list -> trailer, data);
}

// get
Node * get_node_by_index(LinkedList *list, int index){
    Node *temp = list -> header -> next;
    int i = 0;
    while(temp != list -> trailer){
        if(i == index)
            return temp;
        i++;
        temp = temp -> next;
    }
    return NULL;
}

Node * get_node_by_data(LinkedList *list, char *data){
    Node *temp = list -> header -> next;
    while(temp != list -> trailer){
        if(strcmp(temp -> data, data) == 0)
            return temp;
        temp = temp -> next;
    }
    return NULL;
}

Node * get_first(LinkedList *list){
    return get_node_by_index(list, 0);
}

Node * get_last(LinkedList *list){
    return get_node_by_index(list, get_size(list) - 1);
}

// remove
void remove_node(Node *node){
    node -> prev -> next = node -> next;
    node -> next -> prev = node -> prev;
    free(node);
}

// print
void print_list(LinkedList *list){
    Node *temp = list -> header -> next;
    while(temp != list -> trailer){
        printf("\t%s\n", temp -> data);
        temp = temp -> next;
    }
}

void print_lists(LinkedList *list){
    int i;
    for(i=0;i<SIZE;i++){
        if(i != SIZE -1){
            printf("<%c>\n", i + 97);
        } else {
            printf("<The others>\n");
        }
        print_list(list + i);
    }
}

// init and set list
void init_list(LinkedList *lists){
    int i;
    for(i=0;i<SIZE;i++){
        (lists + i) -> header = (Node *)malloc(sizeof(Node));
        (lists + i) -> trailer = (Node *)malloc(sizeof(Node));
        (lists + i) -> header -> prev = NULL;
        (lists + i) -> header -> next = (lists + i)-> trailer;
        (lists + i) -> trailer -> prev = (lists + i) -> header;
        (lists + i) -> trailer -> next = NULL;
    }
}

void set_list(LinkedList *lists){
    FILE *fp = fopen("sample.txt", "rw");
    if(fp == NULL){
        printf("File Loading Failed");
        exit(1);
    }
    char line[BUFF];
    char sep[] = " \n";
    while(fgets(line, BUFF, fp)){
        char *word;
        word = strtok(line, sep);
        while(word != NULL){
            word = string_to_lower(word);
            if(isalpha(get_first_char(word)) != 0){
                //Node * temp =
                insert_node(lists, word);
            }
            word = strtok(NULL, sep);
        }
    }
}

Node * insert(LinkedList *list, char *data){
    if(get_size(list) == 0)
        return add_first(list, data);
    Node *temp = list -> trailer -> prev;
    while(temp != list -> header){
        int s = strcmp(temp -> data, data);
        if(s < 0){
            return add_after(temp, data);
        }
        else if(s == 0){
            return temp;
        } else {
            if(temp -> prev == list -> header)
                return add_before(temp, data);
            
            s = strcmp(temp -> prev -> data, data);
            if(s < 0){
                return add_before(temp, data);
            }
            temp = temp -> prev;
        }
    }
    return NULL;
}

Node * insert_node(LinkedList *lists, char *data){
    int index = get_index(data);
    // 이미 노드가 있으면 추가 시키지 않는다
    Node *temp = search_node(lists, data);
    if(temp != NULL)
        return temp;
    
    Node * first_added_node = insert(lists + index, data);
    Node * last_node = NULL;
    Node * latest_added_node = NULL;
    if(get_size(lists + index) > 5){
        // 5개가 넘으면 마지막에 있는 노드를 지우고(last_node) lists + SIZE - 1에 옮긴다.
        // 이 때 last_node를 구해주어야 마지막 노드를 알 수 있다
        last_node = get_last(lists + index);
        insert(lists + SIZE - 1, last_node -> data);
        // last_node와는 별개로 우리가 추가한 노드를 알아야 하므로 latest_added_node에 해당 data를 갖는 노드를 반환한다
        
        // 마지막에 있는 노드가 6번째에 있다고 생각되면 remove하고 the others에 있는것을 찾아주기 위해서
        latest_added_node = get_node_by_data(lists + index, data);
        if(last_node == latest_added_node){
            latest_added_node = get_node_by_data(lists + SIZE - 1, data);
        }
        remove_node(last_node);
        
        /*
         last_node = lists + index에 있는 맨 뒷 노드. 6번째 노드가 마지막에 입력한 노드일 수 있다.
         latest_added_node = lists + index또는 the others에 있는 입력받은 data로 찾은 노드
         */
    } else {
        // 5개가 아니면 최종 등록된 노드는 처음에 등록했던 노드이다.
        latest_added_node = first_added_node;
    }
    return latest_added_node;
}

Node * search_node(LinkedList *lists, char *data){
    int index = get_index(data);
    Node *temp = get_node_by_data(lists + index, data);
    if(temp == NULL)
        temp = get_node_by_data(lists + SIZE - 1, data);
    return temp;
}

Offset *delete_node(LinkedList *lists, char *data){
    Offset *newOffset = (Offset*)malloc(sizeof(Offset));
    newOffset -> row = -1;
    newOffset -> col = -1;
    Node *temp = search_node(lists, data);
    if(temp != NULL){
        free(newOffset);
        newOffset = get_offset(lists, temp);
        remove_node(temp);
    }
    return newOffset;
}

Offset *get_offset(LinkedList *lists, Node *n){
    Offset *newOffset = (Offset*)malloc(sizeof(Offset));
    newOffset -> row = -1;
    newOffset -> col = -1;
    int i;
    for(i=0;i<SIZE;i++){
        int col = 0;
        Node *temp = (lists + i) -> header -> next;
        while(temp != (lists + i) -> trailer){
            if(temp == n){
                newOffset -> row = i;
                newOffset -> col = col;
                return newOffset;
            }
            col++;
            temp = temp -> next;
        }
    }
    return newOffset;
}

int get_menu(){
    int menu;
    printf("기능을 선택하세요.\n");
    printf("[1] Search [2] Insert\n");
    printf("[3] Delete [4] Quit\n");
    printf(": ");
    scanf("%d", &menu);
    return menu;
}

int main(void){
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList) * 27);
    init_list(list);
    set_list(list);
    print_lists(list);
    int menu;
    while((menu = get_menu()) != 4){
        char input[30];
        Offset *tempOffset;
        Node *tempNode;
        int count;
        if(menu == 1){
            printf("찾을 단어를 입력하세요 : ");
            scanf("%s", input);
            tempNode = search_node(list, input);
            tempOffset = get_offset(list, tempNode);
            printf("SEARCH: %d %d\n", tempOffset -> row, tempOffset -> col);
        } else if(menu == 2){
            printf("추가할 단어를 입력하세요 : ");
            scanf("%s", input);
            tempNode = insert_node(list,input);
            tempOffset = get_offset(list, tempNode);
            count = tempOffset -> row != -1?((tempOffset -> row != 26)?get_size(list+get_index(input)):get_size(list+SIZE-1)):-1;
            printf("INSERT: %d %d @ %d\n", tempOffset -> row, tempOffset -> col, count);
        } else if(menu == 3){
            printf("삭제할 단어를 입력하세요 : ");
            scanf("%s", input);
            tempOffset = delete_node(list, input);
            count = tempOffset -> row != -1?((tempOffset -> row != 26)?get_size(list+get_index(input)):get_size(list+SIZE-1)):-1;
            printf("DELETE: %d %d @ %d\n", tempOffset -> row, tempOffset -> col, count);
        } else if(menu == 5){
            print_lists(list);
        }
        menu = 0;
    }
}