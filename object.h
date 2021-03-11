#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "cmfunc.h"
class Character
{
public:
	SDL_Texture* texture_;
	SDL_Rect rect_;
	int sp, energy = 0;
	int hp = 100;

	int i, j, time, pb, Ad = 200;
	SDL_Rect mrect_;
	SDL_Rect crect_;
	SDL_Rect prect_;
	SDL_Rect pprect_;
	SDL_Texture* A = cmfunc::loadTexture(renderer, "beam1.png");
	SDL_Texture* space = cmfunc::loadTexture(renderer, "linabeam.png");
	SDL_Texture* premetalB = cmfunc::loadTexture(renderer, "prebeam.png");
	SDL_Texture* noti = cmfunc::loadTexture(renderer, "noti.png");
	SDL_Rect nrect;
	SDL_Texture* hbar = cmfunc::loadTexture(renderer, "HP.png");
	SDL_Rect hrect;
	SDL_Rect hcrect;
	SDL_Texture* ebar = cmfunc::loadTexture(renderer, "energy.png");
	SDL_Rect erect;
	SDL_Rect ecrect;
	SDL_Texture* death = cmfunc::loadTexture(renderer, "end_eff.png");
	SDL_Rect drect;
	SDL_Rect dcrect;

	void initN()
	{
		nrect.x = -2;
		nrect.y = SCREEN_HEIGHT - 104;
		nrect.w = 334;
		nrect.h = 104;
		hrect.x = 124;
		hrect.y = nrect.y + 9;
		hrect.h = 10;
		hcrect.x = 0;
		hcrect.y = 0;
		hcrect.h = 10;
		erect.x = 109;
		erect.y = hrect.y + 19;
		erect.h = 36;
		ecrect.x = 0;
		ecrect.y = 0;
		ecrect.h = 78;
		drect.w = 150;
		drect.h = 150;
		dcrect.w = 330;
		dcrect.h = 330;
	}
	void notifi()
	{
		hcrect.w = hp;
		hrect.w = hp * 2;
		erect.w = energy * 2;
		ecrect.w = energy * 4;
		SDL_RenderCopy(renderer, noti, NULL,&nrect);
		SDL_RenderCopy(renderer, hbar, &hcrect, &hrect);
		SDL_RenderCopy(renderer, ebar, &ecrect, &erect); 
	} 

	void initA()
	{
		time = 180;
		i = 0;
		j = 0;
		crect_.w = 200;
		crect_.h = 500;
		mrect_.w = 30;
		mrect_.h = 600;
	}
	void speA(int x, int y)
	{
		mrect_.x = x;
		mrect_.y = y;
		if (time % 3 == 0)
		{
			crect_.x = i * 200;
			crect_.y = j * 500;
			i++;
			if (i == 5) { i = 0; j++; }
		}
		SDL_RenderCopy(renderer, A, &crect_, &mrect_);
	}

	void initB()
	{
		time = 600;
		i = 0;
		j = 0;
		crect_.w = 308;
		crect_.h = 900;
		mrect_.w = 30;
		mrect_.h = 700;
		pb = 0;
		prect_.w = 900;
		prect_.h = 900;
		prect_.y = 0;
		pprect_.w = 10;
		pprect_.h = 10;
	}
	void metalB(int x, int y)
	{
		mrect_.x = x;
		mrect_.y = y;
		if (time % 2 == 0)
		{
			crect_.x = i * 308;
			crect_.y = j * 900;
			i++;
			if (i == 4) { i = 0; j++; }
			if (j == 4) j = 0;
		}
		SDL_RenderCopy(renderer, space, &crect_, &mrect_);
	}
	void metalmove(int x, int y)
	{
		pprect_.x = x;
		pprect_.y = y;
		if (time % 3 == 0)
		{
			pprect_.w++;
			pprect_.h++;
		}
		prect_.x = pb * 900;
		pb++;
		if (pb == 3) pb = 0;
		SDL_RenderCopy(renderer, premetalB, &prect_, &pprect_);
	}
	void premetal(int x, int y)
	{
		pprect_.x = x;
		pprect_.y = y;
		prect_.x = pb * 900;
		pb++;
		if (pb == 3) pb = 0;
		SDL_RenderCopy(renderer, premetalB, &prect_, &pprect_);
	}
	void die(int x,int y)
	{
		drect.x = x - 50;
		drect.y = y - 40;
		if (time % 6 == 0)
		{
			time--;			
			dcrect.x = i * 330;
			dcrect.y = j * 330;
			i++;
			if (i == 3)
			{
				i = 0;
				j++;
			}
			if (j == 3)
			{
				j = 0;
				i = 0;
			}
		}
		time--;
		SDL_RenderCopy(renderer, death, &dcrect, &drect);
	}
};
class Bullet
{
public:
	SDL_Texture* texture_;
	SDL_Rect rect_;
	int sp = 1;
	int dame = 20;
	void init()
	{
		rect_.y = -30;
		rect_.w = 5;
		rect_.h = 20;
	}
	void move()
	{
		rect_.y -= sp;
		SDL_RenderCopy(renderer, texture_, NULL, &rect_);
	}
};
class Enemy
{
public:
	SDL_Texture* texture_;
	SDL_Rect rect_;
	SDL_Texture* bullet = cmfunc::loadTexture(renderer,"ebl.png");
	SDL_Rect rect;
	bool back = true;
	int hp;
	int i = 1, j = 1, time = 0, r, pos, rx;
	void init()
	{
		r = rand() % 5 + 4;
		rx = rand() % 2 + 1;
		if (rx == 2)
		{
			if (i > 0) i = r; else i = -r;
			if (j > 0) j = r; else j = -r;
		}
		else
		{
			if (i > 0) i = -r; else i = r;
			if (j > 0) j = -r; else j = r;
		}
		rect_.w = 50;
		rect_.h = 50;
		rect.w = 5;
		rect.h = 20;
		rect.y = SCREEN_HEIGHT;
	}
	void attack()
	{
		rect.y += 10;
		SDL_RenderCopy(renderer, bullet, NULL, &rect);
	}
	bool call()
	{
		if (rect_.y < pos) { rect_.y += 5; SDL_RenderCopy(renderer, texture_, NULL, &rect_); return true; }
		return false;
	}
	void move()
	{
		rect_.x += i;
		rect_.y += j;
		if (rect_.x <= 0 || rect_.x + rect_.w >= SCREEN_WIDTH)
		{
			while (rect_.x < 0) rect_.x++;
			while (rect_.x + rect_.w > SCREEN_WIDTH) rect_.x--;
			i *= -1;
		}
		if (rect_.y <= 0 || rect_.y + rect_.h >= 300)
		{
			while (rect_.y < 0) rect_.y++;
			while (rect_.y + rect_.h > 300) rect_.y--;
			j *= -1;
		}
		SDL_RenderCopy(renderer, texture_, NULL, &rect_);
	}
};
class Ebullet
{
public:
	SDL_Texture* texture_;
	SDL_Rect rect_;
	int dame = 20;
	void move()
	{
		rect_.y += 10;
		SDL_RenderCopy(renderer, texture_, NULL, &rect_);
	}
};
class Boss
{
public:
	SDL_Texture* texture_ = cmfunc::loadTexture(renderer, "final_dio.png");
	SDL_Rect rect_;
	int i, j, time_entrance,rx,t;
	int HP = 4000;
	bool command, call_;
	void intB()
	{
		rect_.x = 400;
		rect_.y = -200;
		rect_.w = 200;
		rect_.h = 200;
		i = rand() % 5 + 3;
		j = rand() % 3 + 1;
	}
	void call()
	{
		rect_.y += 2;
		SDL_RenderCopy(renderer, texture_, NULL, &rect_);
	}
	void move()
	{
		rect_.x += i;
		rect_.y += j;
		if (rect_.x <= 0 || rect_.x + rect_.w >= SCREEN_WIDTH)
		{
			while (rect_.x < 0) rect_.x++;
			while (rect_.x + rect_.w > SCREEN_WIDTH) rect_.x--;
			i *= -1;
		}
		if (rect_.y <= 0 || rect_.y + rect_.h >= 300)
		{
			while (rect_.y < 0) rect_.y++;
			while (rect_.y + rect_.h > 300) rect_.y--;
			j *= -1;
		}
		SDL_RenderCopy(renderer, texture_, NULL, &rect_);
	}
	void tele(int x)
	{
		i *= -1;
		j *= -1;
		rect_.x = x - 100;
		SDL_RenderCopy(renderer, texture_, NULL, &rect_);
	}
	void evade(int x)
	{
		i *= -1;
		j *= -1;
		rx = rand()%2 + 1;
		t = rand() % 300 + 100;
		if (rx == 2) rect_.x = SCREEN_WIDTH/2 - t;
		else rect_.x = SCREEN_WIDTH/2 + t;
		SDL_RenderCopy(renderer, texture_, NULL, &rect_);
	}
	void attack()
	{

	}
};
class Text
{
public:
	SDL_Texture* texture_;
	SDL_Texture* texture;
	SDL_Rect rect;
};
class Dio_bullet
{
public:
	SDL_Texture* texture_ = cmfunc::loadTexture(renderer, "Dio_5.png");
	SDL_Rect rect_;
	void init()
	{
		rect_.w = 20;
		rect_.h = 50;
		rect_.y = 0;
	}
	void move()
	{
		rect_.y += 10;
		SDL_RenderCopy(renderer, texture_, NULL, &rect_);
	}
};