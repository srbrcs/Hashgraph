#include "Hashgraphs.hpp"
#define W 1000
#define H 1400
#define GAP 10

int runTime = 1;
int testingNum = 1000;
SDL_Window *win;
SDL_Renderer *rend;
SDL_Texture* p1;
SDL_Texture* p2;
SDL_Texture* p3;
SDL_Texture* p4;
SDL_Texture* p5;
SDL_Texture* p6;
SDL_Event event;
std::array<Person*, N> people;
bool stop = 0;
int personShown;

void square(Event *e)
{
	SDL_Rect rect;
	int y = (runTime - e->getData().timestamp) * GAP;
	int x = 100 + e->getOwner() * (W - 200) / (N - 1);
	if (e->getFamous() == 1)
		SDL_SetRenderDrawColor(rend, 247, 185, 0, 255);
	else if (e->getFamous() == 0)
		SDL_SetRenderDrawColor(rend, 130, 130, 130, 255);
	else if (e->getWitness() == 1)
		SDL_SetRenderDrawColor(rend, 163, 0, 0, 255);
	else
		SDL_SetRenderDrawColor(rend, 9, 71, 124, 255);
	rect.w = 10;
	rect.h = 10;
	rect.x = x - 5;
	rect.y = y - 5;
	SDL_RenderFillRect(rend, &rect);
}

void connect(Event *e, Event *p)
{
	int y = (runTime - e->getData().timestamp) * GAP;
	int x = 100 + e->getOwner() * (W - 200) / (N - 1);
	int y2 = (runTime - p->getData().timestamp) * GAP;
	int x2 = 100 + p->getOwner() * (W - 200) / (N - 1);
	SDL_RenderDrawLine(rend, x, y, x2, y2);
	SDL_RenderDrawLine(rend, x, y - 1, x2, y2 - 1);
	SDL_RenderDrawLine(rend, x - 1, y, x2 - 1, y2);
}

void refresh(Person *p)
{
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
	SDL_RenderFillRect(rend, NULL);
	SDL_SetRenderDrawColor(rend, 220, 220, 220, 255);
	for (int i = 0; i < N; i++)
		SDL_RenderDrawLine(rend, 100 + i * (W - 200) / (N - 1), 0, 100 + i * (W - 200) / (N - 1), H);
	for (unsigned int i = 0; i < (p->getHashgraph())->size(); i++)
	{
		if ((runTime - ((*(p->getHashgraph()))[i])->getData().timestamp) * GAP > H)
			continue ;
		SDL_SetRenderDrawColor(rend, 200, 200, 200, 255);
		if ((*(p->getHashgraph()))[i]->getSelfParent())
		{
			connect((*(p->getHashgraph()))[i], ((*(p->getHashgraph()))[i])->getSelfParent());
			connect((*(p->getHashgraph()))[i], ((*(p->getHashgraph()))[i])->getGossiperParent());
		}
	}
	for (unsigned int i = 0; i < (p->getHashgraph())->size(); i++)
	{
		if ((runTime - ((*(p->getHashgraph()))[i])->getData().timestamp) * GAP > H)
			continue ;
		square((*(p->getHashgraph()))[i]);
	}
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
	SDL_Rect rect;
	rect.w = W;
	rect.h = (W - 400) / (N - 1) + 20;
	rect.x = 0;
	rect.y = H - rect.h;
	SDL_RenderFillRect(rend, &rect);

	rect.w = (W - 400) / (N - 1);
	rect.h = (W - 400) / (N - 1);
	rect.x = 100 - rect.w / 2;
	SDL_RenderCopy(rend, p1, NULL, &rect);
	rect.x += (W - 200) / (N - 1);
	SDL_RenderCopy(rend, p2, NULL, &rect);
	rect.x += (W - 200) / (N - 1);
	SDL_RenderCopy(rend, p3, NULL, &rect);
	rect.x += (W - 200) / (N - 1);
	SDL_RenderCopy(rend, p4, NULL, &rect);
	rect.x += (W - 200) / (N - 1);
	SDL_RenderCopy(rend, p5, NULL, &rect);
	rect.x += (W - 200) / (N - 1);
	SDL_RenderCopy(rend, p6, NULL, &rect);
	SDL_RenderPresent(rend);
	// runTime++;
	// sleep(1);
}

int main(){
	auto t_start = std::chrono::high_resolution_clock::now();
	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO);
	win = SDL_CreateWindow("Hashgraph", 1600, 0, W, H, SDL_WINDOW_SHOWN);
	rend = SDL_CreateRenderer(win, -1, 0);
	SDL_Surface *tmpSurf;
	tmpSurf = SDL_LoadBMP("ponies/1.bmp");
	p1 = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("ponies/2.bmp");
	p2 = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("ponies/3.bmp");
	p3 = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("ponies/4.bmp");
	p4 = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("ponies/5.bmp");
	p5 = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("ponies/6.bmp");
	p6 = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	for (int i = 0; i < N; i++)
		people[i] = new Person(i);
	// people[1]->gossip(*(people[3]));
	// refresh(people[1]);
	// people[3]->gossip(*(people[1]));
	// refresh(people[1]);
	// people[1]->gossip(*(people[3]));
	// refresh(people[1]);
	// people[1]->gossip(*(people[0]));
	// refresh(people[1]);
	// people[2]->gossip(*(people[1]));
	// refresh(people[1]);
	// people[1]->gossip(*(people[3]));
	// refresh(people[1]);
	// people[1]->gossip(*(people[2]));
	// refresh(people[1]);
	// people[3]->gossip(*(people[1]));
	// refresh(people[1]);
	// people[0]->gossip(*(people[3]));
	// refresh(people[1]);
	// people[3]->gossip(*(people[0]));
	// refresh(people[1]);
	// people[3]->gossip(*(people[1]));
	// refresh(people[1]);
	// people[2]->gossip(*(people[0]));
	// refresh(people[1]);
	// people[1]->gossip(*(people[3]));
	// refresh(people[1]);
	// people[0]->gossip(*(people[2]));
	// refresh(people[1]);
	// people[1]->gossip(*(people[0]));
	// refresh(people[1]);
	// people[0]->gossip(*(people[3]));
	// refresh(people[1]);
	// people[0]->gossip(*(people[1]));
	// refresh(people[1]);
	// people[3]->gossip(*(people[1]));
	// refresh(people[1]);
	// people[1]->gossip(*(people[3]));
	// refresh(people[1]);
	// people[1]->gossip(*(people[0]));
	// refresh(people[1]);
	// people[0]->gossip(*(people[1]));
	// refresh(people[1]);
	// people[2]->gossip(*(people[3]));
	// refresh(people[1]);
	// people[3]->gossip(*(people[2]));
	// refresh(people[1]);
	// people[1]->gossip(*(people[0]));
	// refresh(people[1]);
	// people[3]->gossip(*(people[1]));
	// refresh(people[1]);
	// people[1]->gossip(*(people[0]));
	// refresh(people[1]);
	// people[1]->gossip(*(people[3]));
	// refresh(people[1]);
	// people[0]->gossip(*(people[1]));
	// refresh(people[1]);
	// people[2]->gossip(*(people[3]));
	// refresh(people[1]);
	// people[3]->gossip(*(people[1]));
	// refresh(people[1]);
	// while (1)
	// 	;
	personShown = 1;
	runTime++;
	while (1)
	{
		while (SDL_PollEvent(&event))
		{
		    if (event.type == SDL_KEYDOWN || event.type == SDL_QUIT)
		    {
		        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
		            exit (1);
		        if (event.key.keysym.sym == SDLK_SPACE)
		            stop = !stop;
		        if (event.key.keysym.sym == SDLK_1)
		        	personShown = 0;
		        if (event.key.keysym.sym == SDLK_2)
		        	personShown = 1;
		        if (event.key.keysym.sym == SDLK_3)
		        	personShown = 2;
		        if (event.key.keysym.sym == SDLK_4)
		        	personShown = 3;
				refresh(people[personShown]);
		    }
		}
		if (stop)
			continue ;
		int i = std::rand() % N;
		int j;
		while ((j = std::rand() % N) == i)
			;
		people[i]->gossip(*(people[j]));
		refresh(people[personShown]);
		runTime++;
	}
}
