#include<stdio.h>
#include<stdlib.h>
#include <math.h>

/*
 Array Implementation of MinHeap data Structure
*/

HEAP_SIZE = 20;
int turn,tarrmax;
#define E 2.71

struct Heap{
    double *arr;
    int count;
    int capacity;
    int heap_type; // for min heap , 1 for max heap
};
typedef struct Heap Heap;

Heap *CreateHeap(int cap,int heap_type);
void insert(Heap *h, double key);
void print(Heap *h);
void BT(Heap *h,int ind);
void TB(Heap *h, int parent_node);
double PopMin(Heap *h);



double priorityCalculate(int ei,int emax){

    double q =2*ei;
    double w = 3*emax;

    double y = q / w;
    double x = pow(  y , 3 );
    double num = pow( 2.71 , x );
    return num;

}
/*
int findemax(int arr[][],int a){
    int emax=0,i;
    for(i=0;i<a;i++){
        if(emax < arr[i][1]){
            emax = arr[i][1];
        }
    }
    return emax;
}*/

//return 0 if all are 0
int checkAllEx(int arr[1000][6],int x){
    int i;
    for(i=0 ; i<x ; i++){
        if(arr[i][0] != 0){
            return 1;
        }
    }

}



int main(){

    //double x = 3*priorityCalculate(3,4);
    //printf("x : %lf\n",x);



    FILE *filee,*file;
    char str[4];
    int i=0,a=0;

    if((file = fopen("input.txt","r")) == NULL){
        printf("Input File Could Not Be Opened!\n");
        return 1;
    }

    while (!feof(file)) {
        fscanf(file, "%s", &str);
        if (str[0] == 'P') {
            a++;
        }
    }
    //printf("a = %d\n",a);

    double arr[a][6];

    int qwe,asd;
    for(qwe=0;qwe<a;qwe++){
        for(asd=0;asd<6;asd++){
            arr[qwe][asd]=0;
        }
    }



    if((filee = fopen("input.txt","r")) == NULL){
        printf("Input File Could Not Be Opened!\n");
        return 1;
    }

    a=0;

    while (!feof(filee)) {
        fscanf(filee, "%s", &str);
        if(i==0){
            if( str[0]=='P' ){
                //arr[a][0]=str;
                i=1;
            }else{
                break;
            }
        }else if(i==1){
            arr[a][0]=atof(str);
            i=2;
        }else{
            arr[a][1]=atof(str);
            i=0;
            a++;
        }
    }
    //printf("a : %d\n",a);


    int xe,ye;
    /*for(xe=0;xe<a;xe++){
        for(ye=0;ye<6;ye++){
            printf("%lf ",arr[xe][ye]);
        }
        printf("\n");
    }*/

    fclose(filee);


    double newarr[a][6];
    int pu,pi;
    for(pu=0; pu<a ;pu++){
        for(pi=0;pi<6;pi++){
            newarr[pu][pi]=arr[pu][pi];
        }
    }

    int emax=0,ii;
    for(ii=0;ii<a;ii++){
        if(emax < newarr[ii][0]){
            emax = newarr[ii][0];
        }
    }

    tarrmax=0;
    int jj;
    for(jj=0;jj<a;jj++){
        if(tarrmax < newarr[jj][1]){
            tarrmax = newarr[jj][1];
        }
    }



    //printf("Emax = %d\n",emax);
    //printf("tarrmax = %d\n",tarrmax);

    int tarr=0;


    Heap *heap = CreateHeap(HEAP_SIZE, 0); //Min Heap
    if( heap == NULL ){
        printf("__Memory Issue____\n");
        return 1;
    }

    /*printf("QWERTYUI");
    insert(heap,4);
    print(heap);
    insert(heap,1.004626);
    print(heap);
    insert(heap,2);
    print(heap);
    insert(heap,5);
    print(heap);
    insert(heap,1);
    print(heap);
    printf("\n\n\n");*/

    int arrt,tur,increment;
    //while(heap->count==0 || turn>tarrmax){
    //function check if all ex are 0

    for(tur=1 ; tur<11 ; tur++){
        if(tur==3){
            printf(" ");
        }
        increment=tur;


        for( turn=0 ;  ; turn+=increment ) {


            increment=tur;

            for(arrt=0;arrt<a;arrt++){

                int trn = turn,trrmax=tarrmax,art=arrt;


                if(turn < newarr[arrt][1]){
                    arrt=tarrmax;
                    continue;
                }
                int ex = newarr[arrt][0];
                if (turn >= newarr[arrt][1] && newarr[arrt][2]==0) {
                    if(turn > newarr[arrt][1]){
                        newarr[arrt][4]+=turn-newarr[arrt][1];
                    }
                    if (newarr[arrt][2] == 0) {
                        newarr[arrt][3] = ex;
                        insert(heap, ex);
                        newarr[arrt][5]=1;
                        newarr[arrt][2] = 1;
                    }

                }else if(newarr[arrt][0] > 0){
                    if(newarr[arrt][0] == arr[arrt][0]){
                        newarr[arrt][3] = ex;
                        insert(heap, ex);
                        newarr[arrt][5]=1;
                        newarr[arrt][2] = 1;
                    }else{
                        newarr[arrt][3] = priorityCalculate(ex, emax)*ex;
                        insert(heap, priorityCalculate(ex, emax)*ex);
                        newarr[arrt][5]=1;
                    }
                }

            }

            //printf("%d",turn);
            //print(heap);

            double popmin=PopMin(heap);
            //printf("popmin : %lf\n",popmin);

            int index,yt;
            for( index=0 ; index<a ; index++ ) {
                if(popmin == newarr[index][3]){
                    if(newarr[index][0]<tur){
                        increment=newarr[index][0];
                    }
                    newarr[index][0]-=increment;
                    yt=index;
                    break;
                }
            }

            double popmin2=0,same=1;
            while(popmin2 != -1){
                popmin2 = PopMin(heap);
                if(popmin2 == -1 ) break;



                for( index=0 ; index<a ; index++ ) {
                    if(index == yt )continue;
                    if(popmin2 == newarr[index][3] && newarr[index][5]){
                        newarr[index][4]+=increment;
                        newarr[index][5]=0;
                        break;
                    }
                }



            }

            if(turn == 184){
                printf(" ");
            }


            int zxc=a;
            for(zxc=0 ; zxc<a ;zxc++){
                newarr[zxc][5]=newarr[zxc][3]=0;
            }



            //if all zero return 0

            int i,cond=0;
            for(i=0 ; i<a ; i++){
                if(newarr[i][0] > 0){
                    cond=1;
                    break;
                }
            }

            int sum=0;
            if(!cond && turn>tarrmax){
                printf("\n\nq : %d\n",tur);
                int ind;
                for(ind=0;ind<a;ind++){
                    int uop = newarr[ind][4];
                    printf("P%d:%d \n",ind,uop);
                    sum+=uop;
                }
                //printf("sum : %d\n",sum);
                double as = a;
                double awt = sum/as;
                printf("AWT : %lf \n",awt);

                turn =0;

                //printf("b=%d",b);

                int g,h;
                for(g=0 ; g<a ; g++){
                    for(h=0 ; h<6 ; h++){
                        //printf("%d ",newarr[g][h]);
                        newarr[g][h]=arr[g][h];
                    }
                }

                if(turn == 184){
                    printf(" ");
                }


                break;
            }




        }


    }
    //printf("turn %d is finished \n",turn);





    //print(heap);

    /*for(i=9;i>=0;i--){
        printf(" Pop Minima : %d\n", PopMin(heap));
        print(heap);
    }*/
    return 0;
}




Heap *CreateHeap(int cap,int heap_type){
    Heap *h = (Heap * ) malloc(sizeof(Heap)); //one is number of heap

    //check if memory allocation is fails
    if(h == NULL){
        printf("Memory Error!");
        return 1;
    }
    h->heap_type = heap_type;
    h->count=0;
    h->capacity = cap;
    h->arr = (double *) malloc(cap*sizeof(double)); //size in bytes

    //check if allocation succeed
    if ( h->arr == NULL){
        printf("Memory Error!");
        return 1;
    }
    return h;
}

void insert(Heap *h, double key){
    if( h->count < h->capacity){
        h->arr[h->count] = key;
        BT(h, h->count);
        h->count++;
    }
}



void TB(Heap *h, int parent_node){
    int left = parent_node*2+1;
    int right = parent_node*2+2;
    int min;
    double temp;

    if(left >= h->count || left <0)
        left = -1;
    if(right >= h->count || right <0)
        right = -1;

    if(left != -1 && h->arr[left] < h->arr[parent_node])
        min=left;
    else
        min =parent_node;
    if(right != -1 && h->arr[right] < h->arr[min])
        min = right;

    if(min != parent_node){
        temp = h->arr[min];
        h->arr[min] = h->arr[parent_node];
        h->arr[parent_node] = temp;

        // recursive  call
        TB(h, min);
    }
}

void BT(Heap *h,int ind){
    double temp;
    int parent_node = (ind-1)/2;

    if(h->arr[parent_node] > h->arr[ind]){
        //swap and recursive call
        temp = h->arr[parent_node];
        h->arr[parent_node] = h->arr[ind];
        h->arr[ind] = temp;
        BT(h,parent_node);
    }
}

double PopMin(Heap *h){
    double pop;
    if(h->count==0){
        //printf("\n__Heap is Empty__\n");
        return -1;
    }
    // replace first node by last and delete last
    pop = h->arr[0];
    h->arr[0] = h->arr[h->count-1];
    h->count--;
    TB(h, 0);
    return pop;
}
void print(Heap *h){
    int i;
    printf("____________Print Heap_____________\n");
    for(i=0;i< h->count;i++){
        double QWERT = h->arr[i];
        printf(" ");
        printf("-> %lf ",h->arr[i]);
    }
    printf("->__/\\__\n");
}