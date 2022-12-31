#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <algorithm>
#include "highscore.h"
#include "media.h"
#include "initial.h"
#include "collision.h"
#include "texture.h"
#include "menu.h"

//Screen dimension constants
// const int SCREEN_WIDTH = 1240;
// const int SCREEN_HEIGHT = 720;

//car width and height constant
const int CAR_WIDTH = 40;
const int CAR_HEIGHT = 80;

//Our main car velocity
int CAR_VelX=0, CAR_VelY=0;
int CAR_VEL=10;
bool pause = false;

//declaration of variables


int n;
int high;
int score;
int night;
int currentTime;
int Final=0;
char crr[6];
char drr[50] = "Score: ";
int total=0;
char err[6];
char frr[20] ="Life: ";
char mrr[20] ="Coin: ";
char nrr[6];
char scoreString[1000];
char lifeString[1000];
char coinString[1000];


char grr[6];
char hrr[20] ="Run time: ";
char runString[1000];

// FOR TTF font
//TTF_Font* Sans =NULL;
SDL_Color Black ={0,255,0};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
//SDL_Window* gWindow = NULL;

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window renderer
//SDL_Renderer* gRenderer = NULL;

//Current displayed texture


//structure car. Here car[0] is our main car.
SDL_Rect car[5];
//structure boy,life 1,life 2;
SDL_Rect boy;
SDL_Rect life;
SDL_Rect life1;
SDL_Rect coin;
SDL_Rect coin1;


//structure background
SDL_Rect bg1;
SDL_Rect bg2;



void higscore(int t);


int mainMenu(SDL_Event e);



//moving the bike
void move(SDL_Rect a)
{//Move the bike left or right
	car[0].x += CAR_VelX;

   //If the bike went too far to the left or right
	if( (car[0].x < 128 ) || ( car[0].x+ 120 > 1048 ) )
	{
		//Move back
		car[0].x -= CAR_VelX;
	}
		//Move the bike up or down
	car[0].y += CAR_VelY;

		//If the bike went too far up or down
	if( ( car[0].y< 0 ) || (car[0].y + 180 > SCREEN_HEIGHT ) )
	{
		  //Move back
		car[0].y -= CAR_VelY;
	}

}

//collision detection
bool checkCollision(SDL_Rect a , SDL_Rect b);



bool quitGame()
{
	return true;

}

void close()
{
	//Destroy window    
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

//string function
void _itoa(int a,char brr[]){

	for(int p =0;p<5;p++){
		brr[p]=48;
	}
	for(int j =0;j<5;j++){

		brr[j]=(a%10)+48;
		a/=10;
	}
	brr[5]=0;
	std::reverse(brr, brr + 5);

}

int main( int argc, char* args[] )
{	
    //starts timer
	int start = SDL_GetTicks();
	//initialising arrray of structure car		
	car[0].x=SCREEN_WIDTH/2;
	car[0].y=4*SCREEN_HEIGHT/6;
	car[0].w=CAR_WIDTH;
	car[0].h=CAR_HEIGHT;

	car[1].x=SCREEN_WIDTH/4;
	car[1].y=4*SCREEN_HEIGHT/6;
	car[1].w=CAR_WIDTH;
	car[1].h=CAR_HEIGHT;

	car[2].x=3*SCREEN_WIDTH/4;
	car[2].y=3*SCREEN_HEIGHT/6;
	car[2].w=CAR_WIDTH;
	car[2].h=CAR_HEIGHT;

	car[3].x=SCREEN_WIDTH/3;
	car[3].y=2*SCREEN_HEIGHT/6;
	car[3].w=CAR_WIDTH;
	car[3].h=CAR_HEIGHT;

	car[4].x=SCREEN_WIDTH/8;
	car[4].y=1*SCREEN_HEIGHT/6;
	car[4].w=CAR_WIDTH;
	car[4].h=CAR_HEIGHT;

	life.x=5*SCREEN_WIDTH/7;
	life.y=0;
	life.w=20;
	life.h=20;

	life1.x=4*SCREEN_WIDTH/2;
	life1.y=0;
	life1.w=20;
	life1.h=20;

	coin.x=700;
	coin.y=0;
	coin.w=20;
	coin.h=20;

   coin1.x=500;
	coin1.y=0;
	coin1.w=20;
	coin1.h=20;

	//boy.x=-100;
	//boy.y=-70;
	//boy.w=40;
	//boy.h=90;


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
			int start, flag;
			bool notStarted = true;

			//Event handler
			SDL_Event e;
			int gameState=0;
			int scrollingOffset = 0;
			int i=5;
			//While application is running
			while( !quit )
			{	
				if(gameState==0)  
				{	CAR_VelX=0; CAR_VelY=0;
					 CAR_VEL=10;
					while( SDL_PollEvent( &e ) != 0 )
					{   
						if( e.type == SDL_QUIT )
						{
							gameState=4;
						}
						else if(e.type == SDL_MOUSEBUTTONDOWN){ 
							if(e.button.x > (139*SCREEN_WIDTH)/1280 && e.button.x < (527*SCREEN_WIDTH)/1280 && e.button.y > (521*SCREEN_HEIGHT)/720 && e.button.y < (574*SCREEN_HEIGHT)/720){
								gameState = 1;
								notStarted = true;
								Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
	    			// load music
								Mix_Music*backgroundSound=Mix_LoadMUS("FINE.mp3");
								Mix_PlayMusic(backgroundSound, -1);

							}
							else if(e.button.x > (631*SCREEN_WIDTH)/1280 && e.button.x < (1259*SCREEN_WIDTH)/1280 && e.button.y > (529*SCREEN_HEIGHT)/720 && e.button.y < (572*SCREEN_HEIGHT)/720){
								gameState = 2;
							}
							else if(e.button.x > (18*SCREEN_WIDTH)/1280 && e.button.x < (759*SCREEN_WIDTH)/1280 && e.button.y > (623*SCREEN_HEIGHT)/720 && e.button.y < (672*SCREEN_HEIGHT)/720){
								gameState = 3;
							}
							else if(e.button.x > (834*SCREEN_WIDTH)/1280 && e.button.x < (1103*SCREEN_WIDTH)/1280 && e.button.y > (627*SCREEN_HEIGHT)/720 && e.button.y < (678*SCREEN_HEIGHT)/720){
								gameState = 4;
							}
						}
					}
				 //Clear screen
					SDL_RenderClear( gRenderer );
					SDL_RenderCopy( gRenderer, gmenuTexture, NULL, NULL );
				//Update screen
					SDL_RenderPresent( gRenderer );
				}
				//printf("%d\n",gameState);

				if(gameState==1)
					{	 
						while(pause){
							while( SDL_PollEvent( &e ) != 0 ){
								if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
								{
					        //Adjust the velocity
								switch( e.key.keysym.sym )
									{
									case SDLK_SPACE: pause = !pause; break;
									}
								}
							}
						}  
					//Handle events on queue
						if(notStarted){

                            SDL_RenderClear( gRenderer );
						    SDL_RenderCopy( gRenderer, gloadingTexture, NULL, NULL );
							SDL_RenderPresent( gRenderer );
							SDL_Delay(1000);

                            SDL_RenderClear( gRenderer );
						    SDL_RenderCopy( gRenderer, glevel1Texture, NULL, NULL );
							SDL_RenderPresent( gRenderer );
							SDL_Delay(1000);
                        	
							
							flag = 0;
							score = 0;
							night = 0;
							start = SDL_GetTicks();
							Final=0;
							i = 6;
							
							car[0].x=SCREEN_WIDTH/2;
							car[0].y=4*SCREEN_HEIGHT/6;
							car[0].w=CAR_WIDTH;
							car[0].h=CAR_HEIGHT;

							car[1].x=SCREEN_WIDTH/4;
							car[1].y=4*SCREEN_HEIGHT/6;
							car[1].w=CAR_WIDTH;
							car[1].h=CAR_HEIGHT;

							car[2].x=3*SCREEN_WIDTH/4;
							car[2].y=3*SCREEN_HEIGHT/6;
							car[2].w=CAR_WIDTH;
							car[2].h=CAR_HEIGHT;

							car[3].x=SCREEN_WIDTH/3;
							car[3].y=2*SCREEN_HEIGHT/6;
							car[3].w=CAR_WIDTH;
							car[3].h=CAR_HEIGHT;

							car[4].x=SCREEN_WIDTH/8;
							car[4].y=1*SCREEN_HEIGHT/6;
							car[4].w=CAR_WIDTH;
							car[4].h=CAR_HEIGHT;

							life.x=5*SCREEN_WIDTH/7;
							life.y=0;
							life.w=20;
							life.h=20;

							life1.x=4*SCREEN_WIDTH/2;
							life1.y=0;
							life1.w=20;
							life1.h=20;

							coin.x=700;
	                        coin.y=0;
	                        coin.w=20;
	                        coin.h=20;
                              

                               coin1.x=500;
	                           coin1.y=0;
	                           coin1.w=20;
	                           coin1.h=20;

							//boy.x=-100;
							//boy.y=0;
							//boy.w=40;
							//boy.h=90;

							notStarted = false;




						}
						currentTime = SDL_GetTicks() - start;

						while( SDL_PollEvent( &e ) != 0 )
						{
						//User requests quit
							if( e.type == SDL_QUIT )
							{
								quit=true;
							}
						//If a key was pressed
							else if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
							{
					        //Adjust the velocity
								switch( e.key.keysym.sym )
								{
									case SDLK_UP: CAR_VelY -= CAR_VEL; break;
									case SDLK_DOWN: CAR_VelY += CAR_VEL; break;
									case SDLK_LEFT: CAR_VelX -= CAR_VEL; break;
									case SDLK_RIGHT: CAR_VelX += CAR_VEL; break;
									case SDLK_SPACE: pause = !pause; break;
								}
							}
						 //If a key was released
							else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
							{
					        //Adjust the velocity
								switch( e.key.keysym.sym )
								{
									case SDLK_UP: CAR_VelY += CAR_VEL; break;
									case SDLK_DOWN: CAR_VelY -= CAR_VEL; break;
									case SDLK_LEFT: CAR_VelX += CAR_VEL; break;
									case SDLK_RIGHT: CAR_VelX -= CAR_VEL; break;
								}
							}
						}
						if(currentTime%1000==0) i++;
					//Scroll background
						scrollingOffset=scrollingOffset+i;
						if( scrollingOffset > SCREEN_HEIGHT )
						{
							scrollingOffset = 0;
						}

					//updating bike position 
						for(int j=1;j<5;j++)
						{
							car[j].y=car[j].y+i;
							if(car[j].h<CAR_HEIGHT) car[j].h++;
							if(car[j].y>SCREEN_HEIGHT)  
							{
								//car[j].h=0;
								car[j].y=-300;
								car[j].x=car[j].x+SCREEN_WIDTH/5;
								if(car[j].x>880)  car[j].x=SCREEN_WIDTH/8;
							}
						}
					//updating life position
						life.y+=i;
						if(life.y>SCREEN_HEIGHT)
							{life.y=rand()%SCREEN_HEIGHT;
								life.x= rand() %(880) + SCREEN_WIDTH/8;
							}

                          //updating life  1 position
							life1.y+=i;
							if(life1.y>SCREEN_HEIGHT)
								{life1.y=rand()%SCREEN_HEIGHT;
									life1.x= rand() %(880) + SCREEN_WIDTH/6;
								}

								 //updating coin position
							coin.y+=i;
							if(coin.y>SCREEN_HEIGHT)
								{coin.y=rand()%SCREEN_HEIGHT;
									coin.x= rand() %(880) + 700;
								}

									 //updating coin 1 position
							coin1.y+=i;
							if(coin1.y>SCREEN_HEIGHT)
								{coin1.y=rand()%SCREEN_HEIGHT;
									coin1.x= rand() %(880) + 500;
								}
					  //updating boy's position
								//if(flag==0)
								//	boy.x+=3;
								//else boy.x-=3;
								//boy.y+=i/2;

								//if(boy.x>SCREEN_WIDTH ||boy.x<0) 

								//	{	int a=rand()%2;
								//		if(a==0)
								////			{	boy.x=128;
									//			flag=0;
									//		}
									//		else
									//			{	boy.x=1048;
									//				flag=1;
									//			}
									//			boy.y=rand() % (SCREEN_HEIGHT/2);
									//		}
                          	//Move the car left or right
											move(car[0]);

				                            //check collision

											for(int k=1;k<5;k++)
											{

												if(checkCollision(car[0],car[k])==true)
												{    
													printf(" Game Over\n");
													Final=currentTime/1000;
													gameState=5;
												}
											}
											if(checkCollision(car[0],life)==true)
											{
												life.y=-100, life.x=-100;
												//i -= 1;

												Final=currentTime/1000;
												score=score+2;

											}

											if(checkCollision(car[0],coin)==true)
											{
												coin.y=-100, coin.x=-100;
												//i -= 1;

												Final=currentTime/1000;
												night=night+10;

											}

											if(checkCollision(car[0],coin1)==true)
											{
												coin1.y=-100, coin1.x=-100;
												//i -= 1;

												Final=currentTime/1000;
												night=night+30;

											}
											

											if(checkCollision(car[0],life1)==true)
											{
												life1.y=-100, life1.x=-100;

											 Final=currentTime/1000;
												score=score+2;
												i++;

											}
											if(checkCollision(car[0],boy)==true)
											{
												printf(" Game Over\n");
					  
												Final=currentTime/1000;
												gameState=5;
											}

											for(int k=1;k<5;k++)
											{
												Final=currentTime/1000;
												if(checkCollision(car[k],boy)==true)
													boy.x=-100;
											} 
					//structure background
											bg1.x=0;
											bg1.y=scrollingOffset-SCREEN_HEIGHT;
											bg1.w=SCREEN_WIDTH;
					//bg1.h=scrollingOffset;
											bg1.h=SCREEN_HEIGHT;

											bg2.x=0;
											bg2.y=scrollingOffset;
											bg2.w=SCREEN_WIDTH;
					                        bg2.h=SCREEN_HEIGHT;//- scrollingOffset;


					//Clear screen
					//SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear( gRenderer );
					SDL_RenderCopy( gRenderer, gBGTexture, NULL, &bg1 );
					SDL_RenderCopy( gRenderer, gBGTexture, NULL, &bg2 );

					//Apply the image(bike)
					for(int k=0;k<5;k++)
					{
						SDL_RenderCopy( gRenderer, gCARTexture[k], NULL,&car[k]);
					}
					SDL_RenderCopy( gRenderer, glifeTexture, NULL,&life);
					SDL_RenderCopy( gRenderer, glife1Texture, NULL,&life1);
					SDL_RenderCopy( gRenderer, gboyTexture, NULL,&boy);
					SDL_RenderCopy( gRenderer, gcoinTexture, NULL,&coin);
					SDL_RenderCopy( gRenderer, gcoin1Texture, NULL,&coin1);


					printf(" LIFE  = %d\n", score);
					printf(" Coin  = %d\n", night);

					printf("Run Time  = %d\n", Final);
					total = score + Final+night;
					
					printf("Final SCORE = %d\n",total);
					strcpy(drr, "Your Score: ");
					_itoa(total, crr);
					printf("%s\n",crr);
					strcat(drr, crr);
					strcpy(frr, "Life: ");
					_itoa(score, err);
					printf("%s\n",err);
					
					strcat(frr,err);
					strcpy(mrr, "Coin: ");
					_itoa(night, nrr);
					printf("%s\n",nrr);;
					strcat(mrr,nrr);
					strcpy(hrr, "Runtime: ");
					_itoa(Final, grr);
					printf("%s\n",grr);
					strcat(hrr,grr);
						//ttf load
					SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, drr, Black);
					SDL_Texture * Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
					if (Message == NULL)
					{
						printf("Unable to load text texture\n");
					}

					SDL_Rect Message_rect;

					Message_rect.x = 950;
					Message_rect.y = 70;
					Message_rect.w = 120;
					Message_rect.h = 30;

					SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);

					SDL_Surface *surfaceMessage2 = TTF_RenderText_Solid(Sans, frr, Black);
					SDL_Texture * Message2 = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage2);
					if (Message2 == NULL)
					{
						printf("Unable to load text texture\n");
					}

					SDL_Rect Message_rect2;

					Message_rect2.x = 45;
					Message_rect2.y = 90;
					Message_rect2.w = 100;
					Message_rect2.h = 30;

					SDL_RenderCopy(gRenderer, Message2, NULL, &Message_rect2);

					SDL_Surface *surfaceMessage3 = TTF_RenderText_Solid(Sans, hrr, Black);
					SDL_Texture * Message3 = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage3);
					if (Message3 == NULL)
					{
						printf("Unable to load text texture\n");
					}

					SDL_Rect Message_rect3;

					Message_rect3.x = 45;
					Message_rect3.y = 60;
					Message_rect3.w = 100;
					Message_rect3.h = 30;

					SDL_RenderCopy(gRenderer, Message3, NULL, &Message_rect3);

					SDL_Surface *surfaceMessage4 = TTF_RenderText_Solid(Sans, mrr, Black);
					SDL_Texture * Message4 = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage4);
					if (Message4 == NULL)
					{
						printf("Unable to load text texture\n");
					}

					SDL_Rect Message_rect4;

					Message_rect4.x = 45;
					Message_rect4.y = 120;
					Message_rect4.w = 100;
					Message_rect4.h = 30;

					SDL_RenderCopy(gRenderer, Message4, NULL, &Message_rect4);
					if(gameState == 0) SDL_Delay(2000);
					
					    		//Render_Text(crr);

					//Update screen
					SDL_RenderPresent( gRenderer );
	                //runtime=SDL_GetTicks()-start;
	                if(total >= 150){
	                	gameState = 7;
	                	notStarted = true;	
	                } 
	                
					
				}
                 ///level 2
				if(gameState == 7){

					while(pause){
							while( SDL_PollEvent( &e ) != 0 ){
								if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
								{
					        //Adjust the velocity
								switch( e.key.keysym.sym )
									{
									case SDLK_SPACE: pause = !pause; break;
									}
								}
							}
						}

                            //SDL_Delay(2000);
                        	
                         
					//Handle events on queue
						if(notStarted){
							SDL_RenderClear( gRenderer );
						    SDL_RenderCopy( gRenderer, glevel2Texture, NULL, NULL );
							SDL_RenderPresent( gRenderer );
							SDL_Delay(1000);
                        	

							flag = 0;
							//score = 0;
							//start = SDL_GetTicks();
							//Final=0;
							i = 9;
							
							car[0].x=SCREEN_WIDTH/2;
							car[0].y=4*SCREEN_HEIGHT/6;
							car[0].w=CAR_WIDTH;
							car[0].h=CAR_HEIGHT;

							car[1].x=SCREEN_WIDTH/4;
							car[1].y=4*SCREEN_HEIGHT/6;
							car[1].w=CAR_WIDTH;
							car[1].h=CAR_HEIGHT;

							car[2].x=3*SCREEN_WIDTH/4;
							car[2].y=3*SCREEN_HEIGHT/6;
							car[2].w=CAR_WIDTH;
							car[2].h=CAR_HEIGHT;

							car[3].x=SCREEN_WIDTH/3;
							car[3].y=2*SCREEN_HEIGHT/6;
							car[3].w=CAR_WIDTH;
							car[3].h=CAR_HEIGHT;

							car[4].x=SCREEN_WIDTH/8;
							car[4].y=1*SCREEN_HEIGHT/6;
							car[4].w=CAR_WIDTH;
							car[4].h=CAR_HEIGHT;

							life.x=5*SCREEN_WIDTH/7;
							life.y=0;
							life.w=20;
							life.h=20;

							life1.x=4*SCREEN_WIDTH/2;
							life1.y=0;
							life1.w=20;
							life1.h=20;
 coin.x=700;
	                        coin.y=0;
	                        coin.w=20;
	                        coin.h=20;
                              

                               coin1.x=500;
	                           coin1.y=0;
	                           coin1.w=20;
	                           coin1.h=20;

							boy.x=-100;
							boy.y=0;
							boy.w=40;
							boy.h=90;

							notStarted = false;


						}
						currentTime = SDL_GetTicks() - start;

						while( SDL_PollEvent( &e ) != 0 )
						{
						//User requests quit
							if( e.type == SDL_QUIT )
							{
								quit=true;
							}

						//for moving the main bike

						//If a key was pressed
							else if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
							{
					        //Adjust the velocity
								switch( e.key.keysym.sym )
								{
									case SDLK_UP: CAR_VelY -= CAR_VEL; break;
									case SDLK_DOWN: CAR_VelY += CAR_VEL; break;
									case SDLK_LEFT: CAR_VelX -= CAR_VEL; break;
									case SDLK_RIGHT: CAR_VelX += CAR_VEL; break;
									case SDLK_SPACE: pause = !pause; break;
								}
							}
						 //If a key was released
							else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
							{
					        //Adjust the velocity
								switch( e.key.keysym.sym )
								{
									case SDLK_UP: CAR_VelY += CAR_VEL; break;
									case SDLK_DOWN: CAR_VelY -= CAR_VEL; break;
									case SDLK_LEFT: CAR_VelX += CAR_VEL; break;
									case SDLK_RIGHT: CAR_VelX -= CAR_VEL; break;
								}
							}
						}
						if(currentTime%1000==0) i++;
					//Scroll background
						scrollingOffset=scrollingOffset+i;
						if( scrollingOffset > SCREEN_HEIGHT )
						{
							scrollingOffset = 0;


						}

					//updating bike position 
						for(int j=1;j<5;j++)
						{
							car[j].y=car[j].y+i;
							if(car[j].h<CAR_HEIGHT) car[j].h++;
							if(car[j].y>SCREEN_HEIGHT)  
							{
								//car[j].h=0;
								car[j].y=-300;
								car[j].x=car[j].x+SCREEN_WIDTH/5;
								if(car[j].x>880)  car[j].x=SCREEN_WIDTH/8;
							}
						}
					//updating life position
						life.y+=i;
						if(life.y>SCREEN_HEIGHT)
							{life.y=rand()%SCREEN_HEIGHT;
								life.x= rand() %(880) + SCREEN_WIDTH/8;
							}

//updating life  1 position
							life1.y+=i;
							if(life1.y>SCREEN_HEIGHT)
								{life1.y=rand()%SCREEN_HEIGHT;
									life1.x= rand() %(880) + SCREEN_WIDTH/6;
								}
 
								 //updating coin position
							coin.y+=i;
							if(coin.y>SCREEN_HEIGHT)
								{coin.y=rand()%SCREEN_HEIGHT;
									coin.x= rand() %(880) + 700;
								}

									 //updating coin 1 position
							coin1.y+=i;
							if(coin1.y>SCREEN_HEIGHT)
								{coin1.y=rand()%SCREEN_HEIGHT;
									coin1.x= rand() %(880) + 500;
								}

					//updating boy's position
								if(flag==0)
									boy.x+=3;
								else boy.x-=3;
								boy.y+=i/2;

								if(boy.x>SCREEN_WIDTH ||boy.x<0) 

									{	int a=rand()%2;
										if(a==0)
											{	boy.x=128;
								//boy.y=rand()%SCREEN_WIDTH;
												flag=0;
											}
											else
												{	boy.x=1048;
								//boy.y=rand()%(SCREEN_WIDTH/2);
													flag=1;

												}
												boy.y=rand() % (SCREEN_HEIGHT/2);

											}


					//Move the car left or right
											move(car[0]);

				    //check collision

											for(int k=1;k<5;k++)
											{
												

												if(checkCollision(car[0],car[k])==true)
												{    

													printf(" Game Over\n");

                            //printf("Run Time = %d seconds\n",currentTime/1000);
													Final=currentTime/1000;
													gameState=5;
													//break;

												}
											}
											if(checkCollision(car[0],life)==true)
											{
												life.y=-100, life.x=-100;

												Final=currentTime/1000;
												score=score+5;
												i -= 1;

											}
											if(checkCollision(car[0],life1)==true)
											{
												life1.y=-100, life1.x=-100;


												Final=currentTime/1000;
												score=score+5;
												i++;

											}

											if(checkCollision(car[0],coin)==true)
											{
												coin.y=-100, coin.x=-100;
												//i -= 1;

												Final=currentTime/1000;
												night=night+15;

											}

											if(checkCollision(car[0],coin1)==true)
											{
												coin1.y=-100, coin1.x=-100;
												//i -= 1;

												Final=currentTime/1000;
												night=night+100;

											}
											
											if(checkCollision(car[0],boy)==true)
											{
												printf(" Game Over\n");
					    //printf("Run Time = %d seconds\n",currentTime/1000);
												Final=currentTime/1000;
												gameState=5;
												

												//break;
											}
											for(int k=1;k<5;k++)
											{

												Final=currentTime/1000;
												if(checkCollision(car[k],boy)==true)
													boy.x=-100;
											}

					//structure background
											bg1.x=0;
											bg1.y=scrollingOffset-SCREEN_HEIGHT;
											bg1.w=SCREEN_WIDTH;
					//bg1.h=scrollingOffset;
											bg1.h=SCREEN_HEIGHT;

											bg2.x=0;
											bg2.y=scrollingOffset;
											bg2.w=SCREEN_WIDTH;
					                        bg2.h=SCREEN_HEIGHT;//- scrollingOffset;
					//Clear screen
					SDL_RenderClear( gRenderer );
					SDL_RenderCopy( gRenderer, gBGTexture, NULL, &bg1 );
					SDL_RenderCopy( gRenderer, gBGTexture, NULL, &bg2 );
					//Apply the image(car)
					for(int k=0;k<5;k++)
					{
						SDL_RenderCopy( gRenderer, gCARTexture[k], NULL,&car[k]);
					}
					SDL_RenderCopy( gRenderer, glifeTexture, NULL,&life);
					SDL_RenderCopy( gRenderer, glife1Texture, NULL,&life1);
					SDL_RenderCopy( gRenderer, gboyTexture, NULL,&boy);
					SDL_RenderCopy( gRenderer, gcoinTexture, NULL,&coin);
					SDL_RenderCopy( gRenderer, gcoin1Texture, NULL,&coin1);

					printf(" LIFE  = %d\n", score);
					printf(" Coin  = %d\n", night);
					printf("Run Time  = %d\n", Final);
					total = score + Final+night;
					printf("Final SCORE = %d\n",total);
					strcpy(drr, "Your Score: ");
					_itoa(total, crr);
					printf("%s\n",crr);
					strcat(drr, crr);
					strcpy(frr, "Life: ");
					_itoa(score, err);
					printf("%s\n",err);
					strcat(frr,err);
					strcpy(hrr, "Runtime: ");
					_itoa(Final, grr);
					printf("%s\n",grr);
					strcat(hrr,grr);
					strcpy(mrr, "Coin: ");
					_itoa(night, nrr);
					printf("%s\n",nrr);;
					strcat(mrr,nrr);
					Black.r=255;
					SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, drr, Black);
					SDL_Texture * Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
					if (Message == NULL)
					{
						printf("Unable to load text texture\n");
					}

					SDL_Rect Message_rect;
                   Message_rect.x = 950;
					Message_rect.y = 70;
					Message_rect.w = 120;
					Message_rect.h = 20;

					SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);

					Black.r=255;
					SDL_Surface *surfaceMessage2 = TTF_RenderText_Solid(Sans, frr, Black);
					SDL_Texture * Message2 = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage2);
					if (Message2 == NULL)
					{
						printf("Unable to load text texture\n");
					}

					SDL_Rect Message_rect2;

					Message_rect2.x = 45;
					Message_rect2.y = 90;
					Message_rect2.w = 100;
					Message_rect2.h = 30;

					SDL_RenderCopy(gRenderer, Message2, NULL, &Message_rect2);
					Black.r=255;
					SDL_Surface *surfaceMessage3 = TTF_RenderText_Solid(Sans, hrr, Black);
					SDL_Texture * Message3 = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage3);
					if (Message3 == NULL)
					{
						printf("Unable to load text texture\n");
					}

					SDL_Rect Message_rect3;

					Message_rect3.x = 45;
					Message_rect3.y = 60;
					Message_rect3.w = 100;
					Message_rect3.h = 30;

					SDL_RenderCopy(gRenderer, Message3, NULL, &Message_rect3);
					SDL_Surface *surfaceMessage4 = TTF_RenderText_Solid(Sans, mrr, Black);
					SDL_Texture * Message4 = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage4);
					if (Message4 == NULL)
					{
						printf("Unable to load text texture\n");
					}

					SDL_Rect Message_rect4;

					Message_rect4.x = 45;
					Message_rect4.y = 120;
					Message_rect4.w = 100;
					Message_rect4.h = 30;

					SDL_RenderCopy(gRenderer, Message4, NULL, &Message_rect4);
					if(gameState == 0) SDL_Delay(2000);
					
					    		//Render_Text(crr);

					//Update screen
					SDL_RenderPresent( gRenderer );
					if(total >= 600){
	                	gameState = 8;
	                	notStarted = true;	
	                //runtime=SDL_GetTicks()-start;
	                
				}

				 ///level 3 
				}
				if(gameState == 8){

					pause = false;

					while(pause){
							while( SDL_PollEvent( &e ) != 0 ){
								if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
								{
					        //Adjust the velocity
								switch( e.key.keysym.sym )
									{
									case SDLK_SPACE: pause = !pause; break;
									}
								}
							}
						}

                            //SDL_Delay(2000);
                        	
                         
					//Handle events on queue
						if(notStarted){
							SDL_RenderClear( gRenderer );
						    SDL_RenderCopy( gRenderer, glevel3Texture, NULL, NULL );
							SDL_RenderPresent( gRenderer );
							SDL_Delay(1000);
                        	

							//flag = 0;
							//score = 0;
							//start = SDL_GetTicks();
							//Final=0;
							i = 13;
							
							car[0].x=SCREEN_WIDTH/2;
							car[0].y=4*SCREEN_HEIGHT/6;
							car[0].w=CAR_WIDTH;
							car[0].h=CAR_HEIGHT;

							car[1].x=SCREEN_WIDTH/4;
							car[1].y=4*SCREEN_HEIGHT/6;
							car[1].w=CAR_WIDTH;
							car[1].h=CAR_HEIGHT;

							car[2].x=3*SCREEN_WIDTH/4;
							car[2].y=3*SCREEN_HEIGHT/6;
							car[2].w=CAR_WIDTH;
							car[2].h=CAR_HEIGHT;

							car[3].x=SCREEN_WIDTH/3;
							car[3].y=2*SCREEN_HEIGHT/6;
							car[3].w=CAR_WIDTH;
							car[3].h=CAR_HEIGHT;

							car[4].x=SCREEN_WIDTH/8;
							car[4].y=1*SCREEN_HEIGHT/6;
							car[4].w=CAR_WIDTH;
							car[4].h=CAR_HEIGHT;

							life.x=5*SCREEN_WIDTH/7;
							life.y=0;
							life.w=20;
							life.h=20;

							life1.x=4*SCREEN_WIDTH/2;
							life1.y=0;
							life1.w=20;
							life1.h=20;

							boy.x=-100;
							boy.y=0;
							boy.w=40;
							boy.h=90;
							coin.x=700;
	                        coin.y=0;
	                        coin.w=20;
	                        coin.h=20;
                              

                               coin1.x=500;
	                           coin1.y=0;
	                           coin1.w=20;
	                           coin1.h=20;


							notStarted = false;


						}
						currentTime = SDL_GetTicks() - start;

						while( SDL_PollEvent( &e ) != 0 )
						{
						//User requests quit
							if( e.type == SDL_QUIT )
							{
								quit=true;
							}

						//for moving the main car

						//If a key was pressed
							else if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
							{
					        //Adjust the velocity
								switch( e.key.keysym.sym )
								{
									case SDLK_UP: CAR_VelY -= CAR_VEL; break;
									case SDLK_DOWN: CAR_VelY += CAR_VEL; break;
									case SDLK_LEFT: CAR_VelX -= CAR_VEL; break;
									case SDLK_RIGHT: CAR_VelX += CAR_VEL; break;
									case SDLK_SPACE: pause = !pause; break;
								}
							}
						 //If a key was released
							else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
							{
					        //Adjust the velocity
								switch( e.key.keysym.sym )
								{
									case SDLK_UP: CAR_VelY += CAR_VEL; break;
									case SDLK_DOWN: CAR_VelY -= CAR_VEL; break;
									case SDLK_LEFT: CAR_VelX += CAR_VEL; break;
									case SDLK_RIGHT: CAR_VelX -= CAR_VEL; break;
								}
							}
						}
						if(currentTime%750==0) i++;
					//Scroll background
						scrollingOffset=scrollingOffset+i;
						if( scrollingOffset > SCREEN_HEIGHT )
						{
							scrollingOffset = 0;


						}

					//updating cars position 
						for(int j=1;j<5;j++)
						{
							car[j].y=car[j].y+i;
							if(car[j].h<CAR_HEIGHT) car[j].h++;
							if(car[j].y>SCREEN_HEIGHT)  
							{
								//car[j].h=0;
								car[j].y=-300;
								car[j].x=car[j].x+SCREEN_WIDTH/5;
								if(car[j].x>880)  car[j].x=SCREEN_WIDTH/8;
							}
						}
					//updating life position
						life.y+=i;
						if(life.y>SCREEN_HEIGHT)
							{life.y=rand()%SCREEN_HEIGHT;
								life.x= rand() %(880) + SCREEN_WIDTH/8;
							}

                              //updating life  1 position
							life1.y+=i;
							if(life1.y>SCREEN_HEIGHT)
								{life1.y=rand()%SCREEN_HEIGHT;
									life1.x= rand() %(880) + SCREEN_WIDTH/6;
								}
	 //updating coin position
							coin.y+=i;
							if(coin.y>SCREEN_HEIGHT)
								{coin.y=rand()%SCREEN_HEIGHT;
									coin.x= rand() %(880) + 700;
								}

									 //updating coin 1 position
							coin1.y+=i;
							if(coin1.y>SCREEN_HEIGHT)
								{coin1.y=rand()%SCREEN_HEIGHT;
									coin1.x= rand() %(880) + 500;
								}

					//updating boy's position
								if(flag==0)
									boy.x+=3;
								else boy.x-=3;
								boy.y+=i/2;

								if(boy.x>SCREEN_WIDTH ||boy.x<0) 

									{	int a=rand()%2;
										if(a==0)
											{	boy.x=128;
								//boy.y=rand()%SCREEN_WIDTH;
												flag=0;
											}
											else
												{	boy.x=1048;
								//boy.y=rand()%(SCREEN_WIDTH/2);
													flag=1;

												}
												boy.y=rand() % (SCREEN_HEIGHT/2);

											}


					//Move the bike left or right
											move(car[0]);

				    //check collision

											for(int k=1;k<5;k++)
											{

												if(checkCollision(car[0],car[k])==true)
												{    
													printf(" Game Over\n");

                            //printf("Run Time = %d seconds\n",currentTime/1000);
													Final=currentTime/1000;
													gameState=5;
													//break;

												}
											}
											if(checkCollision(car[0],life)==true)
											{
												life.y=-100, life.x=-100;
												i -=1;

												Final=currentTime/1000;
												score=score+5;

											}
											if(checkCollision(car[0],life1)==true)
											{
												life1.y=-100, life1.x=-100;
												
												i++;


												Final=currentTime/1000;
												score=score+5;

											}


											if(checkCollision(car[0],coin)==true)
											{
												coin.y=-100, coin.x=-100;
												//i -= 1;

												Final=currentTime/1000;
												night=night+20;

											}

											if(checkCollision(car[0],coin1)==true)
											{
												coin1.y=-100, coin1.x=-100;
												//i -= 1;

												Final=currentTime/1000;
												night=night+200;

											}
											
											if(checkCollision(car[0],boy)==true)
											{
												printf(" Game Over\n");
					    //printf("Run Time = %d seconds\n",currentTime/1000);
												Final=currentTime/1000;
												gameState=5;

												//break;
											}
											for(int k=1;k<5;k++)
											{

												Final=currentTime/1000;
												if(checkCollision(car[k],boy)==true)
													boy.x=-100;
											} 

					//structure background
											bg1.x=0;
											bg1.y=scrollingOffset-SCREEN_HEIGHT;
											bg1.w=SCREEN_WIDTH;
					//bg1.h=scrollingOffset;
											bg1.h=SCREEN_HEIGHT;

											bg2.x=0;
											bg2.y=scrollingOffset;
											bg2.w=SCREEN_WIDTH;
					                        bg2.h=SCREEN_HEIGHT;//- scrollingOffset;


					//Clear screen
					//SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear( gRenderer );
					SDL_RenderCopy( gRenderer, gBGTexture, NULL, &bg1 );
					SDL_RenderCopy( gRenderer, gBGTexture, NULL, &bg2 );

					//Apply the image(bike)
					for(int k=0;k<5;k++)
					{
						SDL_RenderCopy( gRenderer, gCARTexture[k], NULL,&car[k]);
					}
					SDL_RenderCopy( gRenderer, glifeTexture, NULL,&life);
					SDL_RenderCopy( gRenderer, glife1Texture, NULL,&life1);
					SDL_RenderCopy( gRenderer, gboyTexture, NULL,&boy);
                    SDL_RenderCopy( gRenderer, gcoinTexture, NULL,&coin);
					SDL_RenderCopy( gRenderer, gcoin1Texture, NULL,&coin1);

					printf(" LIFE  = %d\n", score);
					printf(" Coin = %d\n", night);
					printf("Run Time  = %d\n", Final);
					total = score + Final+night;
					printf("Final SCORE = %d\n",total);
					strcpy(drr, "Your Score: ");
					_itoa(total, crr);
					printf("%s\n",crr);
					strcat(drr, crr);
					strcpy(frr, "Life: ");
					_itoa(score, err);
					printf("%s\n",err);
					strcat(frr,err);
					strcpy(hrr, "Runtime: ");
					_itoa(Final, grr);
					printf("%s\n",grr);
					strcat(hrr,grr);
					strcpy(mrr, "Coin: ");
					_itoa(night, nrr);
					printf("%s\n",nrr);;
					strcat(mrr,nrr);


					SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, drr, Black);
					SDL_Texture * Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
					if (Message == NULL)
					{
						printf("Unable to load text texture\n");
					}

					SDL_Rect Message_rect;

					Message_rect.x = 950;
					Message_rect.y = 70;
					Message_rect.w = 120;
					Message_rect.h = 30;

					SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);


					SDL_Surface *surfaceMessage2 = TTF_RenderText_Solid(Sans, frr, Black);
					SDL_Texture * Message2 = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage2);
					if (Message2 == NULL)
					{
						printf("Unable to load text texture\n");
					}

					SDL_Rect Message_rect2;

					Message_rect2.x = 45;
					Message_rect2.y = 90;
					Message_rect2.w = 100;
					Message_rect2.h = 30;

					SDL_RenderCopy(gRenderer, Message2, NULL, &Message_rect2);

					SDL_Surface *surfaceMessage3 = TTF_RenderText_Solid(Sans, hrr, Black);
					SDL_Texture * Message3 = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage3);
					if (Message3 == NULL)
					{
						printf("Unable to load text texture\n");
					}

					SDL_Rect Message_rect3;
                    Message_rect3.x = 45;
					Message_rect3.y = 60;
					Message_rect3.w = 100;
					Message_rect3.h = 30;
					SDL_RenderCopy(gRenderer, Message3, NULL, &Message_rect3);

					SDL_Surface *surfaceMessage4 = TTF_RenderText_Solid(Sans, mrr, Black);
					SDL_Texture * Message4 = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage4);
					if (Message4 == NULL)
					{
						printf("Unable to load text texture\n");
					}

					SDL_Rect Message_rect4;

					Message_rect4.x = 45;
					Message_rect4.y = 120;
					Message_rect4.w = 100;
					Message_rect4.h = 30;

					SDL_RenderCopy(gRenderer, Message4, NULL, &Message_rect4);
					if(gameState == 0) SDL_Delay(2000);
					
					    		//Render_Text(crr);

					//Update screen
					SDL_RenderPresent( gRenderer );
	                //runtime=SDL_GetTicks()-start;
	                
	                }
				//int runtime=SDL_GetTicks()-start;
				//printf("Runtime= %d\n",runtime);
	                
	                if(gameState==2){

                        //
                        FILE* fp=fopen("highscore.txt","r");
	             	     //SDL_Event e;
						while( SDL_PollEvent( &e ) != 0 )
						{
						//User requests quit
							if( e.type == SDL_QUIT )
							{
								gameState=0;
							}
							if(e.key.keysym.sym  == SDLK_RETURN) gameState = 0;
						}


						
						SDL_RenderClear( gRenderer );
						SDL_RenderCopy( gRenderer, ghighscoreTexture, NULL, NULL );
						int i=0;
						char s[100];
						while(i<5)
							{	fscanf(fp, "%s", s);
								SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, s, Black);
								SDL_Texture * Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
								SDL_Rect Message_rect = {120,(i*70)+220, 40, 40};
								SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);
								i++;
							}
							fclose(fp);
					//Update screen
						SDL_RenderPresent( gRenderer );  

	                }

				if(gameState==3)
					{   while( SDL_PollEvent( &e ) != 0 )
						{
						//User requests quit
							if( e.type == SDL_QUIT )
							{
								gameState=0;
							}
							if(e.key.keysym.sym  == SDLK_RETURN) gameState = 0;
						}
						SDL_RenderClear( gRenderer );
						SDL_RenderCopy( gRenderer, ginstructionTexture, NULL, NULL );
					//Update screen
						SDL_RenderPresent( gRenderer );

					}
					if(gameState == 4) { 
						quit=true;
					}
					if(gameState == 5) { 

						higscore(total);
						SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
						SDL_RenderClear( gRenderer );
						//strcpy( drr, "Congratulations ");
						_itoa( total, crr );
						//strcat( drr, crr );

					SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, drr, Black);
					SDL_Texture * Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
					SDL_Rect Message_rect = {SCREEN_WIDTH/4,7*SCREEN_HEIGHT/9, 500, 60};

						SDL_RenderCopy( gRenderer, gGameTexture, NULL, NULL );

                    SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);
                    // SDL_RenderCopy(gRenderer, Message2, NULL, &Message_rect2);
                     //SDL_RenderCopy(gRenderer, Message3, NULL, &Message_rect3);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(2000);
                    gameState = 0;

					}

				}
			}
		}

	//Free resources and close SDL
		close();
		printf("Run Time FOR TOTAL GAME  = %d seconds\n",currentTime/1000);
		/*high = total;
		highscore(high);
		printf("kichu %d",high);
		if(n<high){
			highscore(high);
		}*/
		return 0;
	}
