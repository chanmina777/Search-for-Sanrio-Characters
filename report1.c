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
    struct __sanrio *prev;
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
    int num;
    int a = 0;

    printf("プロフィールを知りたいキャラの名前を入力してね♥:");
    scanf("%s",who);

    Sanrio *tmp = head;
    
    while(tmp != NULL){
        if(strcmp(tmp->name, who) == 0){
            printf("name[%s] year[%d] day[%d] like[%s] seikaku1[%s] seikaku2[%s]\n",
                who, tmp->year, tmp->day, tmp->like, tmp->seikaku1, tmp->seikaku2);
                a = 1;
            if(tmp != NULL){
                printf("%sに対応する構造体のアドレスはこんな感じだよ!。\n", who);
                printf("  name: %p\n", &(tmp->name));
                printf("  year: %p\n", &(tmp->year));
                printf("  day: %p\n", &(tmp->day));
                printf("  like: %p\n", &(tmp->like));
                printf("  seikaku1: %p\n", &(tmp->seikaku1));
                printf("  seikaku2: %p\n", &(tmp->seikaku2));
            }
            break;
        }
        tmp = tmp->next;
    }

    if(a!=1){
        printf("その名前のキャラはいないよ泣😢\n");
    }
}

void search_year(Sanrio *head){
    int nen;
    int a = 0;
    printf("その年にキャラが誕生したか知りたい年を入力してね♥:");
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
        printf("その年にデビューしたサンリオキャラはいないよ泣😢\n");
    }
    
}

void delete(Sanrio *head, Sanrio *del){
    int yes;
    int itu;
    char delname[100];
    Sanrio *y;

    printf("削除するキャラの名前を教えてね♥\n");

        printf("誰のデータを削除する?:");
        getchar();
        fgets(delname, 100, stdin);

        for(int i = 0; i < 100; i++){
            if (delname[i] == '\n') {
                delname[i] = '\0';
                break;
            }
        }

        del = head;

        while(del != NULL){
            if(strcmp(del->name, delname) == 0){
                break;
            }
            del = del->next;
            if (del == NULL){
                printf("その名前のキャラはいないよ泣😢\n");
                return;
            }
        }

        printf("%sのデータを削除するね‼。\n", delname);
        if (head == del){
            head = head->next;
        } else {
            y = head; //yは飛ばす前のひとつ前
            while (1){
                if (y->next == del){ //yの次が削除したいやつ
                    y->next = del->next; // y->next = y->next->next
                    break;
                }
                y = y->next;
            }   
        }

        printf("削除後の一覧を見たいかな? 1:yes or 2:no\n");
        scanf("%d", &yes);
        if(yes == 1){

            Sanrio *tmp;
            tmp = head;

            while(tmp != NULL){
                printf("name[%s] year[%d] day[%d] like[%s] seikaku1[%s] seikaku2[%s]\n",
                tmp->name, tmp->year, tmp->day, tmp->like, tmp->seikaku1, tmp->seikaku2);
                tmp = tmp->next;
            }
        } else {
            printf("終了するね‼\n");
        }
    
}

int main(void){
    FILE *fp;
    char fname[] = "data2.csv";
    char line[256]; //行の最大長に応じてサイズを調整する
    int number, check = 1; //操作
    Sanrio *head = NULL;
    Sanrio *tail = NULL;
    Sanrio *data;
    Sanrio *del;

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

    while(1){
        printf("何したい？\n 1:一覧表示, 2:検索(名前指定) 3:検索(デビュー年) 4:削除 5:終了\n 実行番号:");
        char tmp[100] = {"\0"};
        scanf("%s", tmp); //文字として受け取っとる
        while (strlen(tmp) != 1){
            printf("1,2,3,4,5のいずれかを入力してほしいな💦。\n");
            printf("何したい？\n 1:一覧表示, 2:検索(名前指定) 3:検索(デビュー年) 4:削除 5:終了\n 実行番号:");
            scanf("%s", tmp);
        }
        number = (int)(tmp[0] - '0');
        if(number == 1){
            printf("一覧を表示するね‼\n");
            print(head);
        } else if (number == 2){
            search_name(head);
        } else if(number == 3){
            search_year(head);
        } else if (number == 4){
            delete(head, del);
        } else if (number == 5){
            printf("処理を終了するね‼\n");
            break;
        } else {
            printf("1,2,3,4,5のいずれかを入力してほしいな💦。\n");
        }
    }
    

    
    fclose(fp);

    return 0;
}