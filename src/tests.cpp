#include "tests.h"

// 练习1，实现库函数strlen
int my_strlen(char *str) {
    int num=0;
    while(*str != '\0'){
        num++;
        str++;
    }
    return num;
}


// 练习2
void my_strcat(char *str_1, char *str_2) {
    int a=0;
    while (str_1[a]!='\0'){
        a++;
    }
    int b=0;
    while (str_2[b]!='\0'){
        str_1[a]=str_2[b];
        b++;
        a++;    
    }
    str_1[a]='\0';
}


// 练习3
char* my_strstr(char *s, char *p) {
    int a=0;
    while (p[a]!='\0'){
        a++;
    }
    int b=0;
    while (s[b]!='\0'){
        b++;
    }
    if(a==0) return s;
    if(a>b) return 0;
    for (int i=0;i<b-a+1;i++){
        int j=0;
        while(j<a&&s[i+j]==p[j]){
            j++;
        }
        if(j==a){
            return &s[i];
        }
    }
    return 0;
}

//练习4
void rgb2gray(float *in, float *out, int h, int w) {
    for (int i=0;i<h;i++){
        for (int j=0;j<w;j++){
            int a=(i*w+j)*3;
            float R=in[a];
            float G=in[a+1];
            float B=in[a+2];
            float V= 0.1140 * B  + 0.5870 * G + 0.2989 * R;
            out[i*w+j]=V;
        }
    }
}

// 练习5
void resize(float *in, float *out, int h, int w, int c, float scale) {
    int new_h = h * scale, new_w = w * scale;
    for (int i=0;i<new_h;i++){
        for (int j=0;j<new_w;j++){
            for (int k=0;k<c;k++){
                float x0=j/scale;
                float y0=i/scale;
                int x1 = static_cast<int>(x0); 
                int y1 = static_cast<int>(y0);
                int x2 = x1+1;
                int y2 = y1+1;
                if (x2>=w || y2>=h){
                    break;
                }else{
                    float P1 = in[(y2*w+x1)*c+k];
                    float P2 = in[(y2*w+x2)*c+k];
                    float P3 = in[(y1*w+x1)*c+k];
                    float P4 = in[(y1*w+x2)*c+k];
                    float dx = x0-x1;
                    float dy = y0-y1;
                    float Q = P1 * (1 - dx)*(1 - dy) + P2 * dx*(1 - dy)+ P3 * (1 - dx)*dy + P4 * dx*dy;
                    out[(i*new_w+j)*c+k]=Q;
                }
            } 
        }
    }
}


// 练习6
void hist_eq(float *in, int h, int w) {
    for (int i=0;i<h;i++){
        for (int j=0;j<w;j++){
            in[i*w+j]=static_cast<int>(in[i*w+j]+0.5);
        }
    }
    float n[256];
    for (int i=0;i<256;i++){
        n[i]=0;
    }
    for (int i=0;i<256;i++){
        for (int j=0;j<w*h;j++){
            if (in[j]==i){
                n[i]++;
            }
        }
    }
    float N[256];
    for (int i=0;i<256;i++){
        N[i]=n[i]/(w*h);
    }
    for (int i=0;i<255;i++){
        N[i+1]=N[i]+N[i+1];
    }
    for (int i=0;i<256;i++){
        n[i]=static_cast<int>(N[i]*255+0.5);
    }
    for (int i=0;i<h;i++){
        for (int j=0;j<w;j++){
            in[i*w+j]=n[(int)in[i*w+j]];  
        }
    }
}