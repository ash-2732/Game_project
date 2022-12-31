#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <algorithm>


void higscore(int t)
{
FILE *fp;
fp = fopen("highscore.txt","r");
int a[5];
int i=0;
int d;
while(fscanf(fp,"%d",&a[i])==1){
	i++;
	if(i==5)  break;
}

if(t>a[4]) {
 a[4]=t;
for(i=0;i<4;i++){
	for(int j=i+1;j<5;j++){
		if(a[i]<a[j]){
			int tmp=a[i];
			a[i]=a[j];
			a[j]=tmp;
		}
	}
}
}


FILE *fw=fopen("highscore.txt","w");
fprintf(fw,"%d\n%d\n%d\n%d\n%d\n",a[0],a[1],a[2],a[3],a[4]);

fclose(fp);
fclose(fw);
}
