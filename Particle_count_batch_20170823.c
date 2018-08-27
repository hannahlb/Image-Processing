//
//  20170423_count_particles.c
//
//
//  Created by Hannah Bourne on 4/17/17.
// For working with Attenuance BMP Images
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int luminance;
typedef luminance pixel1[1];

//define


#pragma pack(push)  // push current alignment to stack
#pragma pack(1)     // set alignment to 1 byte boundary

struct BitMap
{
    unsigned short int Type;
    unsigned int Size;
    unsigned short int Reserved1, Reserved2;
    unsigned int Offset;
} Header;

struct BitMapInfo
{
    unsigned int Size;
    int Width, Height;
    unsigned short int Planes;
    unsigned short int Bits;
    unsigned int Compression;
    unsigned int ImageSize;
    int xResolution, yResolution;
    unsigned int Colors;
    unsigned int ImportantColors;
} InfoHeader;

struct Point
{
    int x;
    int y;
    struct Point * next;
    
} *top = NULL;

struct Particle_Properites
{
    int size_total;
    int attenuance_total;
    struct Particle_Properites * next2;
    
} *top2 = NULL;

struct Pixels
{
    unsigned char Blue,Green,Red;
};


void pop();
void push();
void display();
void pop2();
void push2();


int main(int argc, char **argv )
{
    
    char filename[500];
    char *ff;
    int c,nc=0; //nl=0;
    
    // start writing file header
    char file_out1[] = "output1.csv";
    FILE * f3 = fopen(file_out1, "a");
    if (f3 == NULL) {
        printf("\nCannot open file \n");
        exit(1);
    }
    
    //print file headers for particle class size bins
    fprintf(f3, "filename, number of <1, attenuance, number of 2-74 pixels, attenuance, number of 74-273 pixels, attenuance, number of 100-1000 pixels, attenuance, number of 1000-10000 pixels, attenuance, 10000 to 100000 number of > 100000, attenuance \n");
    
    fclose(f3);
    
    // close file
    printf("at beginning");

    top= NULL;
    top2= NULL;

    
    while((c=getchar())!=EOF)
    {
        
        filename[nc]=c;
        nc++;
        if(c=='\n')
        {
            filename[nc-1]=0;
            ff=(char *)malloc((nc)*sizeof(char));
            memcpy(ff,filename,nc);
            
            nc=0;
            free(ff);
            // printf("%s ", ff);
            
            
            
            
            char   *title;
            char file_in[150];
            char file_out[150];
            int i,j;
            int length_string, position;
            char *result;
            char stype[3];
            
            int padding;
            int size_spix;
            char temp[4];
            
            title = ff;
            
            
            // start writing file header
            char file_out1[] = "output1.csv";
            FILE * f4 = fopen(file_out1, "a");
            if (f4 == NULL) {
                printf("\nCannot open file \n");
                exit(1);
            }
            
            fprintf(f4, "%s,", ff);
            
            fclose(f4);
            
            stype[0]='b';
            stype[1]='c';
            stype[2]='k';
            // printf("%s", title);
            // printf("%s \n", title);
            
            //this should make a pointer to the in file and the out file
            
            result = strstr(title, stype);
            if(result!=NULL){
                position = result- title;
                length_string=strlen(stype);
                
                //  printf("Position in title is %d \n", position);  //tells you starting index of substring
                //  printf("Length of type is %d \n", length_string);
                //   printf("Title is %s \n", title); //tells you length of substring
                length_string=position+length_string;
                j=strlen(title);
                for (i=0;i<j;i++){
                    file_out[i]=title[i];
                    file_in[i]=title[i];
                }
                file_in[j]='\0';
                file_out[j]='\0';
                file_out[length_string]='G'; //puts 'M' in name
                
                // printf("Printing %s \n %s \n", title, file_in);
            }
            
            
            
            
            // Write error to log file, dmsg tail
            //  printf("%s", file_in);
            
            FILE * f_in=fopen(file_in,"r");
            if (f_in == NULL) {
                printf("\nCannot open file\n");
                exit(1);
            }
            
            fread(&Header, sizeof(Header), 1, f_in);
            fread(&InfoHeader, sizeof(InfoHeader), 1, f_in);
            
            //  printf("fread results InfoHeader.Width is %d \n", InfoHeader.Width);
            
            padding = InfoHeader.Width % 4;
            if(padding != 0 ) {
                padding = 4 - padding;
            }
            
            size_spix = sizeof(struct Pixels);
            struct Pixels **pixel_arrayp;
            
            int **Image1;
            
            //  printf("Size of Info Header Height %d \n", InfoHeader.Height);
            //  printf("\nSize_spix: %d\n", size_spix);
            
            /*allocate memory*/
            pixel_arrayp = (struct Pixels **)malloc(InfoHeader.Height*sizeof(struct Pixel*));
            //   printf("allocate pixel_arrayp \n");
            
            Image1 = (int **)malloc(InfoHeader.Height*sizeof(int *));
            
            for(i=0;i<=InfoHeader.Height; i++) {
                pixel_arrayp[i] = (struct Pixels *)malloc(InfoHeader.Width*size_spix);
                Image1[i] = (int *)malloc(InfoHeader.Width*sizeof(int));
                
            }
            //  printf("Image 1 size i is %d j is %d \n", i, InfoHeader.Width);
            // printf("finished allocating memory");
            
            
            //  printf("BitMap Type %d \n Size %d \n Reserved 1 %d \n Reserved 2 %d \n offset %d \n Size %d \n width %d \n height %d \n planes %d \n bits %d \n compression %d \n image size %d \n xres %d \n y res %d \n colors %d \n important colors %d\n Padding %d \n ", Header.Type, Header.Size, Header.Reserved1, Header.Reserved2, Header.Offset, InfoHeader.Size, InfoHeader.Width, InfoHeader.Height, InfoHeader.Planes, InfoHeader.Bits, InfoHeader.Compression, InfoHeader.ImageSize, InfoHeader.xResolution, InfoHeader.yResolution, InfoHeader.Colors, InfoHeader.ImportantColors, padding);
            
            //  printf("\nReading Pixels Info...\n");
            
            
            
            for(i=0; i <= (InfoHeader.Height-1); i++) {
                for(j=0; j <= (InfoHeader.Width-1); j++) {
                    
                    fread(&pixel_arrayp[i][j], 3,1,  f_in); // each color 1 byte, 8 bits per  byte, 24 bits/pixel
                    
                }
                if(padding != 0) {
                    //printf("Padding: %d\n", padding);
                    fread(&temp, padding, 1,  f_in);
                }
            }
            fclose(f_in);
            
            // printf("assigned pixel array p \n");
            
            unsigned int ro,c;
            ro=InfoHeader.Height;
            c=InfoHeader.Width;
            
            
            int r,g,b;
            int l;
            double rw, gw, bw;
            rw=0.333333;
            gw=rw; bw=rw;
            
            for(i=0;i<(InfoHeader.Height-1);i++){
                for(j=0;j<(InfoHeader.Width-1);j++){
                    
                    
                    
                    r=pixel_arrayp[i][j].Red;
                    // printf("red value is %lf \n", r);
                    g=pixel_arrayp[i][j].Green;
                    // printf("blue value is %lf \n", g);
                    b=pixel_arrayp[i][j].Blue;
                    // printf("green value is %lf \n", b);
                    //  pixel_arrayp[i][j].Black=pixel_arrayp[i][j].Blue;
                    l=(rw*r)+(gw*g)+(bw*b)+0.5;
                    //    printf("i value is %d j is %d b is %d l value is %d and ofs is %d \n",i,j,b, l, ofs);
                    
                    // printf("i is %d j is %d and g is %d \n", i, j, g);
                    l=g;
                    // img[i][j]=l;
                    if(l<=3){
                        Image1[i][j]=0;
                        // greater than 128 is background
                    }
                    //else if(l<1){
                    // Image1[i][j]=2;
                    // less than 1 is pure black edges, edge values are equal to 0
                    // }
                    else{
                        Image1[i][j]=1;
                        // 1 is a particle
                    }
                    
                }
            }
            
            //   printf("filled img \n");
            // free(pixel_arrayp);
            //not freeing yet, need later
            //  printf("freed pixel_array \n");
            
            
            int **clusterized;
            clusterized = (int **)malloc(InfoHeader.Height*sizeof(int *));
            for(i=0;i<=InfoHeader.Height; i++) {
                
                clusterized[i] = (int *)malloc(InfoHeader.Width*sizeof(int));
                
            }
            
            
            for (int a = 0; a < (InfoHeader.Height-1); a++){
                for (int b = 0; b < (InfoHeader.Width-1); b++){
                    clusterized[a][b]=-1;
                }
            }
            
            
            int current_class=0;
            
            
            for (int a = 0; a < (InfoHeader.Height-1); a++){
                for (int b = 0; b < (InfoHeader.Width-1); b++){
                    
                    //printf("clusterized[a][b] is %d \n", clusterized[a][b]);
                    if ( clusterized[a][b] != -1 ){ // if has already been processed will not be negative 1
                        continue;
                    }
                    
                    if ( Image1[a][b] == 0 ){
                        clusterized[a][b] = 0;
                        
                        continue;
                    }// check to see if particle, if Image1[a][b] is either 0 or 2 it is not a particle
                    
                    
                    if ( Image1[a][b] == 2 ){
                        clusterized[a][b] = 0;
                        
                        continue;
                    }
                    
                    //if image1 is not a particle, set clusterized to 0, if it is a particle, keep at -1
                    
                    // printf("Found a particle! indices of particle are %d, %d \n", a, b);
                    //   printf("particle should be labeled 1 %d \n", Image1[a][b]);
                    //   printf("Image1 value %d, current_class %d \n", Image1[a][b], current_class);
                    
                    current_class = current_class +1;
                    
                    
                    
                    push(a,b);//push point to top, which is a stack of points. This will be the first entry in stack
                    
                    push2(1,0);
                    
                    
                    int temp_x;
                    int temp_y;
                    //initialize these pointers to zero, then, in pop function the pointers will be set to x and y values from top of stack
                    temp_x=0;
                    temp_y=0;
                    
                    
                    
                    
                    while (top!=NULL){
                        
                        
                        temp_x=top->x;
                        temp_y=top->y;
                        
                        pop();
                        
                        //  printf("temp_x is %d, temp_y is %d, Image1 value is %d, clusterized is %d  \n", temp_x, temp_y, Image1[a][b], clusterized[temp_x][temp_y]);
                        
                        if (clusterized[temp_x][temp_y]!= -1){
                            continue;
                        } //break from loop if clusterized has already been assigned a different value
                        
                        
                        
                        clusterized[temp_x][temp_y] = current_class;
                        
                        
                        int i[8]={-1,0,1,1,1,0,-1,-1};
                        int j[8]={-1,-1,-1,0,1,1,1,0};
                        
                        //
                        for(int k=0;k<8;k++){
                            if(temp_x+i[k]<0 || temp_x+i[k]>InfoHeader.Height || temp_y+j[k]<0 || temp_y+j[k]>=InfoHeader.Width){
                                continue;
                            }
                            if(clusterized[temp_x+i[k]][temp_y+j[k]]>-1){
                                
                                continue;
                            }
                            if (Image1[temp_x+i[k]][temp_y+j[k]]==0){
                                continue;
                            }
                            if (Image1[temp_x+i[k]][temp_y+j[k]]==2){
                                continue;
                            }
                            
                            top2->size_total=top2->size_total+1;
                            top2->attenuance_total=top2->attenuance_total+pixel_arrayp[temp_x+i[k]][temp_y+j[k]].Green;
                            
                            int temp_xx, temp_yy;
                            temp_xx=temp_x+i[k];
                            temp_yy=temp_y+j[k];
                            push(temp_xx, temp_yy);
                            
                        }
                        //end of checking around point
                        
                        
                    } //while loop pop points in stack end
                    //  } //end if loop found particle
                } // end of for j
            } // end of for i
            
            // printf("\n \n \n number of particles including 1 pixel ones is %d \n \n", current_class);
            display();
            free(top2);
            free(top);
            
            
            for(i=0;i<(InfoHeader.Height-1);i++){
                for(j=0;j<(InfoHeader.Width-1);j++){
                    pixel_arrayp[i][j].Green=0;
                    pixel_arrayp[i][j].Blue=255;
                    pixel_arrayp[i][j].Red=150;
                }
            }
            
            
            for(int p=2; p<=current_class; p++){
                for(i=0;i<InfoHeader.Height;i++){
                    for(j=0;j<InfoHeader.Width;j++){
                        if (clusterized[i][j] == p){
                            if (p % 3 == 0){
                                pixel_arrayp[i][j].Green=200;
                                pixel_arrayp[i][j].Blue=200;
                                pixel_arrayp[i][j].Red=0;
                            }
                            else if(p % 3 == 1){
                                pixel_arrayp[i][j].Red=0;
                                pixel_arrayp[i][j].Blue=255;
                            }
                            else if(p % 3 == 2){
                                pixel_arrayp[i][j].Blue=0;
                                pixel_arrayp[i][j].Red=255;
                                pixel_arrayp[i][j].Green=200;
                            }
                        }
                    }
                    
                }
            }
            
            
            
            FILE * f_out=fopen(file_out,"w");
            if (f_out == NULL) {
                printf("\nCannot open file to output \n");
                exit(1);
            }
            
            
            printf("\nWriting Header...\n");
            //save to new bmp file
            fwrite(&Header, sizeof(Header), 1,  f_out);
            fwrite(&InfoHeader, sizeof(InfoHeader), 1, f_out);
            
            printf("Writing pixels \n");
            for(i=0;i<InfoHeader.Height;i++){
                for(j=0;j<InfoHeader.Width;j++){
                    fwrite(&pixel_arrayp[i][j], 3, 1, f_out);
                    //  printf("value is %d", pixel_arrayp[i][j].Black \n);
                }}
            
            free(pixel_arrayp);
            printf("\nDone writing...\n");
            fclose(f_out);
            
            
            
            // new part
            
            //   int size_distribution[current_class];
            /* int particle_attn[current_class];
             
             for(i=0;i<current_class;i++){
             size_distribution[i]=0;
             particle_attn[i]=0;
             }
             
             int avg_size_n, avg_atn;
             
             //
             
             // int g=1;
             
             int temp_1;
             
             for (int g=1; g<=current_class; g++){
             temp_1=0;
             for (int h = 0; h < (InfoHeader.Height-1); h++){
             for (int f = 0; f < (InfoHeader.Width-1); f++){
             if(clusterized[h][f]==g){
             size_distribution[g]=size_distribution[g-1]+1;
             particle_attn[g]=particle_attn[g-1]+pixel_arrayp[h][f].Green;
             //  printf("g is %d, h is %d, f is %d \n", g,h,f);
             }
             }
             }
             }
             
             
             avg_size_n=0;
             avg_particle_atn=0;
             
             for (i=0;i<current_class;i++){
             avg_size_n=avg_size_n+size_distribution[i];
             avg_particle_atn=avg_particle_atn+particle_attn[i];
             }
             
             // printf("sum of ")
             
             int avg_size;
             avg_size=avg_size_n/current_class;
             avg_particle_atn=avg_size_n;
             printf("average size of particle is %d pixels \n", avg_size_n);
             */
        }
        
    } // these last two for reading in batch
}

//allocate two arrays of ints, one where you store the number of pixels in each particle and one where you store attenuation values



//functions

void push(int o, int p)
{
    
    // need to check if empty, if so, set next to null
    struct Point * new_node;
    new_node = (struct Point*)malloc(sizeof(struct Point));
    
    //  printf("o is %d p is %d \n", o,p);
    
    new_node->x = o;
    new_node->y = p;
    
    
    
    //  printf("new_node x is %d new node y is %d \n", new_node->x, new_node->y);
    
    if(top == NULL){
        printf("top is null \n");
        new_node->next = NULL;}
    else
        new_node->next = top;
    top = new_node;
    //   printf("\nInsertion is Success!!!\n");
}


void push2(int q, int r)
{
    
    // need to check if empty, if so, set next to null
    struct Particle_Properites * new_node2;
    new_node2 = (struct Particle_Properites*)malloc(sizeof(struct Particle_Properites));
    
    //  printf("o is %d p is %d \n", o,p);
    new_node2->size_total = q;
    new_node2-> attenuance_total = r;
    //  printf("new_node x is %d new node y is %d \n", new_node->x, new_node->y);
    
    if(top2 == NULL)
        new_node2->next2 = NULL;
    
    else
        new_node2->next2 = top2;
    top2 = new_node2;
    //   printf("\nInsertion is Success!!!\n");
}

/*int pop()
 {
 int retval = -1;
 point_t * next_node = NULL;
 
 if (*head == NULL) {
 return -1;
 }
 
 next_node = (*head)->next;
 retval = (*head)->val;
 free(*head);
 *head = next_node;
 
 return retval;
 }
 */


void pop()
{
    // printf("inside function pop");
    if(top == NULL)
        printf("\nStack is Empty!!!\n");
    else{
        //  printf("stack is not empty, stack contains %d %d", top->x, top->y);
        struct Point *temp = top;
        // xx=&top->x;
        // yy=&top->y;
        //   printf("\nDeleted element: %d, %d", temp->x, temp->y);
        top = temp->next;
        free(temp);
    }
}

void pop2()
{
    // printf("inside function pop");
    if(top2 == NULL)
        printf("\nStack is Empty!!!\n");
    else{
        //  printf("stack is not empty, stack contains %d %d", top->x, top->y);
        
        struct Particle_Properites *temp2 = top2;
        // xx=&top->x;
        // yy=&top->y;
        //   printf("\nDeleted element: %d, %d", temp->x, temp->y);
        top2 = temp2->next2;
        free(temp2);
    }
}

void display()
{
    // printf("reached here");
    
    char file_out2[] = "output2.csv";
    FILE * f = fopen(file_out2, "a");
    if (f == NULL) {
        printf("\nCannot open file \n");
        exit(1);
    }
    char file_out1[] = "output1.csv";
    FILE * f1 = fopen(file_out1, "a");
    if (f1 == NULL) {
        printf("\nCannot open file \n");
        exit(1);
    }
    int ten,hundred,hundredz, thousand,tenthousand,hundredthousand, hundredthousandm;
    int tena,hundreda,hundredaz, thousanda,tenthousanda,hundredthousanda,hundredthousandma;
    
    ten=hundred=hundredz=thousand=tenthousand=hundredthousand=hundredthousandm=0;
    tena=hundreda=hundredaz=thousanda=tenthousanda=hundredthousanda=hundredthousandma=0;
    
    int total_particles=1;
    printf("total particles is %d \n", total_particles);
    if(top2 == NULL)
        printf("\nStack is Empty!!!\n");
    else{
       // struct Particle_Properites *temp2 = top2;
        while(top2->next2 != NULL){
            
            if (top2->size_total>4){
                fprintf(f, "particle number, %d, size, %d, attenuance, %d \n", total_particles, top2->size_total, top2->attenuance_total);
                total_particles=total_particles+1;
            }
            if (top2->size_total<2){
                ten=ten+1;
                tena=tena+top2->attenuance_total;
            }
            else if (top2->size_total>2 && top2->size_total<74){
                hundredz=hundredz+1;
                hundredaz=hundredaz+top2->attenuance_total;
            }
            else if (top2->size_total>74 && top2->size_total<273){
                hundred=hundred+1;
                hundreda=hundreda+top2->attenuance_total;
            }
            else if (top2->size_total>274 && top2->size_total<1000){
                thousand=thousand+1;
                thousanda=thousanda+top2->attenuance_total;
            }
            else if (top2->size_total>1000 && top2->size_total<10000){
                tenthousand=tenthousand+1;
                tenthousanda=tenthousanda+top2->attenuance_total;
            }
            else if (top2->size_total>10000 && top2->size_total<100000){
                hundredthousand=hundredthousand+1;
                hundredthousanda=hundredthousanda+top2->attenuance_total;
            }
            else if (top2->size_total>100000){
                hundredthousandm=hundredthousandm+1;
                hundredthousandma=hundredthousandma+top2->attenuance_total;
            }
            
           // printf(" total particles greater than 4 is %d \n", total_particles);
          //  fprintf(f1, " %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d \n", ten, tena, hundredz, hundredaz,hundred, hundreda, thousand, thousanda, tenthousand, tenthousanda, hundredthousand, hundredthousanda, hundredthousandm, hundredthousandma);
            top2 = top2 -> next2;
            
        }
        
        printf(" total particles greater than 4 is %d \n", total_particles);
        printf(" \n reached here \n");
        fprintf(f1, " %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d \n", ten, tena, hundredz, hundredaz,hundred, hundreda, thousand, thousanda, tenthousand, tenthousanda, hundredthousand, hundredthousanda, hundredthousandm, hundredthousandma);
        printf(" %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d \n", ten, tena, hundredz, hundredaz,hundred, hundreda, thousand, thousanda, tenthousand, tenthousanda, hundredthousand, hundredthousanda, hundredthousandm, hundredthousandma);
        // printf("%d--->NULL",temp2->size_total);
        // printf("total number of particles is %d \n", total_particles);
        fclose(f);
        fclose(f1);
        
    }
}

