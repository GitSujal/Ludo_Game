//
//  main.cpp
//  2nd stage
//
//  Created by Sujal Dhungana on 18/03/2015.
//  Copyright (c) 2015 Sujal Dhungana. All rights reserved.
//

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "SDL2_mixer/SDL_mixer.h"
#include <fstream>
#include <string>
#include "cmath"

using namespace std;

const int SCREEN_WIDTH = 675;
const int SCREEN_HEIGHT = 750;

class LTexture
{
public:
    int x,gotired1x=430;
    int y,gotired1y=140;
    int pareko;
    bool stop = false ;
    
    LTexture();
    
    ~LTexture();
    
    bool loadFromFile( std::string path );
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    SDL_Rect getrect();
    void free();
    
    void render( int x, int y );
    
    void movedice();
    
    bool stopdice();
    
    void tiltdice();
    
    int stilldice(int x1);
    
    int paryo();

    int getWidth();
    int getHeight();
    
    friend class coordinate;
    
    //bools and count for goti
    
    SDL_Texture* mTexture;
    SDL_Rect a;
    
    
    int mWidth;
    int mHeight;
    
};


Mix_Music *gMusic = NULL;
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;



class goticlass: public LTexture
{
 //bools and count for goti
public:
    bool niskyo = false;
    bool collidedx = false;
    bool collidedy = false;
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
    int initial_x,initial_y,start_x,start_y,xirne_x,xirne_y,game_x,game_y;
    void movegoti(int n,int p);
    bool checkCollision( SDL_Rect a, SDL_Rect b );
    
};

template <class T>             //function template
T abs(T n)
{
    return (n < 0) ? -n : n;
}

void goticlass:: movegoti(int n,int p)
{
    if (p==0) {
        feriferighumcon = true;
    }
    if (p==2) {
        ferighumcon = true;
    }
    int number = n;
    {
        if (number == 1) {
            niskyo = true;
            count1 = count - 1;
            
        }
        else count1++;
        
        if ((count-count1)>=1 || niskyo) {
            if (x == initial_x && y == initial_y ) {
                x = start_x;
                y = start_y;
            }
            else
            {
                if(!xiryo) {
                    if (y<=205 && x==275) {
                        y = y+number*45;
                        x = 275;
                    }
                    if (y>205 &&x ==275 && !ferighumcon ) {
                        x = x+y-205;
                        y = 250;
                        vayo = true;
                    }
                    else vayo = false;
                    if (y==250 && x>275 && !feriferighumcon) {
                        y = 250;
                        if (vayo) {
                            x = x;
                        }
                        else x = x + number*45;
                    }
                    if (y == 250 && x>=545 && !feriferighumcon) {
                        y = y + x - 545;
                        x = 545;
                        pugyo = true;
                    }
                    else pugyo = false;
                    if (y >=250 && x ==545 && !feriferighumcon) {
                        if (pugyo) {
                            y = y;
                        }
                        else
                            y = y+number*45;
                        
                    }
                    if (y >=340 && x==545) {
                        x = x-(y-340);
                        y = 340;
                        ghum = true;
                    }
                    else ghum = false;
                    if (y==340 && x <=545 &&!ferighumcon) {
                        if (ghum) {
                            x = x;
                        }
                        else
                            x = x - 45*number;
                        
                    }
                    if (x <= 275 && y ==340 && !ferighumcon) {
                        y = y+45-(x-275);
                        x = 275;
                        ferighum = true;
                        ferighumcon = false;
                    }
                    else ferighum = false;
                    
                    if (x ==275 && y >=340 && ferighumcon && y<=610) {
                        if (ferighum) {
                            y = y;
                        }
                        else{
                            y = y+number*45;
                            x = 275;
                        }
                    }
                    if (x ==275 && y>=610) {
                        x = 275 - (y-610);
                        y = 610;
                        turn = true;
                    }
                    else turn = false;
                    if (x<=275 && y==610 && ferighumcon) {
                        if (turn) {
                            x = x;
                        }
                        else
                            x =x - 45*number;
                    }
                    
                    if (x<=185 && y == 610 && ferighumcon && !feriferighumcon) {
                        y = y - (185-x);
                        x = 185;
                        ferighum1 = true;
                    }
                    else ferighum1 = false;
                    
                    if (x==185 && y <=610 && !feriferighumcon ) {
                        if (ferighum1) {
                            y = y;
                        }
                        else
                            y = y-45*number;
                    }
                    
                    if (x == 185 && y<385 &&!feriferighumcon ) {
                        x = x-(385-y);
                        y = 340;
                        ferighum2 = true;
                    }
                    else ferighum2 = false;
                    if (x<185 && y==340 &&ferighumcon ) {
                        if (ferighum2) {
                            x = x;
                        }
                        else
                            x = x-45*number;
                        y = 340;
                    }
                    
                    if (x<=-85 && y ==340 &&ferighumcon) {
                        y = y -(-85-x);
                        x = -85;
                        ferighum3 = true;
                    }
                    else ferighum3 = false;
                    if (x ==-85 && y<=340 && ferighumcon &&!feriferighumcon) {
                        if (ferighum3) {
                            y = y;
                        }
                        else
                            y = y - 45*number;
                    }
                    
                    if (x == -85 && y <=250 &&!feriferighumcon) {
                        x = x-(y-250);
                        y = 250;
                        ferighum4 = true;
                        feriferighumcon = true;
                    }
                    else ferighum4 = false;
                    
                    if (x >=-85 && y==250 && feriferighumcon) {
                        if (ferighum4) {
                            x = x;
                        }
                        else
                            x = x +45*number;
                        y = 250;
                    }
                    if (x >140 && y==250 && feriferighumcon) {
                        y = y - (x-140);
                        x = 185;
                        ferighum5 = true;
                        feriferighumcon = true;
                    }
                    else ferighum5 = false;
                    if (x ==185 && y <=250 &&feriferighumcon) {
                        if (ferighum5) {
                            y = y;
                        }
                        else
                            y = y-45*number;
                        x = 185;
                    }
                    if (x ==185 && y <=-20 &&feriferighumcon) {
                        x = x +(-20-y);
                        ferighum6 = true;
                        y= -20;
                    }
                    else ferighum6 = false;
                    if (x >185 && y==-20) {
                        if (ferighum6) {
                            x = x;
                        }
                        else
                            x = x+number*45;
                        y = -20;
                    }
                    if (y==-20 && x>=275) {
                        y = y+(x-275);
                        x = 275;
                    }

    
                    if (x >=xirne_x && y == xirne_y && p ==1 ) {
                        y = y +(x -xirne_x);
                        x = xirne_x;
                        ferighum7 = true;
                        xiryo = true;
                    }
                    if (x<=xirne_x && y== xirne_x && p==2 ) {
                        y = y- (xirne_x-x);
                        x= xirne_x;
                        ferighum7 = true;
                        xiryo = true;
                    }
                    if (x == xirne_x && y <= xirne_y && p ==1 ) {
                        x = x-(y -xirne_y);
                        y = xirne_y;
                        ferighum7 = true;
                        xiryo = true;
                    }
                    if (x==xirne_x && y>= xirne_y && p==3) {
                        x = x-(y-xirne_y);
                        y = xirne_y;
                        ferighum7 = true;
                        xiryo = true;
                    }
                    else ferighum7 = false;
                }
                
                if(!sakkyo){
                    if (xiryo) {
                        cout<<p<<" wala xiryo"<<endl;
                        if (p==1 || p ==2) {
                            
                            int chaiyeko = ((game_y-y)/45)-1;
                            chaiyeko = abs(chaiyeko);
                            if(ferighum7){
                                y = y;
                                ferighum7 = false;
                            }
                            else
                            {
                                if (number <= chaiyeko) {
                                    cout<<"Sano"<<endl;
                                    y = y-pow(-1,p)*number*45;
                                    chaiyeko = chaiyeko - number;
                                }
                                else cout<<"Thulo"<<endl;
                                if (chaiyeko==0) {
                                    cout<<"Game"<<endl;
                                    x = xirne_x;
                                    y = y+450*(p-1);
                                    sakkyo = true;
                                }
                            }
                        }
                        else
                        {
                            int chaiyeko = ((game_x-x)/45)-1;
                            chaiyeko = abs(chaiyeko);
                            if(ferighum7){
                                y = y;
                                ferighum7 = false;
                            }
                            else
                            {
                                if (number <= chaiyeko) {
                                    cout<<"Sano"<<endl;
                                    x = x+pow(-1,p)*number*45;
                                    chaiyeko = chaiyeko - number;
                                }
                                else cout<<"Thulo"<<endl;
                                if (chaiyeko==0) {
                                    cout<<"Game"<<endl;
                                    y = xirne_y;
                                    x = x+450*(p-1);
                                    sakkyo = true;
                                }
                            }
                            
                        }
                    }
                }
                
            }
            cout<<"x "<<x<<endl;
            cout<<"y "<<y<<endl;
            
        }
    }

}

bool  goticlass::checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    
    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}

class coordinate
{
public:
    int x,y,initial_x,initial_y,xirne_x,xirne_y,game_x,game_y;
    
    coordinate():x(0),y(0){}
    coordinate(int n,int p): x(n),y(p){}
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
    void display()
    {
        cout << x << "," << y <<endl;
    }
};

//texture objects //
LTexture gbackground,dice,writeover[9];
goticlass goti[4][4];
// coordinate goticor[3][3];


bool init();

bool loadMedia();

void close();

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

TTF_Font *gFont = NULL;




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


bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();
    
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    
    //Return success
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

SDL_Rect LTexture::getrect()
{
    SDL_Rect renderQuad = { x, y,45, 45};
    return renderQuad;
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
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
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
                
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
                
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
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
    if( !dice.loadFromFile( "defaultdice.png"))
    {
        printf( "Failed to default dice texture image!\n" );
        success = false;
    }
    //load gotired1 texture.
    if( !goti[0][0].loadFromFile( "goti/gotig.png" ) )
    {
        printf( "Failed to load gotig texture image!\n" );
        success = false;
    }
    if( !goti[0][1].loadFromFile( "goti/gotig.png" ) )
    {
        printf( "Failed to load gotirg texture image!\n" );
        success = false;
    }
    if( !goti[0][2].loadFromFile( "goti/gotig.png" ) )
    {
        printf( "Failed to load gotirg texture image!\n" );
        success = false;
    }
    if( !goti[0][3].loadFromFile( "goti/gotig.png" ) )
    {
        printf( "Failed to load gotir4 texture image!\n" );
        success = false;
    }
    if( !goti[1][0].loadFromFile( "goti/gotir.png" ) )
    {
        printf( "Failed to load gotir1 texture image!\n" );
        success = false;
    }
    if( !goti[1][1].loadFromFile( "goti/gotir.png" ) )
    {
        printf( "Failed to load gotir2 texture image!\n" );
        success = false;
    }
    if( !goti[1][2].loadFromFile( "goti/gotir.png" ) )
    {
        printf( "Failed to load gotir3 texture image!\n" );
        success = false;
    }
    if( !goti[1][3].loadFromFile( "goti/gotir.png" ) )
    {
        printf( "Failed to load gotir4 texture image!\n" );
        success = false;
    }
    if( !goti[2][0].loadFromFile( "goti/gotiy.png" ) )
    {
        printf( "Failed to load gotiy texture image!\n" );
        success = false;
    }
    if( !goti[2][1].loadFromFile( "goti/gotiy.png" ) )
    {
        printf( "Failed to load gotiy texture image!\n" );
        success = false;
    }
    if( !goti[2][2].loadFromFile( "goti/gotiy.png" ) )
    {
        printf( "Failed to load gotiy texture image!\n" );
        success = false;
    }
    if( !goti[2][3].loadFromFile( "goti/gotiy.png" ) )
    {
        printf( "Failed to load gotiy texture image!\n" );
        success = false;
    }
    if( !goti[3][0].loadFromFile( "goti/gotib.png" ) )
    {
        printf( "Failed to load gotib texture image!\n" );
        success = false;
    }
    if( !goti[3][1].loadFromFile( "goti/gotib.png" ) )
    {
        printf( "Failed to load gotib texture image!\n" );
        success = false;
    }
    if( !goti[3][2].loadFromFile( "goti/gotib.png" ) )
    {
        printf( "Failed to load gotib texture image!\n" );
        success = false;
    }
    if( !goti[3][3].loadFromFile( "goti/gotib.png" ) )
    {
        printf( "Failed to load gotib texture image!\n" );
        success = false;
    }
    gFont = TTF_OpenFont( "good.ttf", 45 );
    if( gFont == NULL )
    {
        printf( "Failed to load good font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    
    //Load music
    gMusic = Mix_LoadMUS( "beat.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    //Load sound effects
    gScratch = Mix_LoadWAV( "scratch.wav" );
    if( gScratch == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gHigh = Mix_LoadWAV( "gun.wav" );
    if( gHigh == NULL )
    {
        printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gMedium = Mix_LoadWAV( "medium.wav" );
    if( gMedium == NULL )
    {
        printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gLow = Mix_LoadWAV( "low.wav" );
    if( gLow == NULL )
    {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    
    return success;
}

void close()
{
    //Free loaded images
    dice.free();
    gbackground.free();
    //Free the sound effects
    Mix_FreeChunk( gScratch );
    Mix_FreeChunk( gHigh );
    Mix_FreeChunk( gMedium );
    Mix_FreeChunk( gLow );
    gScratch = NULL;
    gHigh = NULL;
    gMedium = NULL;
    gLow = NULL;
    
    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
    
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    TTF_CloseFont( gFont );
    gFont = NULL;
    
    
    //Quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void LTexture::movedice()
{
    x= rand()%550;
    SDL_Delay(5);
    y= rand()%75+600;
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

int checkcolor(int n,int p)
{
    int a=5,b=5;
    for (int i=0;i<=3;i++) {
        for (int j=0; j<=3;j++) {
            if (n <= goti[i][j].x+125  && n >= goti[i][j].x+90 &&                                                                                                 p <= goti[i][j].y+65 && p >= goti[i][j].y+25)
            {
                a-=(5-i);
                b-=(5-j);
            }
        }
    }
    return a;
}
int checknum(int n,int p)
{
    int a=5,b=5;
    for (int i=0;i<=3;i++) {
        for (int j=0; j<=3;j++) {
            if (n <= goti[i][j].x+125  && n >= goti[i][j].x+90 &&                                                                                                 p <= goti[i][j].y+65 && p >= goti[i][j].y+25)
            {
                a-=(5-i);
                b-=(5-j);
            }
        }
    }
    return b;
}


int main()
{
    bool resume = false;
    bool newgame = false;
    bool gamestarted = false;
    SDL_RenderClear(gRenderer);
    if( !init() )
    {
        cout<<"Failed to initialize!"<<endl;
    }
    else{
        if (!loadMedia()) {
            cout<<"Unable to load media"<<endl;
        }
        else
        {
           bool quit = false;
            SDL_RenderClear(gRenderer);
            for (int i=0;i<=9;i++) {
                writeover[i].free();
            }
            SDL_RenderClear(gRenderer);
            writeover[9].loadFromFile("background.jpg");
            writeover[8].loadFromFile("bottom.png");
            writeover[3].loadFromRenderedText("Welcome To The Game",SDL_Color{0xFF,0,0});
            writeover[4].loadFromRenderedText("Resume Game", SDL_Color{0xFF,0,0});
            writeover[5].loadFromRenderedText("New Game", SDL_Color{0xFF,0,0});
            writeover[6].loadFromRenderedText("Credits", SDL_Color{0xFF,0,0});
            writeover[7].loadFromRenderedText("Exit",SDL_Color{0xFF,0,0});
            
        SDL_RenderClear(gRenderer);
            Mix_PlayMusic( gMusic, -1 );
            SDL_Event e;
        while (!quit) {
            
            while( SDL_PollEvent( &e ) != 0 )
            {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                
                writeover[9].render(0,0);
                writeover[8].render(0,675);
                writeover[3].render(50,50);
                
                //Play the music
                
              

                for (int i = 4;i<=7;i++) {
                    writeover[i].x = 25;
                    writeover[i].y = 300+50*(i-4);
                    writeover[i].render(writeover[i].x,writeover[i].y);
                }
                switch (e.type) {
                        
                        case SDL_MOUSEMOTION:
                        int x1,y1;
                        SDL_GetMouseState(&x1,&y1);
                        if (x1>=writeover[4].x && y1>=writeover[4].y && x1<=writeover[4].x+writeover[4].getWidth() && y1<=writeover[4].y+writeover[4].getHeight())
                        {
                            writeover[4].loadFromRenderedText("Resume Game",SDL_Color{0,0xFF,0,0xFF});
                        }
                        else writeover[4].loadFromRenderedText("Resume Game",SDL_Color{0xFF,0,0});
                        
                        if (x1>=writeover[5].x && y1>=writeover[5].y && x1<=writeover[5].x+writeover[5].getWidth() && y1<=writeover[5].y+writeover[5].getHeight())
                        {
                            writeover[5].loadFromRenderedText("New Game",SDL_Color{0xFF,0xFF,0xFF});
                        }
                        else writeover[5].loadFromRenderedText("New Game",SDL_Color{0xFF,0,0});
                        
                        if (x1>=writeover[6].x && y1>=writeover[6].y && x1<=writeover[6].x+writeover[6].getWidth() && y1<=writeover[6].y+writeover[6].getHeight())
                        {
                            writeover[6].loadFromRenderedText("Credits",SDL_Color{0xFF,0xFF,0,0xFF});
                        }
                        else writeover[6].loadFromRenderedText("Credits",SDL_Color{0xFF,0,0});
                        
                        if (x1>=writeover[7].x && y1>=writeover[7].y && x1<=writeover[7].x+writeover[7].getWidth() && y1<=writeover[7].y+writeover[7].getHeight())
                        {
                            writeover[7].loadFromRenderedText("Exit",SDL_Color{0,0,0});
                        }
                        else writeover[7].loadFromRenderedText("Exit",SDL_Color{0xFF,0,0});
                        
                        
                        
                        
                    case SDL_MOUSEBUTTONDOWN:
                        switch (e.button.button) {
                            case SDL_BUTTON_LEFT:
                                int x1, y1;
                                SDL_GetMouseState( &x1, &y1 );
                                if (x1>=writeover[4].x && y1>=writeover[4].y && x1<=writeover[4].x+writeover[4].getWidth() && y1<=writeover[4].y+writeover[4].getHeight()) {
                                 //   SDL_ShowSimpleMessageBox(0,"Game Resumed","\tWelcome again \n \t \tHere is your unfinished game ",gWindow);
                                    gamestarted = true;
                                    resume = true;
                                    Mix_HaltMusic();

                                }
                                else resume = false;
                                if (x1>=writeover[5].x && y1>=writeover[5].y && x1<=writeover[5].x+writeover[5].getWidth() && y1<=writeover[5].y+writeover[5].getHeight()) {
                                    SDL_ShowSimpleMessageBox(0,"New game","Are you sure you want to start a new game?",gWindow);
                                    gamestarted = true;
                                    newgame = true;
                                    Mix_HaltMusic();
                                }
                                else newgame = false;
                                if (x1>=writeover[6].x && y1>=writeover[6].y && x1<=writeover[6].x+writeover[6].getWidth() && y1<=writeover[6].y+writeover[6].getHeight()) {
                                    SDL_ShowSimpleMessageBox(0,"Credits","The credit goes to: \n\t 1. Sujal Dhungana \n\t 2. Susan Gaire",gWindow);
                                }
                                
                                if (x1>=writeover[7].x && y1>=writeover[7].y && x1<=writeover[7].x+writeover[7].getWidth() && y1<=writeover[7].y+writeover[7].getHeight())
                                {
                                    SDL_ShowSimpleMessageBox(0,"Exit","Are you sure you want to exit?",gWindow);
                                    quit = true;
                                    break;
                                }
                                if (gamestarted) {
                                    {
                                        bool quit = false;
                                        SDL_Event e;
                                        bool dicestart = false;
                                        int count = 0;
                                        int palo = 0;
                                        bool green,red,yellow,blue;
                                        green = red = yellow = blue = false;
                                        int intl_x[4][4] = {-7,-7,63,63,398,398,468,468,-7,-7,63,63,398,398,468,468};
                                        int intl_y[4][4] = {125,55,125,55,125,55,125,55,530,460,530,460,530,460,530,460};
                                        for (int i=0;i<=3;) {
                                            for (int j=0;j<=3;) {
                                                
                                                goti[i][j].initial_x = intl_x[i][j];
                                                goti[i][j].initial_y=intl_y[i][j];
                                                goti[i][j].game_x = 230;
                                                goti[i][j].game_y = 295;
                                                j++;
                                            }
                                            i++;
                                        }
                                        if (newgame) {
                                            for (int i=0;i<=3;) {
                                                for (int j=0;j<=3;) {
                                                    goti[i][j].x = goti[i][j].initial_x;
                                                    goti[i][j].y=goti[i][j].initial_y;
                                                    j++;
                                                }
                                                i++;
                                            }
                                        }
                                        if (resume) {
                                            ifstream infile("gotiposition.DAT",ios::binary);
                                            infile.read(reinterpret_cast<char*>(&goti),sizeof(goti));
                                            cout<<goti[1][1].x;
                                        }
                                        for (int i=0;i<=3;i++) {
                                            goti[0][i].start_x = -40;
                                            goti[0][i].start_y = 250;
                                            goti[1][i].start_x = 275;
                                            goti[1][i].start_y = 25;
                                            goti[2][i].start_x = 185;
                                            goti[2][i].start_y = 565;
                                            goti[3][i].start_x = 500;
                                            goti[3][i].start_y = 340;
                                            goti[0][i].xirne_x = -85;
                                            goti[0][i].xirne_y = 295;
                                            goti[1][i].xirne_x = 230;
                                            goti[1][i].xirne_y = -20;
                                            goti[2][i].xirne_x = 230;
                                            goti[2][i].xirne_y = 610;
                                            goti[3][i].xirne_x = 545;
                                            goti[3][i].xirne_y = 295;
                                            
                                        }
                                        
                                        string str2 = "Green's Turn";
                                        
                                        while (!quit) {
                                            while (SDL_PollEvent(&e) !=0) {
                                                
                                                if (e.type==SDL_QUIT) {
                                                    ofstream outfile1("gotiposition.DAT",ios::binary);
                                                    ofstream outfile2("gotiposition.TXT");
                                                    outfile1.write(reinterpret_cast<char*>(&goti),sizeof(goti));
                                                    for (int i=0;i<=3;i++) {
                                                        for (int j=0;j<=3;j++) {
                                                        outfile2<<goti[i][j].x<<endl<<goti[i][j].y<<endl;
                                                        }
                                                    }
                                                    quit = true;
                                                }
                                            }
                                            //drawing
                                            {
                                                //Clear screen
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
                                                
                                                //dice
                                                SDL_Rect filldice = {0,680,675,70};
                                                SDL_SetRenderDrawColor(gRenderer, 0xFF,0xFF,0xFF,0xFF);
                                                SDL_RenderFillRect(gRenderer, &filldice);
                                            }
                                            
                                            //write @//
                                            string str1 = "@";
                                            
                                            SDL_Color textcolor = {0,0,0};
                                            writeover[0].loadFromRenderedText(str1,textcolor);
                                            writeover[0].render(360,40);
                                            writeover[0].render(360,535);
                                            writeover[0].render(270,580);
                                            writeover[0].render(90,355);
                                            writeover[0].render(45,265);
                                            writeover[0].render(270,85);
                                            writeover[0].render(540,265);
                                            writeover[0].render(585,355);
                                            writeover[1].loadFromRenderedText(str2,textcolor);
                                            writeover[1].render(100,700);
                                            dice.render(dice.x,dice.y);
                                            //rendergoti
                                            for (int i = 0;i<=3;i++) {
                                                for (int j=0;j<=3;j++)
                                                {
                                                    goti[i][j].render(goti[i][j].x,goti[i][j].y);
                                                }
                                            }
                                            
                                            switch (e.type) {
                                                    
                                                case SDL_MOUSEBUTTONDOWN:
                                                    switch (e.button.button) {
                                                        case SDL_BUTTON_LEFT:
                                                            int mousex = e.motion.x;
                                                            int mousey = e.motion.y;
                                                            int dicwidth = dice.getWidth();
                                                            int dicheight = dice.getHeight();
                                                            if(mousex<=dice.x+dicwidth&&mousex>=dice.x&&mousey<=dice.y+dicheight&&mousey>=dice.y)
                                                            {
                                                                dicestart = true;
                                                                Mix_PlayChannel( -1, gHigh, 0 );
                                                            }
                                                            checkcolor(mousex,mousey);
                                                            checknum(mousex,mousey);
                                                            if (dicestart && e.type == SDL_MOUSEBUTTONDOWN) {
                                                                dice.movedice();
                                                                dice.tiltdice();
                                                                dice.paryo();
                                                            }
                                                    }
                                                    break;
                                                case SDL_MOUSEBUTTONUP:
                                                {
                                                    
                                                    Mix_HaltMusic();
                                                    if (dicestart) {
                                                        
                                                        dice.stilldice(dice.pareko);
                                                        cout<<" k paryo? "<<endl<<dice.pareko<<endl;
                                                        SDL_Delay(100);
                                                        dice.stopdice();
                                                        count++;
                                                        blue = false;
                                                        if (palo == 0 && !blue) {
                                                            green = true;
                                                            goti[palo][1].movegoti(dice.pareko,palo);
                                                            palo++;
                                                            str2 = "Red's turn";
                                                           
                                                            if (dice.pareko == 1 || dice.pareko==6) {
                                                                palo--;
                                                                str2 = "Green's turn again";
                                                            }
                                                        }
                                                        else green = false;
                                                        
                                                        if (palo==1 && !green) {
                                                            str2 = "Yellow's turn";
                                                            goti[palo][1].movegoti(dice.pareko,palo);
                                                            palo++;
                                                            red = true;
                                                            if (dice.pareko == 1 || dice.pareko==6) {
                                                                palo--;
                                                                str2 = "Red's turn again";
                                                            }
                                                        }
                                                        else red = false;
                                                        
                                                        if (palo==2 && !red) {
                                                            str2 = "Blue's turn";
                                                            goti[palo][1].movegoti(dice.pareko,palo);
                                                            palo++;
                                                            yellow = true;
                                                            
                                                            if (dice.pareko == 1 || dice.pareko==6) {
                                                                palo--;
                                                                str2="Yellow's turn again";
                                                            }
                                                        }
                                                        else yellow = false;
                                                        
                                                        if (palo==3 && !yellow) {
                                                            str2 = "Green's turn";
                                                            blue =  true;
                                                            goti[palo][1].movegoti(dice.pareko,palo);
                                                            palo = 0;
                                                            
                                                            if (dice.pareko == 1 || dice.pareko==6) {
                                                                palo = 3;
                                                                str2 = "Blue's turn again";
                                                            }
                                                        }
                                                        else blue = false;
                                                    }
                                                    dicestart = false;
                                                    
                                                }
                                                    
                                            }
                                            
                                            SDL_RenderPresent(gRenderer);
                                            
                                        }
                                        
                                    }
                                }
                                
                                break;
                                
                        }
                        break;
                        
                        default:
                        
                        break;
                }
         
            
            }
            
        
           SDL_RenderPresent(gRenderer);
        }
        
              close();
        }

    
}
    
}



