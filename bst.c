#include<stdio.h>
#include<stdlib.h>
typedef struct n{
    int data;
    struct n*sol;
    struct n*sag;
}node;
int sum=0,count=0,x,y,sayi,seviye;
int inorder[11];
node*ekle(node * agac,int x);
void dolas(node * agac);
int leaf_count(node*agac);
void leafSum(node*agac);
int max(node*agac);
int min(node*agac);
void menu();
node*arama(node * agac,int y);
int buyukler(node * agac,int sayi);
void printlevel(node *agac, int istenen, int bulundugumLevel);
int yukseklik(node *agac);
void seviyedekiNodelar(node*agac,int);

int main(){
    
    node*agac=NULL;
    agac= ekle(agac,105);
    agac= ekle(agac,87);
    agac= ekle(agac,126);
    agac= ekle(agac,74);
    agac= ekle(agac,95);
    agac= ekle(agac,117);
    agac= ekle(agac,132);
    agac= ekle(agac,45);
    agac= ekle(agac,80);
    agac= ekle(agac,90);
    agac= ekle(agac,100);
    dolas(agac);
    sum=0;
    leafSum(agac);
    printf("min deger: %d , max deger: %d ",min(agac),max(agac));
    printf("yaprak node ortalamasi : %d ",sum/leaf_count(agac));
    printf("yaprak node sayisi : %d",leaf_count(agac));
   
    while(1)
    {
        int selection=0;
    printf("1-Ekleme yapmak icin 1'i tuslayin: \n2-İstediginiz seviyedeki dugumleri gormek icin 2'yi tuslayin: \n3-Eleman aramak icin 3'u tuslayin: \n4-Yaprak dugumlerin ortalamasini gormek icin 4'u tuslayin: \n5-Sectiginiz degerden buyuk elemanlari listelemek icin 5'i tuslayin: \nSeciminiz: ");
    scanf("%d",&selection);
    switch(selection)
    {
        case 1:
            printf("agaca eklemek icin bir sayi girin: ");
            scanf("%d",&x);
            ekle(agac,x);
            break;   
        case 2:
            seviyedekiNodelar(agac,seviye);
            break;
        case 3:
            printf("Aramak istediginiz sayiyi girin: ");
            scanf("%d",&y);
            arama(agac,y);
             
               break;
        case 4:
           leafSum(agac); 
           printf("yaprak node ortalamasi : %d ",sum/leaf_count(agac)); 
           break;
        case 5:   
           buyukler(agac,sayi);
           break;
     
    }


    }

    return 0;
}
int min(node*agac)
{
    while(agac->sol!=NULL)
        agac=agac->sol;
    return agac->data;    
}

int max(node*agac)
{
    while(agac->sag!=NULL)
        agac=agac->sag; //sagın solu null olmadığı sğrece dön ve sağdaki yeni ağacları agaç a ata
    return agac->data;    
}               
void leafSum(node*agac)
{ 
        if (agac == NULL) 
            return; 
       
        
        if (agac->sol == NULL && agac->sag == NULL) 
            sum += agac->data; 
       
       
        leafSum(agac->sol); 
        leafSum(agac->sag); 
    } 

int leaf_count(node*agac)
{
    if(agac==NULL)
        return 0;
    if(agac->sol==NULL && agac->sag==NULL)
        return 1;
    else
    {
        return leaf_count(agac->sag)+leaf_count(agac->sol);
    }
}
void dolas(node * agac)
{ //infix olarak yazıyoruz LNR küçükten büyüğe sıralamış oldu
    if(agac==NULL)
    {
        return;
        }
        else{
             dolas(agac->sol);//agacın solu için recursive olarak tekrar dolaşma fonk çağırdım
             printf("%d ",agac->data);//nodeu yazdım
             dolas(agac->sag);//sağı için tekrar dolaş recursive    
            }
}
void dolas2(node * agac,int sayi)
{ //infix olarak yazıyoruz LNR küçükten büyüğe sıralamış oldu
    if(agac==NULL)
    {
        return;
        }
        else{
             dolas(agac->sol);//agacın solu için recursive olarak tekrar dolaşma fonk çağırdım
             for(int i=0;i<11;i++)
             {  inorder[i]=agac->data;
                
                if(inorder[i]==sayi){
                    i++;
                    printf("%d\t",inorder[i]);
                }
             }
             dolas(agac->sag);//sağı için tekrar dolaş recursive    
            }
}
node*ekle(node * agac,int x)
{ //ekleme fonksiyonumuz node türünden eklenecek ağacı ve değeri alıyor
    
    if(agac == NULL){ //ağaç boşsa root düğüm ekleyerek başlıyoruz
        node *root = (node*)malloc(sizeof(node));
        root->sag=NULL;
        root->sol=NULL;
        root->data=x;//dataya da fonksiyona girilen değerin atamasını yapıyoruz
        return root;

    }
    if (agac->data < x){ //gezwrken bulduğum data ekleyeceğimden küçükse bu datanın sağına eklem yapmalıyım elimde büyük olan var
            agac->sag=ekle(agac->sag,x);
            return agac;
    }
    
    agac->sol=ekle(agac->sol,x); //yukarıdaki ifin dışındaki durumlarda buraya düşüyor 
    return agac;
    
}
int yukseklik(node *agac)
{
    int solYukseklik, sagYukseklik;
    if (agac != NULL)
    {
        solYukseklik = yukseklik(agac->sol);
        solYukseklik = yukseklik(agac->sag);
        if (solYukseklik > sagYukseklik)
            return(solYukseklik+1);
        else 
            return(sagYukseklik+1);
    }
    return -1;
}
void printlevel(node *agac, int istenen, int bulundugumLevel)
{
    if (agac)
    {
        if (istenen == bulundugumLevel)
            printf("%d\t", agac->data);
        else
        {
            printlevel(agac->sol, istenen, bulundugumLevel + 1);
            printlevel(agac->sag, istenen, bulundugumLevel + 1);
        }
    }
}
void seviyedekiNodelar(node* agac,int seviye)
{
    int h, i;
 
    h = yukseklik(agac);
    printf("Elemanlari goruntulemek icin bir seviye girin:");
    scanf("%d",&seviye);
    for (i = 0;i < h;i++)
    {
        printf("\nLEVEL %d  :", seviye);
        printlevel(agac, seviye, 0);
        printf("\n");
    }
}
node* arama(node *agac,int aranan)
{   int sayac=0;
    node*temp=agac;
    while(temp!=NULL)
    {
        if(temp->data==aranan){
            return temp;
            count++;
            printf("aradiginiz deger %d, %d adimda bulundu!",temp->data,count);
            
        }
        else if(temp->data > aranan) {
            count++;
            temp=temp->sol; 
        }
        else if(temp->sag==NULL && temp->sol==NULL)
               printf("Aradiginiz deger bulunamadi");     
        else 
            count++;
            temp=temp->sag;
    }
    return temp;
}
int buyukler(node*agac,int sayi)
{  
     int dizi[11];
    printf("Girdiginiz sayidan buyuk sayilari gprmek icin bir deger giriniz: ");
    scanf("%d",&sayi);
    while(agac!=NULL)
    {
    if(sayi == agac->data)
    {
        for(int i=0;i<11;i++)
        {
            return agac->sag->data;
            dizi[i]=agac->sag->data;
            printf("Girilen degerden buyuk %d. deger:%d ",i,dizi[i]);
            agac=agac->sag;
        }
    } 
    else if(agac->data < sayi)
    {
        dolas2(agac,sayi);

    }
    else if(sayi > agac->data)
    {
        for(int i=0;i<11;i++)
        {
            printf("Girilen degerden buyuk %d. deger: %d \n: ",i,agac->data);
            agac=agac->sag;
        }   
    }
return -1;
}
return 0;
}