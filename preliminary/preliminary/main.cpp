//
//  main.cpp
//  preliminary
//
//  Created by Sujal Dhungana on 9/03/2015.
//  Copyright (c) 2015 Sujal Dhungana. All rights reserved.
//

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"
#include <iostream>
#include "iomanip"
#include "fstream"

using namespace std;

const int SCREEN_WIDTH = 675;
const int SCREEN_HEIGHT = 675;

class LTexture
{
public:
    int x,gotired1x=430;
    int y,gotired1y=140;
    int pareko;
    bool stop = false ;
    //Initializes variables
    LTexture();
    
    //Deallocates memory
    ~LTexture();
    
    //Loads image at specified path
    bool loadFromFile( std::string path );
    
    //Deallocates texture
    void free();
    
    //Renders texture at given point
    void render( int x, int y );
    void movedice();
    bool stopdice();
    void tiltdice();
    int stilldice(int x1);
    int paryo();
    //Gets image dimensions
    int getWidth();
    int getHeight();
    
    friend class coordinate;
private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    
    
    //Image dimensions
    int mWidth;
    int mHeight;
};

class coordinate
{
public:
    int x,y;
    int pareko;
    
    coordinate():x(0),y(0){}
    coordinate(int n,int p,int h): x(n),y(p),pareko(h){}
    int getx()
    {
        return x;
    }
    int gety()
    {
        return  y;
    }
    void han()
    {
    }
    coordinate move(int pr)
    {
        pareko = pr;
        int z= x+pareko*15;
        int w = y+pareko*15;
        coordinate temp =  coordinate (z,w,pareko);
        return  temp;
    }
    coordinate settointial()
    {
        coordinate temp(135,410,pareko);
        return temp;
    }
    void display()
    {
        cout << x << "," << y << "  pareko: "<<pareko<<endl;
    }
};


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture dice,gotired1,gotired2,gotired3,gotired4;
LTexture gBackgroundTexture;

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile( std::string path )
{
    //Get rid of preexisting texture
    free();
    
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}



void LTexture::render( int x, int y )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}


int LTexture::getWidth()
{
    return mWidth;
}


int LTexture::getHeight()
{
    return mHeight;
}


bool init()
{
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        
        //Create window
        gWindow = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    
    return success;
}


bool loadMedia()
{
    //Loading success flag
    bool success = true;
    if( !dice.loadFromFile( "foo5.png"))
    {
        printf( "Failed to load Foo' texture image!\n" );
        success = false;
    }
    //load gotired1 texture.
    if( !gotired1.loadFromFile( "gotir.png" ) )
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }
    if( !gotired2.loadFromFile( "gotir.png" ) )
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }
    if( !gotired3.loadFromFile( "gotir.png" ) )
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }
    if( !gotired4.loadFromFile( "gotir.png" ) )
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }

    return success;
}

void close()
{
    //Free loaded images
    dice.free();
    gBackgroundTexture.free();
    
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void LTexture::movedice()
{
    x= rand()%300;
    SDL_Delay(10);
    y= rand()%300;
    SDL_Delay(10);
    
}
bool LTexture::stopdice()
{
    ofstream outfile("pareko.TXT");
    outfile<<dice.pareko;
    outfile.close();

    return stop;
}

void LTexture::tiltdice()
{
    int v1;
    v1= rand()%7;
    
    switch (v1) {
        case 1:
            SDL_Delay(10);
            dice.loadFromFile( "bin/tilts/tilt1.png");
            break;
        case 2:
            SDL_Delay(10);
            dice.loadFromFile( "bin/tilts/tilt2.png");
            break;
        case 3:
            SDL_Delay(10);
            dice.loadFromFile( "bin/tilts/tilt4.png");
            break;
        case 4:
            SDL_Delay(10);
            dice.loadFromFile( "bin/tilts/tilt3.png");
            break;
        case 5:
            SDL_Delay(10);
            dice.loadFromFile( "bin/tilts/tilt5.png");
            break;
        case 6:
            SDL_Delay(10);
            dice.loadFromFile( "bin/tilts/tilt4.png");
            break;
            
        default:
            break;
    }

}

int LTexture::paryo()
{
    if (!stop) {
        int v1 = rand()%7;
        pareko = v1;
    }
    return pareko;
}

int LTexture:: stilldice(int x2)
{
        switch (x2) {
        case 0:
            dice.loadFromFile( "bin/stills/foo4.png");
            SDL_Delay(10);
                pareko = 4;
            break;
        case 1:
            dice.loadFromFile( "bin/stills/foo1.png");
            SDL_Delay(10);
            break;
        case 2:
            dice.loadFromFile( "bin/stills/foo2.png");
            SDL_Delay(10);
            break;
        case 3:
            dice.loadFromFile( "bin/stills/foo3.png");
            SDL_Delay(10);
            break;
        case 4:
            dice.loadFromFile( "bin/stills/foo4.png");
            SDL_Delay(10);
            break;
        case 5:
            dice.loadFromFile( "bin/stills/foo5.png");
            SDL_Delay(10);
            break;
        case 6:
            dice.loadFromFile( "bin/stills/foo6.png");
            SDL_Delay(10);
            break;
    }
    return pareko;
}


int main( int argc, char* args[] )
{
    
    
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;
            
            //Event handler
            SDL_Event e;
            
            //While application is running
            gotired1.x = gotired2.x = gotired3.x = gotired4.x = 398;
            gotired1.y = gotired2.y = gotired3.y = gotired4.y= 125;
            bool niskyo = false;
            bool vayo = false;
            bool  pugyo =  false;
            bool ghum = false;
            bool ferighum = false;
            bool ferighumcon = false;
            bool feriferighumcon = false;
            bool xiryo = false;
            bool sakkyo = false;
            bool turn = false;
            bool ferighum1 = false;
            bool ferighum2 = false;
            bool ferighum3 = false;
            bool ferighum4 = false;
            bool ferighum5 = false;
            bool ferighum6 = false;
            bool ferighum7 = false;
            int count=0;
            int count1 = 0;
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                }
                //drawing //
                {
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear( gRenderer );
                //green mid
                SDL_Rect fillRect11 = {45,315,225,45};
                SDL_SetRenderDrawColor(gRenderer, 0x00,0xFF,0x00,0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect11);
                //green start
                SDL_Rect fillRect12 = {45,270,45,45};
                SDL_SetRenderDrawColor(gRenderer, 0x00,0xFF,0x00,0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect12);
                //green safe
                SDL_Rect fillRect13 = {270,90,45,45};
                SDL_SetRenderDrawColor(gRenderer, 0x00,0xFF,0x00,0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect13);
                
                //red mid//
                SDL_Rect fillRect21 = {315,45,45,225};
                SDL_SetRenderDrawColor(gRenderer, 0xFF,0x00,0x00,0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect21);
                
                //red start
                SDL_Rect fillRect22 = {360,45,45,45};
                SDL_SetRenderDrawColor(gRenderer, 0xFF,0x00,0x00,0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect22);
                //red safe
                SDL_Rect fillRect23 = {540,270,45,45};
                SDL_SetRenderDrawColor(gRenderer, 0xFF,0x00,0x00,0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect23);
                
                
                //yellow mid
                SDL_Rect fillRect31 = {315,405,45,225};
                SDL_SetRenderDrawColor(gRenderer, 0xFF,0xFF,0x00,0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect31);
                //yellow start//
                SDL_Rect fillRect32 = {270,585,45,45};
                SDL_SetRenderDrawColor(gRenderer, 0xFF,0xFF,0x00,0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect32);
                //yellow safe
                SDL_Rect fillRect33 = {90,360,45,45};
                SDL_SetRenderDrawColor(gRenderer, 0xFF,0xFF,0x00,0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect33);
                
                
                //blue mid//
                SDL_Rect fillRect41 = {405,315,225,45};
                SDL_SetRenderDrawColor(gRenderer, 0x00,0x00,0xFF,0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect41);
                //blue start//
                SDL_Rect fillRect42 = {585,360,45,45};
                SDL_SetRenderDrawColor(gRenderer, 0x00,0x00,0xFF,0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect42);
                //blue safe//
                SDL_Rect fillRect43 = {360,540,45,45};
                SDL_SetRenderDrawColor(gRenderer, 0x00,0x00,0xFF,0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect43);
                
                //partition lines//
                for (int a=0;a<SCREEN_WIDTH;) {
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00);
                    SDL_RenderDrawLine( gRenderer,0, a, SCREEN_WIDTH, a);
                    a=a+45;
                }
                for (int a=0;a<SCREEN_WIDTH;) {
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00,0x00);
                    SDL_RenderDrawLine( gRenderer,a,0,a,SCREEN_WIDTH);
                    a=a+45;
                }
                
                //green home//
                SDL_Rect fillRect1 = {0,0,270,270};
                SDL_SetRenderDrawColor(gRenderer, 0x00,0xFF,0x00,0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect1);
                
                //Red home//
                SDL_Rect fillRect2 = {406,0,675,270};
                SDL_SetRenderDrawColor(gRenderer, 0xFF,0x00,0x00,0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect2);
                
                //Yellow home//
                SDL_Rect fillRect3 = {0,406,270,675};
                SDL_SetRenderDrawColor(gRenderer, 0xFF,0xFF,0x00,0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect3);
                
                //Blue home/
                SDL_Rect fillRect4 = {406,406,675,675};
                SDL_SetRenderDrawColor(gRenderer, 0x00,0x00,0xFF,0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect4);
                //green traingle
                int y1=337;
                int z1=0;
                for (int x=269;x<=337;x++) {
                    
                    SDL_Rect fillRect14 = {x,y1,1,68-z1};
                    SDL_SetRenderDrawColor(gRenderer, 0x00,0xFF,0x00,0xFF);
                    SDL_RenderFillRect(gRenderer, &fillRect14);
                    z1++;
                }
                int x11=269;
                int z11=0;
                for (int y11=270;y11<=337;y11++) {
                    
                    SDL_Rect fillRect14 = {x11,y11,z11,1};
                    SDL_SetRenderDrawColor(gRenderer, 0x00,0xFF,0x00,0xFF);
                    SDL_RenderFillRect(gRenderer, &fillRect14);
                    z11++;
                }
                
                
                //RED traingle//
                int y2=270;
                int z2=0;
                for (int x=337;x<=405;x++) {
                    
                    SDL_Rect fillRect14 = {x,y2,1,68-z2};
                    SDL_SetRenderDrawColor(gRenderer, 0xFF,0x00,0x00,0xFF);
                    SDL_RenderFillRect(gRenderer, &fillRect14);
                    z2++;
                }
                int y22=270;
                int z22=0;
                for (int x22=270;x22<=337;x22++) {
                    
                    SDL_Rect fillRect14 = {x22,y22,1,z22};
                    SDL_SetRenderDrawColor(gRenderer, 0xFF,0x00,0x00,0xFF);
                    SDL_RenderFillRect(gRenderer, &fillRect14);
                    z22++;
                }
                //blue traingle
                int y41=338;
                int z41=0;
                for (int x41=337;x41<=405;x41++) {
                    
                    SDL_Rect fillRect14 = {x41,y41--,1,z41};
                    SDL_SetRenderDrawColor(gRenderer, 0x00,0x00,0xFF,0xFF);
                    SDL_RenderFillRect(gRenderer, &fillRect14);
                    z41++;
                }
                int y42=337;
                int z42=0;
                for (int x42=337;x42<=405;x42++) {
                    
                    SDL_Rect fillRect14 = {x42,y42,1,z42};
                    SDL_SetRenderDrawColor(gRenderer, 0x00,0x00,0xFF,0xFF);
                    SDL_RenderFillRect(gRenderer, &fillRect14);
                    z42++;
                }
                
                
                
                //Yellow traingle//
                int x31=336;
                int z31=0;
                for (int y31=337;y31<=406;y31++) {
                    
                    SDL_Rect fillRect14 = {x31,y31,z31,1};
                    SDL_SetRenderDrawColor(gRenderer, 0xFF,0xFF,0x00,0xFF);
                    SDL_RenderFillRect(gRenderer, &fillRect14);
                    z31++;
                }
                int y32=406;
                int z32=0;
                for (int x32=270;x32<=337;x32++) {
                    
                    SDL_Rect fillRect14 = {x32,y32--,1,z32};
                    SDL_SetRenderDrawColor(gRenderer, 0xFF,0xFF,0x00,0xFF);
                    SDL_RenderFillRect(gRenderer, &fillRect14);
                    z32++;
                }
                //midle cross//
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00,0x00);
                SDL_RenderDrawLine( gRenderer, 270,270,405,405);
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00,0x00);
                SDL_RenderDrawLine( gRenderer,405,270,270,405);
                
                //coin homes
                //Green outline
                SDL_Rect inlineRect1 = { 50, 50 ,170, 170 };
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderDrawRect( gRenderer, &inlineRect1 );
                for (int i=0;i<=2;) {
                    SDL_Rect inlineRect1_1 = { i*34+84, 84 ,34, 34 };
                    SDL_Rect inlineRect1_2 = { i*34+84,152,34,34 };
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00);
                    SDL_RenderDrawRect( gRenderer, &inlineRect1_1 );
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00);
                    SDL_RenderDrawRect( gRenderer, &inlineRect1_2 );
                    i++;
                    i++;
                }
                //Red outline
                SDL_Rect inlineRect2 = { 455, 50 ,170, 170 };
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderDrawRect( gRenderer, &inlineRect2 );
                for (int i=0;i<=2;) {
                    SDL_Rect inlineRect1_1 = { i*34+84+405, 84 ,34, 34 };
                    SDL_Rect inlineRect1_2 = { i*34+84+405,152,34,34 };
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00);
                    SDL_RenderDrawRect( gRenderer, &inlineRect1_1 );
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00);
                    SDL_RenderDrawRect( gRenderer, &inlineRect1_2 );
                    i++;
                    i++;
                }
                
                //Yellow outline
                SDL_Rect inlineRect3 = { 50,455,170, 170 };
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderDrawRect( gRenderer, &inlineRect3 );
                for (int i=0;i<=2;) {
                    SDL_Rect inlineRect1_1 = { i*34+84, 84+405 ,34, 34 };
                    SDL_Rect inlineRect1_2 = { i*34+84,152+405,34,34 };
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00);
                    SDL_RenderDrawRect( gRenderer, &inlineRect1_1 );
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00);
                    SDL_RenderDrawRect( gRenderer, &inlineRect1_2 );
                    i++;
                    i++;
                }
                //Blue outline
                SDL_Rect inlineRect4 = { 455, 455 ,170, 170 };
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderDrawRect( gRenderer, &inlineRect4 );
                for (int i=0;i<=2;) {
                    SDL_Rect inlineRect1_1 = { i*34+84+405, 84+405 ,34, 34 };
                    SDL_Rect inlineRect1_2 = { i*34+84+405,152+405,34,34 };
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00);
                    SDL_RenderDrawRect( gRenderer, &inlineRect1_1 );
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00);
                    SDL_RenderDrawRect( gRenderer, &inlineRect1_2 );
                    i++;
                    i++;
                }
                //Boundary
                SDL_Rect outlineRect = {0,0, SCREEN_WIDTH,SCREEN_HEIGHT};
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00);
                    SDL_RenderDrawRect( gRenderer, &outlineRect );
                }
                coordinate c1;
                dice.render( dice.x,dice.y);
                gotired1.render(gotired1.x,gotired1.y);
                gotired2.render(gotired2.x+70,gotired2.y);
                gotired3.render(gotired3.x,gotired3.y-70);
                gotired4.render(gotired4.x+70,gotired4.y-70);
                switch (e.type) {
                    case SDL_MOUSEBUTTONDOWN:
                        switch (e.button.button) {
                            case SDL_BUTTON_LEFT:
                                dice.movedice();
                                dice.tiltdice();
                                break;
                            default:
                                break;
                        }
                        break;
                    case SDL_MOUSEBUTTONUP:
                        switch (e.button.button) {
                            case SDL_BUTTON_LEFT:
                                 dice.paryo();
                                 dice.stilldice(dice.pareko);
                                cout<<" k paryo? "<<endl<<dice.pareko<<endl;
                                SDL_Delay(250);
                                dice.stopdice();
                                count++;
                            {
                                if (dice.pareko != 1) {
                                    niskyo = true;
                                    count1 = count - 1;

                                }
                                else count1++;
                                
                                if ((count-count1)>=1) {
                                    if (gotired1.x == 398 && gotired1.y ==125 ) {
                                        gotired1.x = 275;
                                        gotired1.y = 25;
                                    }
                                   else
                                   {
                                      if(!xiryo) {
                                       if (gotired1.y<=205 && gotired1.x==275) {
                                           gotired1.y = gotired1.y+dice.pareko*45;
                                           gotired1.x = 275;
                                       }
                                       if (gotired1.y>205 &&gotired1.x ==275 && !ferighumcon ) {
                                           gotired1.x = gotired1.x+gotired1.y-205;
                                           gotired1.y = 250;
                                           vayo = true;
                                       }
                                       else vayo = false;
                                       if (gotired1.y==250 && gotired1.x>275 && !feriferighumcon) {
                                           gotired1.y = 250;
                                           if (vayo) {
                                               gotired1.x = gotired1.x;
                                           }
                                           else gotired1.x = gotired1.x + dice.pareko*45;
                                       }
                                      if (gotired1.y == 250 && gotired1.x>=545 && !feriferighumcon) {
                                          gotired1.y = gotired1.y + gotired1.x - 545;
                                          gotired1.x = 545;
                                          pugyo = true;
                                       }
                                       else pugyo = false;
                                       if (gotired1.y >=250 && gotired1.x ==545 && !feriferighumcon) {
                                           if (pugyo) {
                                               gotired1.y = gotired1.y;
                                           }
                                           else
                                               gotired1.y = gotired1.y+dice.pareko*45;
                                           
                                       }
                                       if (gotired1.y >=340 && gotired1.x==545) {
                                           gotired1.x = gotired1.x-(gotired1.y-340);
                                           gotired1.y = 340;
                                           ghum = true;
                                       }
                                       else ghum = false;
                                       if (gotired1.y==340 && gotired1.x <=545 &&!ferighumcon) {
                                           if (ghum) {
                                               gotired1.x = gotired1.x;
                                           }
                                           else
                                               gotired1.x = gotired1.x - 45*dice.pareko;
                                           
                                       }
                                       if (gotired1.x <= 275 && gotired1.y ==340 &&!ferighumcon) {
                                           gotired1.y = gotired1.y+45-(gotired1.x-275);
                                           gotired1.x = 275;
                                           ferighum = true;
                                           ferighumcon = true;
                                       }
                                       else ferighum = false;
                                       if (gotired1.x ==275 && gotired1.y >=340 && ferighumcon && gotired1.y<=610) {
                                           if (ferighum) {
                                               gotired1.y = gotired1.y;
                                           }
                                           else{
                                               gotired1.y = gotired1.y+dice.pareko*45;
                                               gotired1.x = 275;
                                           }
                                       }
                                       if (gotired1.x ==275 && gotired1.y>=610) {
                                           gotired1.x = 275 - (gotired1.y-610);
                                           gotired1.y = 610;
                                           turn = true;
                                       }
                                       else turn = false;
                                       if (gotired1.x<=275 && gotired1.y==610 && ferighumcon) {
                                           if (turn) {
                                               gotired1.x = gotired1.x;
                                           }
                                           else
                                               gotired1.x =gotired1.x - 45*dice.pareko;
                                       }
                                       
                                       if (gotired1.x<=185 && gotired1.y == 610 && ferighumcon && !feriferighumcon) {
                                           gotired1.y = gotired1.y - (185-gotired1.x);
                                           gotired1.x = 185;
                                           ferighum1 = true;
                                       }
                                       else ferighum1 = false;
                                       
                                       if (gotired1.x==185 && gotired1.y <=610 && !feriferighumcon ) {
                                           if (ferighum1) {
                                               gotired1.y = gotired1.y;
                                           }
                                           else
                                               gotired1.y = gotired1.y-45*dice.pareko;
                                       }
                                       
                                       if (gotired1.x == 185 && gotired1.y<385 &&!feriferighumcon ) {
                                           gotired1.x = gotired1.x-(385-gotired1.y);
                                           gotired1.y = 340;
                                           ferighum2 = true;
                                       }
                                       else ferighum2 = false;
                                       if (gotired1.x<185 && gotired1.y==340 &&ferighumcon ) {
                                           if (ferighum2) {
                                               gotired1.x = gotired1.x;
                                           }
                                           else
                                         gotired1.x = gotired1.x-45*dice.pareko;
                                           gotired1.y = 340;
                                       }
                                       
                                       if (gotired1.x<=-85 && gotired1.y ==340 &&ferighumcon) {
                                           gotired1.y = gotired1.y -(-85-gotired1.x);
                                           gotired1.x = -85;
                                           ferighum3 = true;
                                       }
                                       else ferighum3 = false;
                                       if (gotired1.x ==-85 && gotired1.y<=340 && ferighumcon &&!feriferighumcon) {
                                           if (ferighum3) {
                                               gotired1.y = gotired1.y;
                                           }
                                           else
                                               gotired1.y = gotired1.y - 45*dice.pareko;
                                       }
                                       
                                       if (gotired1.x == -85 && gotired1.y <=250 &&!feriferighumcon) {
                                           gotired1.x = gotired1.x-(gotired1.y-250);
                                           gotired1.y = 250;
                                           ferighum4 = true;
                                           feriferighumcon = true;
                                       }
                                       else ferighum4 = false;
                                       
                                       if (gotired1.x >=-85 && gotired1.y==250 && feriferighumcon) {
                                           if (ferighum4) {
                                               gotired1.x = gotired1.x;
                                           }
                                           else
                                               gotired1.x = gotired1.x +45*dice.pareko;
                                           gotired1.y = 250;
                                       }
                                       if (gotired1.x >=140 && gotired1.y==250 && feriferighumcon) {
                                           gotired1.y = gotired1.y - (gotired1.x-140);
                                           gotired1.x = 185;
                                           ferighum5 = true;
                                           feriferighumcon = true;
                                       }
                                       else ferighum5 = false;
                                       if (gotired1.x ==185 && gotired1.y <=250 &&feriferighumcon) {
                                           if (ferighum5) {
                                               gotired1.y = gotired1.y;
                                           }
                                           else
                                               gotired1.y = gotired1.y-45*dice.pareko;
                                           gotired1.x = 185;
                                       }
                                       if (gotired1.x ==185 && gotired1.y <=-20 &&feriferighumcon) {
                                           gotired1.x = gotired1.x +(-20-gotired1.y);
                                           ferighum6 = true;
                                           gotired1.y= -20;
                                       }
                                       else ferighum6 = false;
                                       if (gotired1.x >185 && gotired1.y==-20) {
                                           if (ferighum6) {
                                               gotired1.x = gotired1.x;
                                           }
                                           else
                                               gotired1.x = gotired1.x+dice.pareko*45;
                                           gotired1.y = -20;
                                       }
                                       if (gotired1.x >=230 && gotired1.y ==-20 ) {
                                           gotired1.y = gotired1.y +(gotired1.x -230);
                                           gotired1.x = 230;
                                           ferighum7 = true;
                                           xiryo = true;
                                       }
                                       else ferighum7 = false;
                                       }
                                       
                                       if(!sakkyo){
                                       if (xiryo) {
                                           cout<<"xiryo"<<endl;
                                           int chaiyeko = (250-gotired1.y)/45;
                                           if(ferighum7){
                                               gotired1.y = gotired1.y;
                                               ferighum7 = false;
                                           }
                                           else
                                           {
                                               if (dice.pareko <= chaiyeko) {
                                               cout<<"Sano"<<endl;
                                               gotired1.y = gotired1.y+dice.pareko*45;
                                               chaiyeko = chaiyeko- dice.pareko;
                                           }
                                           else cout<<"Thulo"<<endl;
                                           if (chaiyeko==0) {
                                               cout<<"Game"<<endl;
                                               gotired1.x = 545;
                                               gotired1.y = -20;
                                               sakkyo = true;
                                           }
                                           }
                                       }
                                   }
                                  
                                   }
                                       cout<<"x"<<gotired1.x<<endl;
                                        cout<<"y"<<gotired1.y<<endl;
                                       
                                       
                                   }
                                }
                            break;
                        }
                    default:
                        
                        break;
                }
                SDL_RenderPresent( gRenderer );
            }
        }
    }
    close();
    return 0;
}





