#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFF 1000

void change_last_char(char *word, char find, char to) {
   if (word[strlen(word) - 1] == find) word[strlen(word) - 1] = to;
      return;
}

char last_char(char *word) {
   return word[strlen(word) - 1];
}

int word_check(char *word, char *input) {
   // 두 문자열이 같은 경우에는 더할나위 없이 return 1
   if (strcmp(word, input) == 0)
      return 1;
   int i;
   char *temp;
   temp = (char *)malloc(sizeof(char)*30);
   // 입력받은 문자 전체를 temp에 복사하고 이것을 통해 검색한다
   strcpy(temp, word);
   for (i = 0; i < strlen(input); i++) {
      if (input[i] == '*') {
         // i번째 char이 *이면 0개~n개 문자가 있던 상관없으므로 다음 문자열을 찾기 위해 continue
         continue;
      } else {
         // strchr을 이용해 temp에 i번째 input된 char의 위치를 검색한다
         char *t = strchr(temp, input[i]);
         if (t == NULL) {
            // char을 string내에서 못 찾았으므로 없음 return 0
            return 0;
         } else {
            // 찾았지만 input의 첫문자가 *이 아니면서 t + 1을 하면 *input과 같이 처리되므로 if문을 해준다
            if (i == 0 && input[0] != word[0]) {
               return 0;
            }
            // 찾았으므로 찾은 문자 다음에서부터 temp에 넣어줌
            temp = t + 1;
            // 찾은 문자 다음것과 input[i+1]이 같지 않을경우 return 0
            // ex) soloier *li*일때 o가 있음에도 문자열 처리가 되는 문제
            if (temp[0] != input[i + 1] && input[i + 1] != '*'){
               return 0;
            }
         }
      }
   }
   // for문이 다 돌고나서 temp의 길이가 0이면 다 찾아진 것이므로 return 1
   if (strlen(temp) == 0){
      return 1;
   } else {
      // temp의 길이가 1이 아니지만, (앞에서 *이 아닌 문자에 대한 searching을 끝낸 후 이므로) 입력받은 값이 *이면 나머지에 관게없이 return 1
      if (last_char(input) == '*'){
        return 1;
      }
   }
   return 0;
}

int main(int argc, char *argv[]) {
   if(argc == 1){
      printf("Regular Expression을 입력해주세요.\n");
      return 0;
   }
   // input변수를 만들고 거기에 입력받은 Regular Expression을 복사해 넣는다
   char input[30];
   strcpy(input, argv[1]);
   FILE *fp;
   char line[BUFF];
   int line_num = 0;
   fp = fopen("sample.txt", "r+");
   // Line 단위 기준 불러오기
   while (fgets(line, BUFF, fp)) {
      line_num++;
      // 맨 뒤의 개행문자를 없애고 그 자리에 NULL문자를 넣어줌
      change_last_char(line, '\n', '\0');
      // Word 단위 기준 작업하기
      char *word = NULL;
      int word_count = 0;
      word = strtok(line, " ");
      while (word != NULL) {
         // word의 맨 뒷 문자가 .이거나 !일 때 NULL로 바꿔줘서 문자열 길이를 1개 줄여준다(그 문자를 없앤다)
         if (word_check(word, input) == 1) {
            word_count++;
         }
         word = strtok(NULL, " ");
      }
      printf("%d ", word_count);
   }
   // commit test
}
