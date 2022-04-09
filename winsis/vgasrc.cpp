/*
vgasrc.cpp
Copyright (C) 2021  Yusuf K. Hanoğlu
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; version 2
of the License.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA. 
 */


#include <stdint.h>
#include "qwerty.cpp"

// Password
const char* passwd = "ADMIN";

// PERSONAL:
#define _PersonalCount 2
const char* personal_title = "CONFIGURING MESSAGES";
const char* personal[_PersonalCount] = {
    "ALL MESSAGES CAN BE EDITTED ON TOP OF THE VGASRC CPP SOURCE",
    "FILE"
};

// UTILITIES
#define _UtilitiesCount 1
const char* utilities_title = "COMPILATION OF SOURCE";
const char* utilities[_UtilitiesCount] = {
    "LOOK AT BUILD SHELL FILE"
};

// ABOUT
#define _AboutCount 5
const char* about_title = "ABOUT ISOLATED OS";
const char* about[_AboutCount] = {
    "ISOLATED OS VERSION A",
    "THIS OPERATING SYSTEM IS DEVELOPED FOR ENTERTAINMENT PURPOSES",
    "INSPIRED BY FAMOUS VIDEO GAME AND NOT RELATED WITH ANY TRADEMARK",
    "OF IT",
    "PROJECT LICENSED UNDER GPL VERSION TWO"
};

void ppx(char,int,int); // Put pixel
void ppx(char,int32_t); // Put pixel
void prc(char,int,int,int,int); // Put rectangle
void pbr(char,char,int,int,int,int,int,int); // Put blank rectangle function
void message(const char*);
void print(char, int,int,int,int);
void print(char,int,int,const char*,int);
void print(char, int,int,int);
void print(char,int,int,const char*);
int pxlength(const char *);
int ccsize2(const char*);
int csize2(char *);
int initmenu();

static int32_t framebufferloc = 0;

const int screen_x = 1024;
const int screen_y = 768;
const int olu_pixel = 0;//254

void ppx(char color, int x, int y){

	int b;
	int32_t pxloc = framebufferloc;
	pxloc += screen_x*y;//320
		    //319,199
	pxloc += x;
	

	ppx(color, pxloc);
	
	
return;

}
void ppx(char color,int32_t pos){
int b;
pos+=olu_pixel;
asm( "movl %1, %%edi;"
     		:"=r"(b)
		:"r"(pos)
		:"%edi"
     		);

	//asm( "addl  $400000,%edi");
	asm( "movb %1, %%al"
		:"=r"(b)
		:"r"(color)
		:"%al");
	
	asm( "movb %al,(%edi)");


}
void prc(char color, int basx, int basy, int sonx, int sony){
for(int i=0;i<sonx;i++){
	for(int j=0;j<sony;j++)
		ppx(color,basx+i,basy+j);
}
return;
}
void pbr(char color, char colorinterior, int basx, int basy, int sonx, int sony, int borderpxx, int borderpxy){
prc(color,basx,basy,sonx,sony);
prc(colorinterior,basx+borderpxx,basy+borderpxy,sonx-borderpxx*2,sony-borderpxy*2);
return;
}

void message(const char* msg){



}

const int harfler_size = 32;
int harfler[harfler_size] = {'A','B','C','Ç','D','E','F','G','Ğ','H','I','İ','J','K','L','M','N','O','Ö','P','Q','R','S','Ş','T','U','Ü','W','V','X','Y','Z'};  
int arkabosluk[harfler_size]={0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  1,  1,  0,  0,  0,  0,  1,  0,  1,  1,  1,  0,  1,  1,  0,  1,  1,  0,  0};
int onbosluk[harfler_size]=  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  3,  3,  1,  1,  -1, 0,  0,  0,  1,  0,  1,  1,  1,  1,  1,  1,  -1, 0,  1,  1,  0};

bool alfabedevarmi(int ch){
int harfnumara = -1;
	
	for(int i=0;i<harfler_size;i++){
		if(ch==harfler[i]){
			harfnumara = i;break;
		}		
	}

	if(ch == ' ')
		harfnumara = -2;
	if(harfnumara == -1)
		return false;

	return true;

}
int kacinciharf(int ch){
int harfnumara = -1;
	
	for(int i=0;i<harfler_size;i++){
		if(ch==harfler[i]){
			harfnumara = i;break;
		}		
	}

	if(ch == ' ')
		harfnumara = -2;
	if(harfnumara == -1)
		return -1;

	return harfnumara;

}

int pointer_print = 0;
void print(char color, int x, int y, int ch, int scale){
	int harfnumara = -1;
	for(int i=0;i<harfler_size;i++){
		if(ch==harfler[i]){
			harfnumara = i;break;
		}		
	}
	if(harfnumara == -1)
		return;
	pointer_print-=arkabosluk[harfnumara];
	int32_t pos = framebufferloc;
	pos += y*screen_x;
	pos += x;
	for(int i=0;i<12;i++){
	for(int j=0;j<12;j++){
		if(charpixel[harfnumara][i*12+j]){
      for(int ii=0;ii<scale;ii++)
        for(int jj=0;jj<scale;jj++)
          ppx(color,pos+i*scale*screen_x+ii*screen_x+j*scale+jj+pointer_print*scale);
			}
	}
	}
	pointer_print-=onbosluk[harfnumara];
}

void print(char color, int x, int y, int ch){
  print(color, x, y, ch, 1);
}
void print(char color, int x, int y, const char* ch, int scale){
pointer_print=0;
	int chr = 0;
	for(int i=0;i<ccsize2(ch);i++){
		chr = ch[i];
		if(!alfabedevarmi(chr)){
			chr = 0;
			*((char*)&chr) = ch[i+1];
			*((char*)&chr+1)=ch[i];
			i++;
		}
		print(color,x,y,chr,scale);
		pointer_print+=10;
	}
	pointer_print = 0;
}
void print(char color, int x, int y, const char* ch){
  print(color, x, y, ch, 1);
}

int pxlength(const char* ch){//bosluk isi bozar

	int chr = 0;
	int num = 0;
	int uzunluk = 0;
	for(int i=0;i<ccsize2(ch);i++){
		chr = ch[i];
		if(!alfabedevarmi(chr)){
			//chr = (ch[i]-'0')*10 + (ch[i+1]-'0');
			//chr = (ch[i+1] << 8)+ch[i];
			chr = 0;
			*((char*)&chr) = ch[i+1];
			*((char*)&chr+1)=ch[i];
			
			i++;
			
		}

		if(alfabedevarmi(chr)){
		num = kacinciharf(chr);
		uzunluk -= arkabosluk[num];
		uzunluk -= onbosluk[num];
		}
		uzunluk += 10;
	}
	return uzunluk;


}
bool ccesit2(const char* a, const char* b){

	int sizea = ccsize2(a);
	int sizeb = ccsize2(b);
 	if(sizea==sizeb){
		bool donut = true;
		for(int i=0;i<sizea;i++){
			if(a[i] != b[i])
				donut = false;
		}
		return donut;
	}
	else
		return false;

}


int ccsize2(const char * ch)
{

    int Size = 0;
    while (ch[Size] != '\0') Size++;
    return Size;
}
int csize2(char * ch)
{

    int Size = 0;
    while (ch[Size] != '\0') Size++;
    return Size;
}

void vgakurulum(int32_t framebuffer){
	framebufferloc = framebuffer;
	prc(0xbf,0,0,1024,768);
	
	int ux = 250;
	int uy = 100;
	int br = 10;
	int d = 0;
	bool b = 1;
	int ch = 0;
	char guvenlik[20];
	int guvenlik_i=0;
	while(true){
	b=1;d=0;
	for(int i=0;i<20;i++)
		guvenlik[i]=0;
	guvenlik_i=0;

  int uxSignIn = 550;	
  int uySignIn = 180;
  
	prc(0x00,0,0,screen_x,screen_y);//ekranı temizler
	prc(0x30,(screen_x-olu_pixel-uxSignIn)/2,(screen_y-uySignIn)/2,uxSignIn,uySignIn);//kutu
  // prc(0x30,(screen_x-olu_pixel-uxSignIn)/2,(screen_y-uySignIn)/2+35,uxSignIn-br/2,br/2);//ayrac
	print(0x00,(screen_x-olu_pixel-uxSignIn)/2+pxlength("SIGNAIN")/5+112,(screen_y-uySignIn)/2+uySignIn/2-5-30-30,"SIGN IN", 5);
	ch = getkey();
  prc(0x00,0,0,screen_x,screen_y); //ekranı temizler

	while(true){

	
	prc(0x30,(screen_x-olu_pixel-ux)/2,(screen_y-uy)/2,ux,uy);//kutu
	prc(0xBF,(screen_x-olu_pixel-ux+br)/2,(screen_y-uy+br)/2,ux-br,uy-br);//beyaz
	prc(0x30,(screen_x-olu_pixel-ux)/2,(screen_y-uy)/2+35,ux-br/2,br/2);//ayrac
	print(0x0f,(screen_x-olu_pixel-ux)/2+pxlength("LOGINAID")/5,(screen_y-uy)/2+uy/2-5-30,"LOGIN ID");
	print(0x0f,(screen_x-olu_pixel-ux)/2+pxlength("LOGINAID")/5,(screen_y-uy)/2+uy/2+10,guvenlik);
	ch = getkey();
	if(ch == -100)
		break;
	else if(ch == ' ' || ch=='Ş'|| ch=='İ'|| ch=='Ğ'|| ch=='Ü'|| ch=='Ö'|| ch=='Ç'){}
	else if(ch == -9){
		if(guvenlik_i>0){
		guvenlik_i--;
		guvenlik[guvenlik_i]=0;	}	
	}
	else if(guvenlik_i==19){}
	else if(ch=='Q'||ch=='W'||ch=='E'||ch=='R'||ch=='T'||ch=='Y'||ch=='U'||ch=='I'||ch=='O'||ch=='P'||ch=='A'||ch=='S'||ch=='D'||ch=='F'||ch=='G'||ch=='H'||ch=='J'||ch=='K'||ch=='L'||ch=='Z'||ch=='X'||ch=='C'||ch=='V'||ch=='B'||ch=='N'||ch=='M'){
	guvenlik[guvenlik_i]=ch;
	guvenlik_i++;
	}
	}
	
	if(!ccesit2(guvenlik,passwd)){
	for(int i=0;i<5;i++){
	if(b){
	prc(0x04,(screen_x-olu_pixel-uxSignIn)/2,(screen_y-uySignIn)/2,uxSignIn,uySignIn);
	print(0x00,(screen_x-olu_pixel-uxSignIn)/2+pxlength("ACCESSADENIED")/5+5,(screen_y-uySignIn)/2+uySignIn/2-5-30-30,"ACCESS DENIED", 4);
	}else{
	for(long k=0;k<8000;k++)
	for(long l = 0;l<99999;l++)
		d=(4000*8)/56*0.4;
	
	prc(0x00,0,0,screen_x,screen_y);
	for(long k=0;k<999;k++)
	for(long l = 0;l<99999;l++)
		d=(4000*8)/56*0.4;
	}
	b=!b;
	}
	}
	else
		break;
	}
	//prc(0xBF,(screen_x-olu_pixel-ux)/2,(screen_y-uy)/2,ux,uy); //yarım temizleme
  prc(0xBF,0,0,screen_x,screen_y);
	int ux2 = 650;
	int uy2 = 100;int uy2arti = 80;

	for(long k=0;k<5000;k++)
	for(long l = 0;l<99999;l++)
		d=(4000*8)/56*0.4;
	
	
	print(0x30,(screen_x-olu_pixel/2-ux2+br)/2-15,(screen_y-uy2+br)/3+uy2arti,"ACCESS GRANTED", 5);
	for(int jj=0;jj<1;jj++){//6
	prc(0x30,(screen_x-olu_pixel/2-ux2)/2,(screen_y-uy2)/2+uy2arti,ux2-olu_pixel/2,uy2-olu_pixel/5);
	prc(0xBF,(screen_x-olu_pixel/2-ux2+br)/2,(screen_y-uy2+br)/2+uy2arti,ux2-olu_pixel/2-br,uy2-br-olu_pixel/5);//arka plan

	for(int i=0;i<ux2-olu_pixel/2-br;i++){
		for(long k=0;k<99;k++)//999
		for(long l = 0;l<9999;l++)
			d=(4000*8)/56*0.4;
	prc(0x02,(screen_x-olu_pixel/2-ux2+br)/2+i,(screen_y-uy2+br)/2+uy2arti,1,uy2-br-olu_pixel/5);//doluyor

	}
  prc(0xBF,0,0,screen_x,screen_y); //ekranı temizler
  prc(0x48,10,10,screen_x-2*10,30);
  prc(0xFF,screen_x-35,15,20,20);
  print(0xBF,15,12,"PERSONAL TERMINAL",2);
	}

	initmenu();

	



}
void reinitfourbox(int focus){
    print(0x48, 30, 100, "FOLDERS", 2);
	char chr[][30] = {"PERSONAL","UTILITIES","ABOUT", "SIGN OUT"};
    for(int i=0;i<4;i++){ // Draws four rectangles
        if(i==focus){
            prc(0x0F,10,150+142*i,245+20*2,135);
            pbr(0x0F,0xBF,30,150+142*i,245,135,4,4);
            print(0x0F,35,160+142*i,chr[i],2); }else{ pbr(0x48,0xBF,30,150+142*i,245,135,4,4);
            print(0x0F,35,160+142*i,chr[i],2);
        }
    }
    
    print(0x0F,150,screen_y-20,"W GO UP");
    print(0x0F,300,screen_y-20,"S GO DOWN");
    print(0x0F,450,screen_y-20,"E SELECT");
    print(0x0F,600,screen_y-20,"Q BACK");
    print(0x0F,750,screen_y-20,"L QUICK LOCK");
}
void reinittitlebox(const char* title){
    pbr(0x0F,0x76,350,60,600,65,2,2);
    print(0x0F,360,73,title,3);
    
}
void reinitcontentbox(int focus){
if(focus==0){
    reinittitlebox(personal_title);
    pbr(0x48,0xBF,350,162,640,550,2,2); 
    for(int i=0;i<_PersonalCount;i++)
        print(0x0F,360,180+i*20,personal[i]);
}
else if(focus==1){
    reinittitlebox(utilities_title);
    pbr(0x48,0xBF,350,162,640,550,2,2); 
    for(int i=0;i<_UtilitiesCount;i++)
        print(0x0F,360,180+i*20,utilities[i]);
}
else if(focus==2){
    reinittitlebox(about_title);
    pbr(0x48,0xBF,350,162,640,550,2,2); 
    for(int i=0;i<_AboutCount;i++)
        print(0x0F,360,180+i*20,about[i]);
    print(0x0F,360,680,"DEVELOPER YUSUF HANOĞLU");
}
    
}
int focus = 0;
void logoutmessage(){    
    
    int uxSignIn = 550;	int uySignIn = 180;
	pbr(0x04,0x48,(screen_x-olu_pixel-uxSignIn)/2,(screen_y-uySignIn)/2,uxSignIn,uySignIn,5,5);
	print(0x00,(screen_x-olu_pixel-uxSignIn)/2+pxlength("AREAYOUASUREATOALOGAOUT")/5+15,(screen_y-uySignIn)/2+uySignIn/2-5-30-30,"ARE YOU SURE TO LOG OUT", 2);
	pbr(0xBF,0x48,(screen_x-olu_pixel-uxSignIn)/2+65,(screen_y-uySignIn)/2+75,200,70,5,5);
	print(0xBF,(screen_x-olu_pixel-uxSignIn)/2+110,(screen_y-uySignIn)/2+90,"BACK",3);
	pbr(0xBF,0x48,(screen_x-olu_pixel-uxSignIn)/2+275,(screen_y-uySignIn)/2+75,200,70,5,5);
	print(0xBF,(screen_x-olu_pixel-uxSignIn)/2+290,(screen_y-uySignIn)/2+90,"SELECT",3);
    char ch; 
    while(1){
        ch = getkey();
    if(ch=='E')
        outb(0x64, 0xFE);
    else if(ch=='Q'){
        prc(0xBF,0,50,screen_x,screen_y);
        reinitfourbox(focus);
        reinitcontentbox(focus);
        break;
    }    
    }
}
int initmenu(){
	int pivot1 = 25;
	//print(0x0f,(screen_x-olu_pixel)/2,(screen_y)/2/2-5 + pivot1,"X");
	char ch = ' ';
	while(1){
    prc(0xBF,0,50,screen_x,screen_y);
    reinitfourbox(focus);
    reinitcontentbox(focus);
    while(1){
	ch = getkey();
	if(ch=='W'&&focus>0){
		focus--;
        break;
    }
	else if(ch=='S'&&focus<3){
		focus++;
        break;
    }
    else if(ch=='E'){
        if(focus==3){
            logoutmessage();
            break;
        }
    }
    else if(ch=='L'){
      outb(0x64, 0xFE);
    }
    }
	}
    
    return 0;
}


