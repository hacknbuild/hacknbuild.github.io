#include <Adafruit_NeoPixel.h>
#define PIN       2
#define NUMPIXELS 12

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

// Returns the Red component of a 32-bit color
uint8_t Red(uint32_t color)
{
    return (color >> 16) & 0xFF;
}

// Returns the Green component of a 32-bit color
uint8_t Green(uint32_t color)
{
    return (color >> 8) & 0xFF;
}

// Returns the Blue component of a 32-bit color
uint8_t Blue(uint32_t color)
{
    return color & 0xFF;
} 

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pixels.begin(); 
}



const uint32_t white = pixels.Color(255,255,255);
const uint32_t red = pixels.Color(255,0,0);
const uint32_t yellow = pixels.Color(255,255,0);
const uint32_t orange = pixels.Color(255,155,0);
const uint32_t blue = pixels.Color(0,0,255);
const uint32_t green = pixels.Color(0,255,0);
const uint32_t magenta = pixels.Color(255,0,255);
const uint32_t black = pixels.Color(0,0,0);


const uint32_t c1 = pixels.Color(150, 0, 0);
const uint32_t c2 = pixels.Color(0, 150, 0);
const uint32_t c3 = pixels.Color(0, 0, 150);
const uint32_t c4 = pixels.Color(150, 0, 150);
const uint32_t c5 = pixels.Color(0, 150, 150);
const uint32_t c6 = pixels.Color(150,150,0);

const uint32_t colors[] = {c1,c2,c3,c4,c5,c6,
                           c1,c2,c3,c4,c5,c6};

const int numRows = 5;
const int numCols = 6;

const int pixelsByRow [5][6] =    {
                            {2,  -1, -1,   -1, -1, 8},
                            {-1,  1, -1,   -1,  7, -1},
                            {3,  -1,  0,   6,  -1, 9},
                            {-1,  5, -1,   -1, 11, -1},
                            {4,  -1, -1,  - 1, -1, 10}
                        };


const int pixelsByCol [3][6] = { {0,  6, -1,  -1, -1, -1},
                                {1,  5,  7,  11, -1, -1},
                                {2,  3,  4,   8, 9, 10}
                              };

void wipeBackToFront(uint32_t color)
{
   

   for (int r=0;r<numRows;r++)
   {
     for (int c=0;c<numCols;c++)
     {
       int pixelNum = pixelsByRow[r][c];
       pixels.setPixelColor(pixelNum,color);
     }
   }
}

void fade(uint32_t targetColor,uint pixel, float pct)
{
  
  int targetRed = Red(targetColor);
  int targetBlue = Blue(targetColor);
  int targetGreen = Green(targetColor);

  uint32_t currentColor = pixels.getPixelColor(pixel);
  int currentRed =  Red(currentColor);
  int currentBlue = Blue(currentColor);
  int currentGreen = Green(currentColor);

  float redToGo =  targetRed - currentRed;
  float blueToGo = targetBlue - currentBlue;
  float greenToGo = targetGreen - currentGreen;

  uint8_t newRed   =  (uint8_t) ( (float) currentRed +  (pct * redToGo) );
  uint8_t newGreen =  (uint8_t) ( (float) currentGreen +  (pct * greenToGo) );
  uint8_t newBlue  =  (uint8_t) ( (float) newBlue +  (pct * blueToGo) ); 

  //pixels.setPixelColor(pixel, pixels.Color(newRed,newGreen,newBlue)); 
  //pixels.setPixelColor(pixel, targetColor); 
  pixels.setPixelColor(pixel, pixels.Color(newRed,newGreen,newBlue)); 
    
}

void fade(uint32_t targetColor,uint pixel,float pct, float brightness )
{
  fade(targetColor,pixel,pct);
  uint32_t currentColor = pixels.getPixelColor(pixel);

  int currentRed =  Red(currentColor);
  int currentGreen = Green(currentColor);
  int currentBlue = Blue(currentColor);

  int whiteLevel = (int) (255.0 * brightness);

    pixels.setPixelColor(pixel, pixels.Color(currentRed,currentGreen,currentBlue,whiteLevel)); 

}
void randomize(int duration)
{
  float dutyCycle = 500.0;

  for (uint i=0;i<duration;i+=dutyCycle)
  {
     int pixel = random(0,NUMPIXELS-1);
     int colorIndex = random(1,11);

    uint32_t color;


    if (colorIndex==1) color=red; 
    if (colorIndex==2) color= pixels.Color(255,255,255,127); ;
    if (colorIndex==3) color=orange;
    if (colorIndex==4) color= yellow;
    if (colorIndex==5) color=pixels.Color(255,0,0,127); // half red
    if (colorIndex==6) color=pixels.Color(255,255,255,120);

    if (colorIndex==7) color=pixels.Color(255,0,0,100); 
    if (colorIndex==8) color=pixels.Color(255,255,255,100); 
    if (colorIndex==9) color=pixels.Color(255,255,0,100); //yellow
    if (colorIndex==10) color=pixels.Color(255,0,0,50); //red 
    if (colorIndex==11) color=pixels.Color(255,255,0,200); //red 


    for (int j=0;j<dutyCycle;j+=1)
    {
      float pct=0;
       if (j>0) pct = ( (float) j/  dutyCycle );
       //pixels.setPixelColor(pixel,color);
       fade(color,pixel,pct );
       delay(1);
       pixels.show();
    }

  }
}

void randomize2(int duration)
{
  float dutyCycle = 200.0;

  for (uint i=0;i<duration;i+=dutyCycle)
  {
     int pixel = random(0,NUMPIXELS-1);
     int colorIndex = random(1,6);

    uint32_t color;


    if (colorIndex==1) color=pixels.Color(200,200,200); 
    if (colorIndex==2) color= pixels.Color(128,128,128);
    if (colorIndex==3) color=pixels.Color(75, 0,0);
    if (colorIndex==3) color=pixels.Color(50,25,25,20);    
    if (colorIndex==5) color= 0;
    if (colorIndex==6) color= 0;


    for (int j=0;j<dutyCycle;j+=1)
    {
      float pct=0;
       if (j>0) pct = ( (float) j/  dutyCycle );
       //pixels.setPixelColor(pixel,color);
       if (color>0)
       {
        fade(color,pixel,pct );
       }
       else 
        pixels.setPixelColor(pixel,color);

       delay(1);
       pixels.show();
    }

  }
}

void crawlDown(uint32_t targetColor, int duration)
{

  float rowCycle = (float) duration / numRows;
  float updateAmount = rowCycle/10.0;
  float complete = 0.0;
  const int NUMCOLS=3;  
  const int NUMROWS=6;

   for (int c=0;c<NUMCOLS;c++)
   {
     for (int r=0;r<NUMROWS;r++)
     {
          int pixelNum = pixelsByRow[c][r];

          if (pixelNum>=0)
          {
            fade(targetColor, pixelNum, 1.0f);
          }
     }
     pixels.show();
     delay((long) rowCycle);
    
    
   }

   
}

void fill(uint32_t targetColor, int duration)
{
  for (int i=0;i<duration;i+=10)
  {
     float pct = 0;
     if (i>0) pct = (float) i / (float) duration;

     for(int j=0; j<NUMPIXELS; j++) {
       fade(targetColor,j,pct);
     }
    pixels.show(); 
    delay(10);
  }
}

void fadeIn(uint32_t targetColor, int duration)
{
  for (int i=0;i<duration;i+=10)
  {
     float pct = 0;
     if (i>0) pct = (float) i / (float) duration;

     for(int j=0; j<NUMPIXELS; j++) {
       fade(targetColor,j,1.0,pct);
     }
    pixels.show(); 
    delay(10);
  }
}

void fadeOut(uint32_t targetColor, int duration)
{
  for (int i=0;i<duration;i+=10)
  {
     float pct = 0;
     if (i>0) pct = (float) i / (float) duration;

     pct = 1 - pct;

     for(int j=0; j<NUMPIXELS; j++) {
       fade(targetColor,j,1.0,pct);
     }
    pixels.show(); 
    delay(10);
  }
}

void crawl(uint32_t targetColor, int duration)
{
  const int STRIP_LENGTH = 6;


  float dutyCycle = ( (float) duration/ (float) STRIP_LENGTH );
  
  for (uint i=0;i<STRIP_LENGTH;i++)
  {
    for(uint j=0;j<dutyCycle;j+=10)
    {
     float pct = 0.0;
     if (j>0) pct = ( (float) j/  dutyCycle );

     fade(targetColor,i, pct);
     fade(targetColor,i+6, pct);
     delay(10);
     pixels.show();   

    } 
  }

   
}

void crawlReverse(uint32_t targetColor, int duration)
{
  const int STRIP_LENGTH = 6;


  float dutyCycle = ( (float) duration/ (float) STRIP_LENGTH );
  int led1 = 5;
  int led2= 11;

  for (uint i=0;i<STRIP_LENGTH;i++)
  {
    for(uint j=0;j<dutyCycle;j+=10)
    {
     float pct = 0.0;
     if (j>0) pct = ( (float) j/  dutyCycle );

     fade(targetColor,led1, pct);
     fade(targetColor,led2, pct);
     delay(10);
     pixels.show();   

    } 

    led1--;
    led2--;

  }

   
}

void testPattern()
{
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, colors[i]);
    pixels.show();
  }
}

void loop() {


  pixels.clear();
  pixels.setBrightness(50);

  fadeIn(white,3000);
  crawl(red, 3500);
  delay(1000);
  fadeOut(red,1000);
  crawlReverse(white, 3500);
  fadeOut(white,3000);
  randomize(15000);
 
    // //fill white
  fill(orange,3000);
  pixels.show();
  delay(2000);

  crawl(yellow, 3500);
  delay(50);
  crawlReverse(red, 3000);
  crawl(white, 2500);
  crawlReverse(red, 2000);
  crawl(yellow, 1000);
  crawlReverse(red, 500);
  crawl(white,250);
  crawlReverse(yellow,100);
  crawl(red,50);

  fadeIn(white,2000);

  randomize2(30000);
  randomize(15000);

  pixels.fill(0,0,0);
  pixels.show();
  delay(10000);

} 