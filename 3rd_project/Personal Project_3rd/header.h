#ifndef Personal_Project_header_h
#define Personal_Project_header_h

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
#endif
