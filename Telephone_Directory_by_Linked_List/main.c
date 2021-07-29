//
//  main.c
//  Telephone_Directory_by_Linked_List
//
//  Created by 세광 on 2021/07/29.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_NAME 102
#define SIZE_PHONE 102

typedef struct node {
    char name[SIZE_NAME];
    char phone[SIZE_PHONE];
    struct node *link;
} NODE;

NODE *ptr_head = NULL;

int Show_Menu(void);
void Init(void);
void Init_Node(char *name, char *phone);
void Append_Node(void);
void Display_All(void);
void Insert_Node(void);
void Delete_Node(void);
void Search_Node(void);
void Reverse_Node(void);
int Get_Total(void);

int main(void) {
    Init();
    
    while (1) {
        switch (Show_Menu()) {
            case 1:
                Append_Node();
                break;
                
            case 2:
                Display_All();
                puts("\t** 엔터키를 누르세요 **");
                getchar();
                break;
                
            case 3:
                Insert_Node();
                break;
                
            case 4:
                Delete_Node();
                break;
                
            case 5:
                Search_Node();
                getchar();
                break;
                
            case 6:
                Reverse_Node();
                break;
                
            case 7:
                puts("프로그램을 종료하였습니다.");
                return 0;
                
            default:
                puts("메뉴 번호를 잘못 선택하셨습니다!");
                break;
        }
    }
    return 0;
}

int Show_Menu(void) {
    int num = 0;
    char str[12];
    system("clear");
    
    puts("========== [전화번호부 메뉴] ==========");
    puts("\t1. 추가하기 [Append data to the end]");
    puts("\t2. 출력하기 [Display all]");
    puts("\t3. 삽입하기 [Insert data]");
    puts("\t4. 삭제하기 [Delete data]");
    puts("\t5. 검색하기 [Search data]");
    puts("\t6. 역순으로 정렬하기 [Reverse list]");
    puts("\t7. 종료하기 [Quit]");
    puts("===================================");
    
    printf("[현재 총 %d개의 자료가 저장되어 있습니다.]\n", Get_Total());
    printf("# 메뉴 번호 선택 [   ]\b\b\b");
    fgets(str, sizeof(str) / sizeof(char), stdin);
    // new line을 0으로 교체
    str[strlen(str) - 1] = '\0';
    num = atoi(str);
    
    return num;
}

void Init(void) {
    // 3개의 초기 자료 입력
    Init_Node("A", "010-0000-0000");
    Init_Node("B", "010-1111-1111");
    Init_Node("C", "010-2222-2222");
}

void Init_Node(char *name, char *phone) {
    NODE *ptr_curr = ptr_head;
    
    // 마지막 노드에 추가될 구조체 자료 생성
    // 마지막 노드는 항상 링크 필드가 NULL
    NODE *ptr_new = (NODE *)malloc(sizeof(NODE));
    strcpy(ptr_new->name, name);
    strcpy(ptr_new->phone, phone);
    
    ptr_new->link = NULL;
    if (ptr_head == NULL) {
        ptr_head = ptr_new;
    } else {
        while (ptr_curr->link != NULL) {
            ptr_curr = ptr_curr->link;
        }
        ptr_curr->link = ptr_new;
    }
}

void Append_Node(void) {
    NODE *ptr_curr = ptr_head;
    
    // 마지막 노드에 추가될 구조체 자료 생성
    // 마지막 노드는 항상 링크 필드가 NULL
    NODE *ptr_new = (NODE *)malloc(sizeof(NODE));
    ptr_new->link = NULL;
    
    printf("이름을 입력하세요. : ");
    fgets(ptr_new->name, SIZE_NAME, stdin);
    // new line을 NULL로 교체
    ptr_new->name[strlen(ptr_new->name) - 1] = '\0';
    
    printf("휴대폰 번호를 입력하세요. : ");
    fgets(ptr_new->phone, SIZE_PHONE, stdin);
    // new line을 NULL로 교체
    ptr_new->phone[strlen(ptr_new->phone) - 1] = '\0';
    
    if (ptr_head == NULL) {
        ptr_head = ptr_new;
    } else {
        while (ptr_curr->link != NULL) {
            ptr_curr = ptr_curr->link;
        }
        ptr_curr->link = ptr_new;
    }
}

void Display_All(void) {
    NODE *ptr_curr = ptr_head;
    int i = 1;
    
    puts("\t    \t[전화번호부 목록]");
    puts("\t------------------------------");
    puts("\t [no]\t [이름]\t [휴대폰 번호]");
    puts("\t------------------------------");
    while (ptr_curr != NULL) {
        printf("\t %d\t %s\t %s \n", i++, ptr_curr->name, ptr_curr->phone);
        ptr_curr = ptr_curr->link;
    }
    puts("\t------------------------------");
    printf("\t[총 %d개]\n", Get_Total());
}

void Insert_Node(void) {
    int pos;
    NODE *ptr_curr = ptr_head;
    NODE *ptr_new = (NODE *)malloc(sizeof(NODE));
    Display_All();
    
    while (1) {
        printf("\n삽입할 번호는(입력 번호 이전에 삽입됨) : ");
        scanf("%d", &pos);
        getchar();
        
        if (pos > 0 && pos <= Get_Total()) {
            printf("이름을 입력하세요 : ");
            fgets(ptr_new->name, SIZE_NAME, stdin);
            // new line을 NULL로 교체
            ptr_new->name[strlen(ptr_new->name) - 1] = '\0';
            
            printf("휴대폰 번호를 입력하세요 : ");
            fgets(ptr_new->phone, SIZE_PHONE, stdin);
            // new line을 NULL로 교체
            ptr_new->phone[strlen(ptr_new->phone) - 1] = '\0';
            
            if (pos == 1) {
                ptr_new->link = ptr_curr;
                ptr_head = ptr_new;
            } else {
                for (int i = 1; i < pos - 1; i++) {
                    ptr_curr = ptr_curr->link;
                }
                ptr_new->link = ptr_curr->link;
                ptr_curr->link = ptr_new;
            }
            break;
        } else {
            puts("잘못 입력하셨습니다. 다시 입력해주세요!");
            continue;
        }
    }
}

void Delete_Node(void) {
    NODE *ptr_curr = ptr_head;
    int pos;
    
    if (ptr_head == NULL) {
        puts("** 노드가 비어 있습니다 **");
        getchar();
        return;
    }
    
    Display_All();
    while (1) {
        printf("삭제할 번호[no]는 : ");
        scanf("%d", &pos);
        if(pos > 0 && pos <= Get_Total()) {
            if (pos == 1) {
                ptr_head = ptr_curr->link;
                free(ptr_curr);
            } else {
                NODE *temp;
                for (int i = 1; i < pos - 1; i++) {
                    ptr_curr = ptr_curr->link;
                }
                temp = ptr_curr->link;
                ptr_curr->link = ptr_curr->link->link;
                free(temp);
            }
            break;
        } else {
            puts("잘못 입력하셨습니다. 다시 입력해주세요!");
            continue;
        }
    }
}

void Search_Node(void) {
    NODE *ptr_curr = ptr_head;
    char name[SIZE_NAME];
    int found = 0;
    
    if (ptr_head == NULL) {
        puts("** 노드가 비어 있습니다 **");
        getchar();
        return;
    }
    
    printf("검색할 이름을 입력하세요 : ");
    fgets(name, SIZE_NAME, stdin);
    // new line을 NULL로 교체
    name[strlen(name) - 1] = '\0';
    
    while (ptr_curr != NULL) {
        if(strcmp(name, ptr_curr->name) == 0) {
            found = 1;
            printf("\n%s님의 휴대폰 번호는 %s입니다.\n", ptr_curr->name, ptr_curr->phone);
            puts("\t** 엔터키를 누르세요 **");
        }
        ptr_curr = ptr_curr->link;
    }
    if(!found) {
        puts("** 존재하지 않습니다!! **");
        puts("\t** 엔터키를 누르세요 **");
    }
}

void Reverse_Node(void) {
    NODE *ptr_prev, *ptr_curr, *ptr_next;
    ptr_prev = NULL;
    ptr_next = NULL;
    ptr_curr = ptr_head;
    
    if (ptr_head == NULL) {
        puts("** 노드가 비어 있습니다 **");
        getchar();
        return;
    }
    
    while (ptr_curr != NULL) {
        ptr_next = ptr_curr->link;
        ptr_curr->link = ptr_prev;
        ptr_prev = ptr_curr;
        ptr_curr = ptr_next;
    }
    ptr_head = ptr_prev;
    
    Display_All();
    puts("\t** 엔터키를 누르세요 **");
    getchar();
}

int Get_Total(void) {
    NODE *ptr_curr = ptr_head;
    int total = 0;
    while (ptr_curr != NULL) {
        ptr_curr = ptr_curr->link;
        total++;
    }
    return total;
}
