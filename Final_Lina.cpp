#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include "cmfunc.h"
#include "object.h"
void initE(class Enemy epl[], int n)
{
	for (int i = 1; i <= 10; i++)
	{
		epl[i].rect_.y = -150;
		epl[i].rect_.x = i * 80 + 50;
		epl[i].pos = 100;
		epl[i].hp = 100;
	}
	if (n > 10)
		for (int i = 11; i <= 20; i++)
		{
			epl[i].rect_.y = -100;
			epl[i].rect_.x = (i - 10) * 80 + 50;
			epl[i].pos = 150;
			epl[i].hp = 100;
		}
	if (n > 20)
		for (int i = 21; i <= 30; i++)
		{
			epl[i].rect_.y = -50;
			epl[i].rect_.x = (i - 20) * 80 + 50;
			epl[i].pos = 200;
			epl[i].hp = 100;
		}
}
SDL_Texture* createMessage(SDL_Color color, const char* mess, TTF_Font* font)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, mess, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	return texture;
}
int main(int argc, char* argv[])
{
	FreeConsole();
	cmfunc::initSDL(window, renderer);
	TTF_Font* sans = TTF_OpenFont("sans.ttf", 72);
	TTF_Font* myriad = TTF_OpenFont("myriad.ttf",144);
	SDL_Color navy = { 102, 102, 255 };
	SDL_Color blue = { 51,255,51 };
	Mix_Music* bgm = Mix_LoadMUS("bgm.mp3");
	Mix_Music* wry = Mix_LoadMUS("wry.mp3");
	Mix_Music* coffin = Mix_LoadMUS("coffin.mp3");
	Mix_Music* vic = Mix_LoadMUS("speciallist.mp3");
	int xx, yy;

	SDL_Texture* fbg = cmfunc::loadTexture(renderer, "fbg.jpg");
	Text first_text;
	first_text.texture_ = createMessage(navy, "Press to join the battle", myriad);
	first_text.texture = createMessage(blue, "Press to join the battle", myriad);
	first_text.rect.w = 600;
	first_text.rect.h = 100;
	first_text.rect.y = SCREEN_HEIGHT - first_text.rect.h;
	first_text.rect.x = (SCREEN_WIDTH - first_text.rect.w) / 2;
	int sw = 30, d = -1;
	SDL_Event event;
	bool quit = false;

	SDL_Texture* l_credit = cmfunc::loadTexture(renderer,"lose_credit_1.png");
	SDL_Texture* v_credit = cmfunc::loadTexture(renderer, "vic_credit_1.png");
	SDL_Texture* guide = cmfunc::loadTexture(renderer, "guide.png");

	SDL_Texture* background = cmfunc::loadTexture(renderer, "bg.png");
	Character lina;
	lina.texture_ = cmfunc::loadTexture(renderer, "ship.png");
	lina.rect_.h = 100; lina.rect_.w = 50;
	SDL_Texture* bullet = cmfunc::loadTexture(renderer, "bullet.png");
	Mix_Chunk* shoot = Mix_LoadWAV("shoot.wav");
	Mix_Chunk* A = Mix_LoadWAV("speA.wav");
	Mix_Chunk* beam = Mix_LoadWAV("lina.wav");
	Mix_Chunk* pre = Mix_LoadWAV("pre_shoot.wav");
	Mix_Music* die = Mix_LoadMUS("end_eff.mp3");
	Mix_Chunk* die_d = Mix_LoadWAV("die_dd.wav");
	bool speA = false;
	bool metalB = false;
	bool pre_s = true;
	quit = false;
	int A_cd = 0;
	lina.initN();

	Text cbullet;
	cbullet.rect.x = 158;
	cbullet.rect.y = SCREEN_HEIGHT - 25;
	cbullet.rect.h = 14;
	std::string ss;
	const char* s;

	Text railgun_cd;
	railgun_cd.rect.x = 290;
	railgun_cd.rect.y = SCREEN_HEIGHT - 25;
	railgun_cd.rect.h = 14;

	Bullet f[2][31];
	for (int i = 0; i <= 1; i++)
		for (int j = 1; j <= 30; j++)
		{
			f[i][j].sp = 16;
			f[i][j].init();
			f[i][j].texture_ = bullet;
		}
	int j = 0, b = 0;
	int reload = 0;

	bool move = true;
	bool check = false;
	int num = 10;
	int prod = 1;
	SDL_Texture* eplane = cmfunc::loadTexture(renderer, "enemy.png");
	Enemy epl[31];
	for (int i = 1; i <= 30; i++)
	{
		epl[i].texture_ = eplane;
		epl[i].init();
	}
	SDL_Texture* ebll = cmfunc::loadTexture(renderer, "ebl.png");
	Ebullet ebl[31];
	for (int i = 1; i <= 30; i++)
	{
		ebl[i].texture_ = ebll;
		ebl[i].rect_.w = 5;
		ebl[i].rect_.h = 20;
		ebl[i].rect_.y = SCREEN_HEIGHT;
	}
	int bs = 0;
	int b_cd = 0;
	int fire = 0;
	Mix_Chunk* eshoot = Mix_LoadWAV("eshoot.wav");
	Mix_Chunk* boom = Mix_LoadWAV("boom.wav");

	Boss Dio;
	Mix_Chunk* E1 = Mix_LoadWAV("Dio_Entrance.wav");
	Mix_Chunk* tele = Mix_LoadWAV("tele.wav");
	Dio.time_entrance = 121;
	Dio.intB();
	bool a_ = true;
	int attack;
	Dio_bullet x[6];
	int cd = 20;
	int d_bullet = 0;
	for (int i = 1; i <= 5; i++) x[i].init();
start: 
	while (!quit)
	{
		sw += d;
		if (sw == 0 || sw == 30) d *= -1;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
					SDL_GetMouseState(&xx, &yy);
					if (yy >= 0 && yy <= 100)
						if (xx >= 0 && xx <= 50) goto guide_;

					if (yy >= SCREEN_HEIGHT - first_text.rect.h && xx >= (SCREEN_WIDTH - first_text.rect.w) / 2 && xx <= (SCREEN_WIDTH - first_text.rect.w) / 2 + 600) goto a;
			}
			if (event.type == SDL_QUIT)
			{
				return 1;
			}
		}
		SDL_RenderCopy(renderer, fbg, NULL, NULL);
		if (d == -1) SDL_RenderCopy(renderer, first_text.texture_, NULL, &first_text.rect);
		else SDL_RenderCopy(renderer, first_text.texture, NULL, &first_text.rect);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}

a: 
	initE(epl, 10);
	Mix_PlayMusic(bgm, 10);
	Mix_PlayChannel(3, E1, 0);
	SDL_GetMouseState(&lina.rect_.x, &lina.rect_.y);
	lina.rect_.x -= 25;
	lina.rect_.y -= 50;
	SDL_RenderCopy(renderer, background, NULL, NULL);
	SDL_RenderCopy(renderer, lina.texture_, NULL, &lina.rect_);
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			if (event.type == SDL_MOUSEMOTION)
			{
				SDL_GetMouseState(&lina.rect_.x, &lina.rect_.y);
				lina.rect_.x -= 25;
				lina.rect_.y -= 50;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN && reload <= 0 && speA == false && metalB == false)
			{
				Mix_PlayChannel(-1, shoot, 0);
				b++;
				if (b == 30) reload = 60;
				SDL_GetMouseState(&f[j % 2][b].rect_.x, &f[j % 2][b].rect_.y);
				f[j % 2][b].rect_.x -= 3; f[j % 2][b].rect_.y -= 30;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a && speA == false && metalB == false && A_cd == 0)
			{
				A_cd = 600;
				Mix_PlayChannel(2, A, 0);
				speA = true;
				reload = 0;
				b = 0;
				lina.initA();
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE && metalB == false && speA == false && lina.energy == 100)
			{
				pre_s = true;
				lina.energy = 0;
				Mix_PlayChannel(2, beam, 0);
				metalB = true;
				reload = 0; b = 0;
				lina.initB();
			}
		}

		SDL_RenderCopy(renderer, background, NULL, NULL);
		
		if (Dio.time_entrance > 0) { Dio.call(); Dio.time_entrance--; }
		if (Dio.time_entrance == 1) Dio.call_ = true;
		if (Dio.time_entrance == 0 && Dio.HP > 0)
		{
			Dio.move();
			if (a_ == true) attack = rand() % 300 + 1;
			if (attack == 5)
			{
				a_ = false;
				if (cd == 0)
				{
					Mix_PlayChannel(0, tele, 0);
					cd = 20;
					Dio.tele(lina.rect_.x);
					d_bullet++;
					x[d_bullet].rect_.x = Dio.rect_.x + 100;
					x[d_bullet].rect_.y = Dio.rect_.y + 200;
					if (d_bullet == 5)
					{
						d_bullet = 0;
						a_ = true;
					}
				}
				else cd--;
			}
			if (attack == 7 || attack == 10 || attack == 13)
			{
				Mix_PlayChannel(0, tele, 0); Dio.evade(lina.rect_.x);
			}
		}
		for (int i = 1; i <= 5; i++)
			if (x[i].rect_.y != 0)
			{
				x[i].move();
				if (x[i].rect_.x >= lina.rect_.x && x[i].rect_.x + x[i].rect_.w <= lina.rect_.x + lina.rect_.w)
					if (x[i].rect_.y + x[i].rect_.h <= lina.rect_.y + lina.rect_.h && x[i].rect_.y + x[i].rect_.h >= lina.rect_.y)
					{
						x[i].rect_.y = 0;
						lina.hp -= 50;
					}
			}

		if (lina.rect_.x >= Dio.rect_.x && lina.rect_.x + lina.rect_.w <= Dio.rect_.x + Dio.rect_.w)
			if (lina.rect_.y <= Dio.rect_.y + Dio.rect_.h && lina.rect_.y >= Dio.rect_.y)
				goto f;

		if (move == true) for (int i = 1; i <= 30; i++) if (epl[i].hp > 0) move = epl[i].call();
		if (move == false) 
			for (int i = 1; i <= 30; i++) if (epl[i].hp > 0)
			{
				epl[i].move();
				if (lina.rect_.x <= epl[i].rect_.x + epl[i].rect_.w && lina.rect_.x + lina.rect_.w >= epl[i].rect_.x + epl[i].rect_.w || lina.rect_.x <= epl[i].rect_.x && lina.rect_.x + lina.rect_.w >= epl[i].rect_.x)
					if (lina.rect_.y >= epl[i].rect_.y && lina.rect_.y <= epl[i].rect_.y + epl[i].rect_.h)
						goto f;
			}

		if (move == false && num > 0)
		{

			if (b_cd == 0) fire = rand() % 5 + 1;
			if (fire == 5)
			{
				if (b_cd == 0)
				{
					b_cd = 8;
				cm: int pos = rand() % 30 + 1;
					if (epl[pos].hp <= 0) goto cm;
					bs++;
					ebl[bs].rect_.x = epl[pos].rect_.x + 25;
					ebl[bs].rect_.y = epl[pos].rect_.y + 50;
					if (bs == 30) bs = 0;
					Mix_PlayChannel(1, eshoot, 0);
				}
				else b_cd--;
			}			
		}

		for (int i = 1; i <= 30; i++) 
		{
			if (ebl[i].rect_.y != SCREEN_HEIGHT)
			{
				if (ebl[i].rect_.y + ebl[i].rect_.h <= lina.rect_.y + lina.rect_.h && ebl[i].rect_.y + ebl[i].rect_.h >= lina.rect_.y)
				{
					if (ebl[i].rect_.x >= lina.rect_.x && ebl[i].rect_.x + ebl[i].rect_.w <= lina.rect_.x + lina.rect_.w)
					{
						ebl[i].rect_.y = SCREEN_HEIGHT;
						lina.hp -= ebl[i].dame;
					}
				}
			}
			ebl[i].move();
		}

		if (num == 0 && prod < 3)
		{
			if (Dio.i > 0) Dio.i++;
			else Dio.i--;
			if (Dio.j > 0) Dio.j++;
			else Dio.j--;
			prod++;
			move = true;
			num = 10 * prod;
			initE(epl, num);
		}		

		for (int i = 1; i <= 30; i++)
			if (f[j % 2][i].rect_.y >= 0)
			{
				for (int l = 1; l <= 30; l++)
					if (epl[l].hp > 0)
					{
						if (f[j % 2][i].rect_.y >= epl[l].rect_.y && f[j % 2][i].rect_.y <= epl[l].rect_.y + epl[l].rect_.h && f[j % 2][i].rect_.x >= epl[l].rect_.x && f[j % 2][i].rect_.x + f[j % 2][i].rect_.w <= epl[l].rect_.x + epl[l].rect_.w)
						{
							if (lina.hp <= 95) lina.hp += 5; else lina.hp = 100;
							if (lina.energy < 100) lina.energy++;
							f[j % 2][i].rect_.y = -30;
							epl[l].hp -= f[j % 2][i].dame;
							if (epl[l].hp <= 0) { check = true; num--; if (lina.energy <= 95) lina.energy += 5; else lina.energy = 100; }
							break;
						}
					}
			}

		for (int i = 0; i <= 1; i++)
			for (int l = 1; l <= 30; l++)
				if (f[i][l].rect_.y >= 0) f[i][l].move();

		if (check == true)
		{
			for (int i = 1; i <= 30; i++)
				if (epl[i].hp > 0) epl[i].init();
			check = false;
		}

		if (lina.hp <= 0) { goto f; }

		for (int i = 1; i <= 30; i++)
			if (f[j % 2][i].rect_.y >= 0)
			{
				if (f[j % 2][i].rect_.y <= Dio.rect_.y + Dio.rect_.h && f[j % 2][i].rect_.y >= Dio.rect_.y)
					if (f[j % 2][i].rect_.x >= Dio.rect_.x && f[j % 2][i].rect_.x + f[j % 2][i].rect_.w <= Dio.rect_.x + Dio.rect_.w)
					{
						Dio.HP -= f[j % 2][i].dame;
						if (lina.hp <= 95) lina.hp += 5; else lina.hp = 100;
						if (lina.energy < 100) lina.energy++;
						f[j % 2][i].rect_.y = -1;
					}
			}		

		if (reload > 0) reload--;
		if (reload == 0) { j++; b = 0; reload = -1; }
		if (speA == true)
		{
			if (lina.time > 0) { lina.speA(lina.rect_.x + 10, lina.rect_.y - 550); lina.time--; }
			if (lina.time == 0) speA = false;
			if (lina.time == 90)
			{
				for (int i = 1; i <= 30; i++)
				{
					if (epl[i].hp > 0)
					{
						if (lina.mrect_.x >= epl[i].rect_.x && lina.mrect_.x + lina.mrect_.w <= epl[i].rect_.x + epl[i].rect_.w || lina.mrect_.x <= epl[i].rect_.x && lina.mrect_.x + lina.mrect_.w >= epl[i].rect_.x || lina.mrect_.x <= epl[i].rect_.x + epl[i].rect_.w && lina.mrect_.x + lina.mrect_.w >= epl[i].rect_.x + epl[i].rect_.w)
						{
							if (lina.hp <= 95) lina.hp += 5; else lina.hp = 100;
							epl[i].hp -= lina.Ad;
							check = true;
							if (epl[i].hp <= 0) { num--; if (lina.energy <= 98) lina.energy += 2; else lina.energy = 100; }
						}
					}
					if (ebl[i].rect_.y < SCREEN_HEIGHT)
					{
						if (ebl[i].rect_.x >= lina.mrect_.x && ebl[i].rect_.x + ebl[i].rect_.w <= lina.mrect_.x + lina.mrect_.w)
							ebl[i].rect_.y = SCREEN_HEIGHT;
					}
				}
				if (lina.mrect_.x >= Dio.rect_.x && lina.mrect_.x + lina.mrect_.w <= Dio.rect_.x + Dio.rect_.w || lina.mrect_.x <= Dio.rect_.x && lina.mrect_.x + lina.mrect_.w >= Dio.rect_.x || lina.mrect_.x <= Dio.rect_.x + Dio.rect_.w && lina.mrect_.x + lina.mrect_.w >= Dio.rect_.x + Dio.rect_.w)
				{
					if (lina.hp <= 95) lina.hp += 5; else lina.hp = 100;
					Dio.HP -= lina.Ad;
					check = true;
					if (lina.energy <= 99) lina.energy += 1; else lina.energy = 100;
				}
			}
		}
		if (metalB == true)
		{
			if (lina.time > 380) { lina.premetal(lina.rect_.x + 20, lina.rect_.y + 30); lina.time--; }
			else if (lina.time <= 380 && lina.time > 320) { lina.metalmove(lina.rect_.x - (lina.pprect_.w - 10) / 2 + 20, lina.rect_.y - (lina.pprect_.h - 10) * 2 + 30); lina.time--; }
			else if (lina.time <= 320) { lina.metalB(lina.rect_.x + 9, lina.rect_.y - 595); lina.time--; }
			else lina.time--;
			if (lina.time == 0) metalB = false;
			if (lina.time <= 320)
			{
				if (lina.time == 320) { Dio.evade(lina.rect_.x); Mix_PlayChannel(0, tele, 0); }
				if (lina.mrect_.x >= Dio.rect_.x + 10 && lina.mrect_.x + lina.mrect_.w <= Dio.rect_.x + Dio.rect_.w - 10) Dio.HP -= 5;
				for (int i = 1; i <= 30; i++)
				{
					if (epl[i].hp > 0)
					{
						if (lina.mrect_.x >= epl[i].rect_.x && lina.mrect_.x + lina.mrect_.w <= epl[i].rect_.x + epl[i].rect_.w || lina.mrect_.x <= epl[i].rect_.x && lina.mrect_.x + lina.mrect_.w >= epl[i].rect_.x || lina.mrect_.x <= epl[i].rect_.x + epl[i].rect_.w && lina.mrect_.x + lina.mrect_.w >= epl[i].rect_.x + epl[i].rect_.w)
						{
							if (lina.hp <= 95) lina.hp += 5; else lina.hp = 100;
							epl[i].hp -= 10;
							if (epl[i].hp <= 0) {num--;}
						}
					}
					if (ebl[i].rect_.y < SCREEN_HEIGHT)
					{
						if (ebl[i].rect_.x >= lina.mrect_.x && ebl[i].rect_.x + ebl[i].rect_.w <= lina.mrect_.x + lina.mrect_.w)
							ebl[i].rect_.y = SCREEN_HEIGHT;
					}
				}
				for (int i = 1; i <= 5; i++)
					if (x[i].rect_.y != 0)
					{
						if (x[i].rect_.x >= lina.mrect_.x && x[i].rect_.x + x[i].rect_.w <= lina.mrect_.x + lina.mrect_.w || lina.mrect_.x >= x[i].rect_.x && lina.rect_.x <= x[i].rect_.x + x[i].rect_.w || lina.mrect_.x <= x[i].rect_.x + x[i].rect_.w && lina.rect_.x + lina.mrect_.w >= x[i].rect_.x + x[i].rect_.w)
							x[i].rect_.y = 0;
					}
			}
		}
		if (A_cd > 0) A_cd--;
		if (pre_s == true && lina.energy == 100) { Mix_PlayChannel(4, pre, 0); pre_s = false; }


		SDL_RenderCopy(renderer, lina.texture_, NULL, &lina.rect_);
		lina.notifi();
		ss = std::to_string(30 - b);
		s = ss.c_str();
		cbullet.texture = createMessage(blue, s, myriad);
		if (30 - b <= 9) cbullet.rect.w = 8; else cbullet.rect.w = 16;
		SDL_RenderCopy(renderer, cbullet.texture, NULL, &cbullet.rect);
		ss = std::to_string(600 - A_cd);
		s = ss.c_str();
		railgun_cd.texture = createMessage(blue, s, myriad);
		if (600 - A_cd >= 100) railgun_cd.rect.w = 24;
		else if (600 - A_cd >= 10) railgun_cd.rect.w = 16;
		else railgun_cd.rect.w = 8;
		if (Dio.HP <= 0) goto w;
		SDL_RenderCopy(renderer, railgun_cd.texture, NULL, &railgun_cd.rect);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
w:
	Mix_PlayMusic(die, 0);
	lina.i = 0;
	lina.j = 0;
	lina.time = 600;
	lina.drect.w = 300;
	lina.drect.h = 300;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				return 1;				
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				Mix_Pause(-1);
				//Mix_PauseMusic();
				goto selection_w;
			}
		}

		SDL_RenderCopy(renderer, background, NULL, NULL);
		SDL_RenderCopy(renderer, Dio.texture_, NULL, &Dio.rect_);
		for (int i = 1; i <= 30; i++)
		{
			if (epl[i].hp > 0) SDL_RenderCopy(renderer, epl[i].texture_, NULL, &epl[i].rect_);
			if (f[j % 2][i].rect_.y >= 0) SDL_RenderCopy(renderer, f[j % 2][i].texture_, NULL, &f[j % 2][i].rect_);
			if (ebl[i].rect_.y != SCREEN_HEIGHT) SDL_RenderCopy(renderer, ebl[i].texture_, NULL, &ebl[i].rect_);
		}
		if (speA == true) SDL_RenderCopy(renderer, lina.A, &lina.crect_, &lina.mrect_);
		if (metalB == true && lina.time <= 320) SDL_RenderCopy(renderer, lina.space, &lina.crect_, &lina.mrect_);
		SDL_RenderCopy(renderer, lina.texture_, NULL, &lina.rect_);
		lina.die(Dio.rect_.x, Dio.rect_.y - 50);
		lina.notifi();
		SDL_RenderCopy(renderer, cbullet.texture, NULL, &cbullet.rect);
		SDL_RenderCopy(renderer, railgun_cd.texture, NULL, &railgun_cd.rect);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		if (lina.time == 0) goto selection_w;
	}

f:
	for (int i = -1; i <= 3; i++) Mix_Pause(i);
	Mix_PlayMusic(wry, 0);
	Mix_PlayChannel(6, die_d, 0);
	lina.i = 0;
	lina.j = 0;
	lina.drect.w = 150;
	lina.drect.h = 150;
	lina.time = 300;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				return 1;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				Mix_Pause(-1);
				//Mix_PauseMusic();
				goto selection_l;
			}
		}
		
		SDL_RenderCopy(renderer,background, NULL, NULL);		
		SDL_RenderCopy(renderer, Dio.texture_, NULL, &Dio.rect_);
		for (int i = 1; i <= 30; i++)
		{
			if (epl[i].hp > 0) SDL_RenderCopy(renderer, epl[i].texture_, NULL, &epl[i].rect_);
			if (f[j % 2][i].rect_.y >= 0) SDL_RenderCopy(renderer, f[j % 2][i].texture_, NULL, &f[j % 2][i].rect_);
			if (ebl[i].rect_.y != SCREEN_HEIGHT) SDL_RenderCopy(renderer, ebl[i].texture_, NULL, &ebl[i].rect_);
		}
		if (speA == true) SDL_RenderCopy(renderer, lina.A, &lina.crect_, &lina.mrect_);
		if (metalB == true) SDL_RenderCopy(renderer, lina.space, &lina.crect_, &lina.mrect_);
		SDL_RenderCopy(renderer, lina.texture_, NULL, &lina.rect_);
		lina.die(lina.rect_.x, lina.rect_.y);
		lina.notifi();
		SDL_RenderCopy(renderer, cbullet.texture, NULL, &cbullet.rect);
		SDL_RenderCopy(renderer, railgun_cd.texture, NULL, &railgun_cd.rect);		
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		if (lina.time == 0) 
		{
			Mix_Pause(-1);
			Mix_PauseMusic();
			goto selection_l;
		}
	}
selection_l:
	Mix_PlayMusic(coffin, 0);
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				return 1;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_GetMouseState(&xx, &yy);
				if (yy >= 500)
				{
					if (xx <= 350 && xx >= 150)
					{						
						lina.hp = 100;
						lina.energy = 0;
						b = 0;
						A_cd = 0;
						speA = false;
						metalB = false;
						pre_s = true;
						j = 0;
						reload = 0;
						for (int i = 0; i <= 1; i++)
							for (int j = 1; j <= 30; j++)
								f[i][j].init();

						bs = 0;
						move = true;
						check = false;
						num = 10;
						prod = 1;
						Dio.HP = 4000;
						Dio.intB();
						Dio.time_entrance = 121;
						a_ = true;
						cd = 20;
						d_bullet = 0;
						for (int i = 1; i <= 5; i++) x[i].init();
						for (int i = 1; i <= 30; i++) {ebl[i].rect_.y = SCREEN_HEIGHT; epl[i].hp = 0;}
						Mix_PauseMusic();

						goto a;
					}
					if (xx >= 650 && xx <= 1000) return 0;
				}

			}
		}
		SDL_RenderCopy(renderer, l_credit, NULL, NULL);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
selection_w:
	Mix_PlayMusic(vic, 0);
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				return 1;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_GetMouseState(&xx, &yy);
				if (yy >= 500)
				{
					if (xx <= 600 && xx >= 50)
					{
						lina.hp = 100;
						lina.energy = 0;
						b = 0;
						A_cd = 0;
						speA = false;
						metalB = false;
						pre_s = true;
						j = 0;
						reload = 0;
						for (int i = 0; i <= 1; i++)
							for (int j = 1; j <= 30; j++)
								f[i][j].init();

						bs = 0;
						move = true;
						check = false;
						num = 10;
						prod = 1;
						Dio.HP = 4000;
						Dio.intB();
						Dio.time_entrance = 121;
						a_ = true;
						cd = 20;
						d_bullet = 0;
						for (int i = 1; i <= 5; i++) x[i].init();
						for (int i = 1; i <= 30; i++) { ebl[i].rect_.y = SCREEN_HEIGHT; epl[i].hp = 0; }

						Mix_PauseMusic();

						goto a;
					}
					if (xx >= 700 && xx <= 1000) return 0;
				}

			}
		}
		SDL_RenderCopy(renderer, v_credit, NULL, NULL);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
guide_:

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) return 1;
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_GetMouseState(&xx, &yy);
				if (yy >= 20 && yy <= 100)
					if (xx >= 20 && xx <= 120) goto start;
			}
		}
		SDL_RenderCopy(renderer, guide, NULL, NULL);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}

    return 0;
}