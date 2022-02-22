
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct firstorder{
  char *string;
  struct firstorder *next;
}firstorder;

typedef struct list {
    struct list *head;
    char *string;
    int count;
    int txtcount;
    struct list *next;
    struct firstorder *firstorder;
}LIST;

typedef struct TXTPTR{
    LIST *ptr;
    struct TXTPTR *next;
}TXTPTR;

typedef struct LISTE{
  LIST *list;
  struct LISTE *next;
}LISTE;


LISTE *insertLISTE(LISTE **head, LISTE *add){

    LISTE *current = *head;

    while(current->next){
        current=current->next;
    }
    current->next=add;


    return *head;
}


void printhead(LIST *head){
	LIST *current = head;
	while(current!=NULL){
		printf("Head's string is : %s\n",current->head->string);
		current = current->next;
	}
	printf("\n\n\n\n\n");
}



void printList(LIST *head){
	LIST *current = head;
	while(current!=NULL){
		printf("%s;%d\n",current->string,current->count);
		current = current->next;
	}
	printf("\n\n\n\n\n");
}


LIST *deleteDuplicate(LIST *head){

    LIST* current = head;

    LIST* next_next;

    if (current == NULL)
       return current;

    while (current->next != NULL){
       if ( strcmp(current->string , current->next->string) == 0 ){
           current->count++;
           next_next = current->next->next;
           free(current->next);
           current->next = next_next;
       }
       else{
          current = current->next;
       }
    }
    return current;
}


LISTE *duplicate(LISTE *head){

    LISTE* current = head;

    LISTE* next_next;

    if (current == NULL){
       return head;
    }

    while (current->next != NULL)
    {
       if ( strcmp( current->list->string , current->next->list->string ) == 0 ){
          current->list->count+=current->next->list->count;
           current->list->txtcount++;
           next_next = current->next->next;
           free(current->next);
           current->next = next_next;
       }
       else{
          current = current->next;
       }
    }
    return head;
}



void tostring(char str[], int num){
    int i, rem, len = 0, n;

    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}


void swap (LIST *a,LIST *b){

    char *string = malloc(sizeof(char) * 20);
    strcpy(string,a->string);
    strcpy(a->string,b->string);
    strcpy(b->string,string);

}


void sortList(LIST *List){
    int swapped;
    LIST *ptr1;
    LIST *lptr = NULL;

    do
    {
        swapped = 0;
        //ptr1 = List->next;
		ptr1 = List;


        while (ptr1->next != lptr)
        {
            if (strcmp(ptr1->string,ptr1->next->string) > 0)
            {
                swap(ptr1,ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);

}


/*char *string = malloc(sizeof(char) * 20);
    strcpy(string,a->string);
    strcpy(a->string,b->string);
    strcpy(b->string,string);*/

void degistir(LISTE *a,LISTE *b)
{
    LIST *temp = (LIST *)malloc(sizeof(LIST));
    temp = a->list;
    a->list = b->list;
    b->list = temp;
}

void sort(LISTE *start)
{
    int swapped, i;
    LISTE *ptr1;
    LISTE *lptr = NULL;

    /* Checking for empty list */
    if (!start){
        return;
    }

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)
        {
            if ( strcmp( ptr1->list->string , ptr1->next->list->string ) > 0 )
            {
                degistir(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}


void sirala(LISTE *start)
{
    int swapped, i;
    LISTE *ptr1;
    LISTE *lptr = NULL;

    /* Checking for empty list */
    if (!start){
        return;
    }

    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)  {
            if ( ptr1->list->count < ptr1->next->list->count ) {
                degistir(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}




LIST *openf(char *fileName,char *isFile){

        FILE *fp;
        char line[128];
        LIST *current, *head;

        head = current = NULL;
        fp = fopen(fileName, "r");
        if ( fp == NULL ){
            (*isFile)='0';
            //printf("FP IS NULL");
            return NULL;
        }else{
          //printf("FP IS NOT NULL");
        }

        //printf("%s \n \n \n ",fileName);


        while( fscanf(fp, "%s", line) != EOF ){
            LIST *node = malloc(sizeof(LIST));
            node->string = strdup(line);
            node->count=1;
            node->firstorder=NULL;
            node->txtcount=1;
            node->next =NULL;

            if(head == NULL){
                current = head = node;
            } else {
                current = current->next = node;
            }
        }
        LIST *node = malloc(sizeof(LIST));
            node->string = strdup(line);
            node->count=1;
            node->firstorder=NULL;
            node->txtcount=1;
            node->next =NULL;


        sortList(head);
        //printf("HEAD IS : %s\n",head->string);

        /*head->next->head=head;
        head->next->next->head=head;
        printf("head->next->next->head->string : %s\n",head->next->next->head->string);*/

        LIST *curr=head;
        while(curr!=NULL){

          curr->head=head;
          curr = curr->next;
        }




        deleteDuplicate(head);

        //printf("head->next->next->next->next->next->head->string : %s and itself : %s\n",head->next->next->next->next->next->head->string,head->next->next->next->next->next->string);

        //printList(head);

        fclose(fp);
        return head;

}


TXTPTR *insertTXT(TXTPTR **head,TXTPTR *add){

    TXTPTR *current = *head;

    if(!current->ptr && !current->next){
        current = *head = add;
    }else{
        while(current->next){
            current = current->next;
        }
        current->next = add;
    }
    //printList(current);

    return *head;

}


char *TXTfileName(int i,char *c){

        char str[5]=".txt";
        tostring(c,i);
        strcat(c,str);
        return c;

}

TXTPTR *printAllTXT(TXTPTR *first){
    TXTPTR *current = first;
    while(current!=NULL){
        printList(current->ptr);
        current = current->next;
    }
    return first;
}


int main(void) {

    TXTPTR *first = (TXTPTR *)malloc(sizeof(TXTPTR *));
    first->next=NULL;first->ptr=NULL;

    TXTPTR *current = first;

    char isFile = '1';
    //../data/test.txt
    first->ptr = openf("./dataset/Econ/1.txt",&isFile);
    if(first->ptr == NULL){
      //printf("first->ptr null\n\n");
      return 1;
    }

    //printList(first->ptr);



    int totaltxtcount = 1;

  	char c[30];
    int i= 2;
	while(isFile!='0' && i<10){
        TXTPTR *second = (TXTPTR * )malloc(sizeof(TXTPTR *));
        second->next=NULL;second->ptr=NULL;

        TXTfileName(i,c);
        char name[30]= "./dataset/Econ/";
        strcat(name,c);
        //printf("file name : %s\n",name);

        second->ptr = openf(name,&isFile);
        if(second->ptr == NULL){
          //printf("\nsecond->ptr : NULL\n");
        }else{
          //printf("\nsecond->ptr : NOT NULL\n");
          //printf("second->ptr->string : %s\n",second->ptr->string);
        }

        //printf("Q\nISFILE VALUE = %c\n",isFile);

        if(second->ptr==NULL && isFile!='0'){
            //printf("NULL\n");
        }
        if(isFile=='0'){
            //printf("BREAK CONDITION\n");
            break;
        }else{
            //printf("%s dosyasi okundu\n",c);
        }

        //printf("%s dosyasi ekleniyor.\n",c);
        insertTXT(&first,second);
        //printf("%s dosyasi eklendi.\n",c);



        //printf("\n %d \n",i);
        i++;

        totaltxtcount++;
	}
  /*printf("\n\nECON 1.TXT\n\n");
  printList(first->ptr);
  printf("\n\nECON 2.TXT\n\n");
  printList(first->next->ptr);
  printf("\n\nECON 3.TXT\n\m");
  printList(first->next->next->ptr);*/

  i=1;isFile='1';
  	while(isFile!='0' && i<10){
        TXTPTR *second = (TXTPTR * )malloc(sizeof(TXTPTR *));
        second->next=NULL;second->ptr=NULL;

        TXTfileName(i,c);
        char name[30]= "./dataset/Health/";
        strcat(name,c);
        //printf("file name : %s\n",name);

        second->ptr = openf(name,&isFile);

        //printf("Q\nISFILE VALUE = %c\n",isFile);

        if(second->ptr==NULL && isFile!='0'){
            //printf("NULL\n");
        }
        if(isFile=='0'){
            //printf("BREAK CONDITION\n");
            break;
        }else{
            //printf("%s dosyasi okundu\n",c);
        }

        //printf("%s dosyasi ekleniyor.\n",c);
        insertTXT(&first,second);
        //printf("%s dosyasi eklendi.\n",c);



        //printf("\n %d \n",i);
        i++;


        totaltxtcount++;
	}
  i=1;isFile='1';
  	while(isFile!='0' && i<10){
        TXTPTR *second = (TXTPTR * )malloc(sizeof(TXTPTR *));
        second->next=NULL;second->ptr=NULL;

        TXTfileName(i,c);
        char name[30]= "./dataset/Magazine/";
        strcat(name,c);
        //printf("file name : %s\n",name);

        second->ptr = openf(name,&isFile);

        //printf("Q\nISFILE VALUE = %c\n",isFile);

        if(second->ptr==NULL && isFile!='0'){
           // printf("NULL\n");
        }
        if(isFile=='0'){
            //printf("BREAK CONDITION\n");
            break;
        }else{
            //printf("%s dosyasi okundu\n",c);
        }

        //printf("%s dosyasi ekleniyor.\n",c);
        insertTXT(&first,second);
        //printf("%s dosyasi eklendi.\n",c);



        //printf("\n %d \n",i);
        i++;


        totaltxtcount++;
	}


//	printAllTXT(current);


    /*printf("\nFIRSTTT\n");
    printList(first->ptr);
    printf("\nSECONDDD\n");
    printList(first->next->ptr);
    printf("\nTHIRDDDDD\n");
    printList(first->next->next->ptr);
    if(first->next->next->next->next == NULL){
      printf("forth is null\n");
    }*/
    /*printf("\FOURTHHHHH\n");
    printList(first->next->next->next->next->ptr);
    printf("\nSIXTHHHH\n");
    printList(first->next->next->next->next->next->ptr);
    printf("\nSEVENTHH\n");
    printList(first->next->next->next->next->next->next->ptr);
    printf("\nEIGHTTTT\n");
    printList(first->next->next->next->next->next->next->next->ptr);
    printf("\nNINTHHHH\n");
    printList(first->next->next->next->next->next->next->next->next->ptr);*/

    LIST *pointer = first->ptr;
    LISTE *bas = (LISTE *)(malloc(sizeof(LISTE)));
    bas->list =  pointer;
    bas->next = NULL;

    LISTE *basptr = bas;

    //pointer = pointer->next->next;


  int qwe=0;
  TXTPTR *mainpointer = first;
      while(mainpointer){


           pointer = mainpointer->ptr;

      while(pointer!=NULL){
          LISTE *kuyruk = (LISTE *)(malloc(sizeof(LISTE)));
          kuyruk->list = pointer;
          kuyruk->next=NULL;

          basptr=bas;
          while(basptr->next != NULL){
            basptr = basptr->next;
          }
          basptr->next=kuyruk;
          //printf("x-%s\n",basptr->list->string);



          pointer = pointer->next;
      }

      mainpointer=mainpointer->next;
    }/*
    while(pointer!=NULL){
        LISTE *kuyruk = (LISTE *)(malloc(sizeof(LISTE)));
        kuyruk->list = pointer;
        kuyruk->next=NULL;

        basptr=bas;
        while(basptr->next != NULL){
          basptr = basptr->next;
        }
        basptr->next=kuyruk;
        //printf("x-%s\n",basptr->list->string);



        pointer = pointer->next;
    }*/



    TXTPTR *currentbas = first;
    //printf("\n\nCURRENTBAS->PTR->STRING : %s\n\n",currentbas->ptr->string);
    //printf("\n\nCURRENTBAS->NEXT->PTR->STRING : %s\n\n",currentbas->next->ptr->string);


    /*basptr = bas;
    while(currentbas != NULL){




            while(basptr->next != NULL){
              basptr = basptr->next;
            }

          basptr->next=kuyruk;

      if(currentbas->next !=NULL){
          currentbas = currentbas->next;
      }else{
        break;
      }

    }*/



    //bas->next = kuyruk;

    basptr = bas;
    sort(bas);
    /*printf("\n\n\nBEFORE DUPLICATE\n\n\n");
    while(basptr !=NULL){

      printf("%s;%d;%d\n",basptr->list->string,basptr->list->count,basptr->list->txtcount);

        basptr = basptr->next;
    }*/

    duplicate(bas);
    basptr = bas;
    //printf("\n\n\nAFTER DUPLICATE\n\n\n");
    /*while(basptr !=NULL){

      printf("%s;%d;%d\n",basptr->list->string,basptr->list->count,basptr->list->txtcount);

        basptr = basptr->next;
    }*/


    /*printf("%s\n",bas->list->string);
    printf("%s\n",bas->next->list->string);
    printf("%s\n",bas->next->next->list->string);
    printf("%s\n",bas->next->next->next->next->list->string);*/

    //printf("\n\n\nQWEQWEQWE\n\n\n");
    TXTPTR *suantxt = first;
    LIST *suan = suantxt->ptr;
    LIST *gezen = suan->head;




    printf("\n\n\n\n1st-order term co-occurrence\n\n\n\n");
     while(suantxt != NULL){
      while(suan != NULL){

          while(gezen != NULL){
            if( strcmp(suan->string , gezen->string) != 0 ){
              printf("(%s,%s) ,",suan->string,gezen->string);
            }
            gezen = gezen->next;

          }
          printf("\n");
          if(suan->next !=NULL){
            suan = suan->next;
            gezen = suan;
          }else{
            break;
          }

      }
      if(suantxt->next != NULL){
        suantxt = suantxt->next;
        suan = suantxt->ptr;
        gezen = suan->head;
      }else{
        //printf("breakk\n");
        break;
      }

    }


    /*suan = suantxt->next->ptr;
    gezen = suan->head;


      while(suantxt != NULL){
        while(suan != NULL){

            while(gezen != NULL){
              if( strcmp(suan->string , gezen->string) != 0 ){
                printf("(%s,%s) \n",suan->string,gezen->string);
              }
              gezen = gezen->next;

            }
            if(suan->next !=NULL){
              suan = suan->next;
              gezen = suan;
            }
        }



      }*/
    
    basptr = bas;
    sirala(basptr);

    printf("\n\n\nMy code's big-O time is O(n^3) because i used at most 3 nested loop.\n\n\n");


    
    printf("\n\n\nMOST FREQUETLY USED 10 WORDS IN INPUT SET OF DOCUMENTS AND THEIR TF-IDF VALUES\n\n\n\n\n");
    int counter = 0;
    while(counter < 10 && basptr !=NULL){
      double qwer = (double)basptr->list->count * log((double)totaltxtcount / basptr->list->txtcount);
      
      //printf("%s - %d - %d\n",basptr->list->string,basptr->list->txtcount,basptr->list->count);
      printf("(%s;%d) - ",basptr->list->string,basptr->list->count);
      printf("(tf-idf value : %lf) \n",qwer);

        basptr = basptr->next;
        counter++;
    }

    /*printf("\n\n\n\n\nTF-IDF VALUE OF MOST FREQUETLY USED 10 WORDS IN INPUT SET OF DOCUMENTS\n\n\n\n\n");
    counter = 0;
    while(counter<10 && basptr !=NULL){
      double qwer = (double)basptr->list->count * log((double)totaltxtcount / basptr->list->txtcount);
      
      //printf("(%s;%d) , ",basptr->list->string,basptr->list->count);
      printf("(tf-idf value of %s : %lf) \n",basptr->list->string,qwer);

        basptr = basptr->next;
        counter++;
    }
    printf("\b");*/

  /*printf("\n\n\n\n\nTF-IDF VALUE OF MOST FREQUETLY USED 10 WORDS IN INPUT SET OF DOCUMENTS\n\n\n\n\n");
      counter = 0;
      while(i<10 && basptr !=NULL){
          int idf =0;
          
        
        printf("%s;%d\n",basptr->list->string,basptr->list->count);

          basptr = basptr->next;
          i++;
      }*/



/*
    allwords *firstt= NULL;


    insert(&firstt,"ahmet");
    insert(&firstt,"mehmet");
    insert(&firstt,"zeki");


    printf("main1-%s\n",firstt->str);
    printf("main2-%s\n",firstt->next->str);
    printf("main3-%s\n",firstt->next->next->str);*/
    //printf("totaltxtcount : %d\n",totaltxtcount);
  
  //printf("\nfinished\n");
    return 0;
}


