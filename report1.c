#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __sanrio{
    char name[100]; //キャラクターの名前
    int year; //デビュー年
    int day; //誕生日
    char like[100]; //好きなもの
    char seikaku1[100]; //性格1
    char seikaku2[100]; //性格2
    struct __sanrio *next;
} Sanrio; 

void print(Sanrio *top){
    Sanrio *tmp;
    tmp = top;
    if(tmp == NULL){
        printf("null");
    }
    while(tmp != NULL){
        printf("name[%s] year[%d] day[%d] like[%s] seikaku1[%s] seikaku2[%s]\n",
            tmp->name, tmp->year, tmp->day, tmp->like, tmp->seikaku1, tmp->seikaku2);
        tmp = tmp->next;
    }
}

void search_name(Sanrio *head){
    char who[100];
    printf("プロフィールを知りたいキャラの名前を入力してください:");
    scanf("%s",who);

    Sanrio *tmp = head;
    
    while(tmp != NULL){
        if(strcmp(tmp->name, who) == 0){
            printf("name[%s] year[%d] day[%d] like[%s] seikaku1[%s] seikaku2[%s]\n",
                who, tmp->year, tmp->day, tmp->like, tmp->seikaku1, tmp->seikaku2);
            break;
        }
        tmp = tmp->next;
    }
    
}

void search_year(Sanrio *head){
    int nen;
    int a = 0;
    printf("その年にキャラが誕生したかしりたい年を入力してください:");
    scanf("%d", &nen);

    Sanrio *tmp = head;

    while(tmp != NULL){
        if(tmp->year == nen){
            printf("name[%s] year[%d] day[%d] like[%s] seikaku1[%s] seikaku2[%s]\n",
                tmp->name, tmp->year, tmp->day, tmp->like, tmp->seikaku1, tmp->seikaku2);
                a = 1;
        }
        tmp = tmp->next;
    }

    if(a!=1){
        printf("その年にデビューしたサンリオキャラはいないよ泣\n");
    }
    
}

int main(void){
    FILE *fp;
    char fname[] = "data2.csv";
    char line[256]; //行の最大長に応じてサイズを調整する
    int number, check = 0; //操作
    Sanrio *head = NULL;
    Sanrio *tail = NULL;
    Sanrio *data;

    fp = fopen(fname, "r");
    if(fp == NULL){
        printf("%s file not open!\n", fname);
		return -1;
    }

    while(fgets(line, sizeof(line), fp) != NULL){
        char *token = strtok(line, ","); //文字列lineを,で区切って分解　
        if(token != NULL){
            data = malloc(sizeof(Sanrio));
            strcpy(data->name, token);

            token = strtok(NULL, ",");
            sscanf(token, "%d", &(data->year));

            token = strtok(NULL, ",");
            sscanf(token, "%d" ,&(data->day));

            token = strtok(NULL, ",");
            strcpy(data->like, token);

            token = strtok(NULL, ",");
            strcpy(data->seikaku1, token);

            token = strtok(NULL, "\n");
            strcpy(data->seikaku2, token);
            data->seikaku2[strlen(data->seikaku2) -1] = '\0';

            data->next = head;
            head = data;
        }
        check = 1;
    }

    printf("どのような操作をしますか？\n 1:一覧表示, 2:検索(名前指定) 3:検索(デビュー年) 4:削除 5:登録\n 実行番号:");
    scanf("%d", &number);
    if(number == 1){
        printf("一覧を表示します\n");
        print(head);
    } else if (number == 2){
        search_name(head);
    } else if(number == 3){
        search_year(head);
    } else {
        printf("1,2,3,4,5のいずれかを入力してください。\n");
    }

    
    fclose(fp);

    return 0;
}