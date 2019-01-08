

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Char.h>
#include <Adafruit_NeoPixel.h>  


#define PIN_l A2  //A2 腳位控制左側LED

#define PIN_r A3  //A3 腳位控制右側LED

int number4strip=15; // 每條LED燈條上有的LED數目

Adafruit_NeoPixel strip_l = Adafruit_NeoPixel(number4strip, PIN_l, NEO_GRB + NEO_KHZ800);
//定義左側的燈條


Adafruit_NeoPixel strip_r = Adafruit_NeoPixel(number4strip, PIN_r, NEO_GRB + NEO_KHZ800);
//定義右側的燈條


ros::NodeHandle  nh;
 std_msgs::String str_msg;
ros::Publisher chatter("color4led", &str_msg); 



void messageCb( const std_msgs::String& toggle_msg){

 String state;
 state=toggle_msg.data;



if (state== "demo")
  {
   breathe(1,0); //橘色呼吸燈
    
    breathe(1,1); //綠色呼吸燈
     
    backward(0,5,0); //藍色兩側跑馬燈, 由標號最大的led往零號led跑
    
    backward(0,5,1); //藍色左側跑馬燈, 由標號最大的led往零號led跑
    
    backward(0,5,2); //藍色右側跑馬燈, 由標號最大的led往零號led跑

    forward(0,5,0); //藍色兩側跑馬燈, 由標號零號led往標號最大的led跑
    
    forward(0,5,1); //藍色左側跑馬燈, 由標號零號led往標號最大的led跑
    
    forward(0,5,2); //藍色右側跑馬燈, 由標號零號led往標號最大的led跑

    
blibli(0);  //閃黃燈
blibli(1);   //閃紅燈
blibli(2);  //閃紫燈
    }
 
 
   if (state== "q")
  {
    breathe(1,0); //橘色呼吸燈
    }

    if (state== "w")
  {
    breathe(1,1); //綠色呼吸燈
    }



    if (state== "e")
  {
    backward(0,5,0);  //藍色兩側跑馬燈
    }
  if (state== "r")
  {
backward(0,5,1);       //藍色左側跑馬燈
    }

    if (state== "t")
  {
backward(0,5,2);       //藍色右側跑馬燈
    }

     if (state== "y")  
  {
    
blibli(0);            //閃黃燈
    }

if (state== "u")
  {
    
blibli(0);          //閃黃燈
    }
    if (state== "i")
  {
    
blibli(0);          //閃黃燈
    }
if (state== "o")
  {
    
blibli(1);          //閃紅燈
    }
    if (state== "p")
  {
    
blibli(2);        //閃紫燈
    }


}

ros::Subscriber<std_msgs::String> sub("state", messageCb );




void setup()
{
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
strip_l.begin();
  strip_l.show(); // Initialize all pixels to 'off'
  strip_r.begin();
  strip_r.show(); 

  
}

void loop()
{
  
  nh.spinOnce();
  delay(500);
}



void breathe(int pace, int color) {


int wait;
int ma=180;
int radius=90;
int t;
 int v;
 int slope;
 int slope2;
 int temp;
 float w;
 t=0;
 v=0;

 if(pace==0)
 {
  w=0.03;
 slope=3;
 slope2=-3;
 wait=100;
 }

 if(pace==1)
 {
  w=0.02;
 slope=2;
 slope2=-2;
 wait=200;
 }

  if(pace==2)
 {
  w=0.01;
 slope=1;
 slope2=-1;
 wait=300;
 }



 
 for(;v<ma;)
 {
  v=t*slope;
  for (int i=0; i<number4strip;i++)
  {

    if(color==0){
      int g=v*0.2;
      int r=v;
      if(g==0){r=0;}
  strip_l.setPixelColor(i,r,g,0 );
  
  strip_r.setPixelColor(i,r,g,0 );
    }
  if(color==1){
  strip_l.setPixelColor(i,0,v,0 );
  
  strip_r.setPixelColor(i,0,v,0 );
    }
  }
  strip_l.show();
  
  strip_r.show();
  t++;
  delay(10);
  }
  
  
  t=0;
  temp=v;
  for(;v>(temp-radius);)
  {
    v=temp-radius*sin(w*t);
    for (int i=0; i<number4strip;i++)
  { if(color==0){
      int g=v*0.2;
      int r=v;
      if(g==0){r=0;}
  strip_l.setPixelColor(i,r,g,0 );
  
  strip_r.setPixelColor(i,r,g,0 );
    }
  if(color==1){
  strip_l.setPixelColor(i,0,v,0 );
  
  strip_r.setPixelColor(i,0,v,0 );
    }
  }
  strip_l.show();
  
  strip_r.show();
  t++;
  delay(10);
    }

  t=0;
  temp=v;
  for(;v>0;)
  {
    v=temp+slope2*t;
     for (int i=0; i<number4strip;i++)
  { if(color==0){
      int g=v*0.2;
      int r=v;
      if(g==0){r=0;}
  strip_l.setPixelColor(i,r,g,0 );
  
  strip_r.setPixelColor(i,r,g,0 );
    }
  if(color==1){
  strip_l.setPixelColor(i,0,v,0 );
  
  strip_r.setPixelColor(i,0,v,0 );
    }
  }
  strip_l.show();
  
  strip_r.show();
  t++;
  delay(10);
    
    }

delay(wait);

}


void forward(int pace, int number, int mode) {

  int ma=180;
  int wait;
  int gap=ma/number;
  int mid=(number/2)+1;
  
  for(int i=0;i<number4strip;i++)
{
  
  strip_l.setPixelColor(i, 0,0,0 );
  
  strip_r.setPixelColor(i, 0,0,0 );
 
  }

  strip_l.show();
  
  strip_r.show();
if (pace==0) {wait=50;}


if (pace==1) {wait=100;}

if (pace==2) {wait=200;}


for(int t=(1-mid);t<(number4strip+mid);t++)
{
  for(int i=0;i<(1+(number/2));i++)
  {
  strip_r.setPixelColor((t+i), 0,0,(ma-i*gap) );
  
  strip_r.setPixelColor((t-i), 0,0,(ma-i*gap ));

  
  strip_l.setPixelColor((t+i), 0,0,(ma-i*gap) );
  
  strip_l.setPixelColor((t-i), 0,0,(ma-i*gap ));
  }

  
  strip_l.setPixelColor(t-(1+(number/2)), 0,0,0);
  strip_r.setPixelColor(t-(1+(number/2)), 0,0,0);
  if(mode==0){
  strip_l.show();
  strip_r.show();
  }
  else if(mode==1){
  strip_l.show();
  }
  else if(mode==2){
  
  strip_r.show();
  }
  
  
  
  delay(wait);
}



  
}


void blibli(int color) {

  int wait;
  if(color==0){wait=300;}
  else{wait=100;}

  int v=180;
  for(int r=0;r<5;r++){
  
for(int i=0;i<number4strip;i++)
  {

    if(color==0){
    strip_l.setPixelColor(i,v,v,0 );
    
    strip_r.setPixelColor(i,v,v,0 );
    }

    if(color==1){
    strip_l.setPixelColor(i,v,0,0 );
    
    strip_r.setPixelColor(i,v,0,0 );
    }

    if(color==2){
    strip_l.setPixelColor(i,v,0,v );
    
    strip_r.setPixelColor(i,v,0,v );
    }
    
    }
    
  strip_l.show();
  
  strip_r.show();


delay(wait);
for(int i=0;i<number4strip;i++)
  {

    strip_l.setPixelColor(i,0,0,0 );
   
    strip_r.setPixelColor(i,0,0,0 );
    
    }
    
  strip_l.show();
  
  strip_r.show();


delay(wait);
  }
}



void backward(int pace, int number, int mode) {

  int ma=180;
  int wait;
  int gap=ma/number;
  int mid=(number/2)+1;
  
  for(int i=0;i<number4strip;i++)
{
  
  strip_l.setPixelColor(i, 0,0,0 );
  
  strip_r.setPixelColor(i, 0,0,0 );
 
  }

  strip_l.show();
  
  strip_r.show();
if (pace==0) {wait=50;}


if (pace==1) {wait=100;}

if (pace==2) {wait=200;}


for( int t=(number4strip+mid-1);t>(0-mid);t--)
{
  for(int i=0;i<(1+(number/2));i++)
  {
  strip_r.setPixelColor((t+i), 0,0,(ma-i*gap) );
  
  strip_r.setPixelColor((t-i), 0,0,(ma-i*gap ));

  
  strip_l.setPixelColor((t+i), 0,0,(ma-i*gap) );
  
  strip_l.setPixelColor((t-i), 0,0,(ma-i*gap ));
  }

  
  strip_l.setPixelColor(t+(1+(number/2)), 0,0,0);
  strip_r.setPixelColor(t+(1+(number/2)), 0,0,0);
  if(mode==0){
  strip_l.show();
  strip_r.show();
  }
  else if(mode==1){
  strip_l.show();
  }
  else if(mode==2){
  
  strip_r.show();
  }
  
  
  
  delay(wait);
}
strip_l.setPixelColor(0, 0,0,0);
  strip_r.setPixelColor(0, 0,0,0);
  if(mode==0){
  strip_l.show();
  strip_r.show();
  }
  else if(mode==1){
  strip_l.show();
  }
  else if(mode==2){
  
  strip_r.show();
  }
  
  
  
  delay(wait);


}
