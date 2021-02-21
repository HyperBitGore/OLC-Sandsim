#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

float target = 1.0f / 60.0f;
float accum = 0.0f;
long timer = 0;
int current = 1;
struct Particle {
	int x;
	int y;
	int type;
	int r;
	int b;
	int g;
};
std::vector<Particle> pars;
class Sand : public olc::PixelGameEngine {
public:
	Sand() {
		sAppName = "Falling Sand";
	}
public:
	bool OnUserCreate() override{
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override {
		accum += fElapsedTime;
		if (accum >= target) {
			accum -= target;
			fElapsedTime = target;
			//Above code limits the frames
			Clear(olc::BLACK);
			timer++;
			for (int i = 0; i < pars.size(); i++) {
				//Grabbing entire window variable into a sprite
				olc::Sprite* name = GetDrawTarget();
				const olc::Pixel b = { 0, 0, 0 };
				//The basic sand sim logic
				switch (pars[i].type) {
				case 1:
					//Sand
					if ((name->GetPixel(pars[i].x, pars[i].y+1)).operator==(b)) {
						pars[i].y++;
					}
					else if ((name->GetPixel(pars[i].x-1, pars[i].y+1)).operator==(b)) {
						pars[i].x--;
						pars[i].y++;
					}
					else if ((name->GetPixel(pars[i].x + 1, pars[i].y + 1)).operator==(b)) {
						pars[i].x++;
						pars[i].y++;
					}
					break;
				case 2:
					//Water
					if ((name->GetPixel(pars[i].x, pars[i].y + 1)).operator==(b)) {
						pars[i].y++;
					}
					else if ((name->GetPixel(pars[i].x - 1, pars[i].y + 1)).operator==(b)) {
						pars[i].x--;
						pars[i].y++;
					}
					else if ((name->GetPixel(pars[i].x + 1, pars[i].y + 1)).operator==(b)) {
						pars[i].x++;
						pars[i].y++;
					}
					else if ((name->GetPixel(pars[i].x + 1, pars[i].y)).operator==(b)) {
						pars[i].x++;
					}
					else if ((name->GetPixel(pars[i].x - 1, pars[i].y)).operator==(b)) {
						pars[i].x--;
					}
					break;
				case 3:
					//Wood


					break;

				}
				//Drawing the pixels
				Draw(pars[i].x, pars[i].y, olc::Pixel(pars[i].r, pars[i].g, pars[i].b));
				
			}
			//Code for when I add more particles
			if (GetKey(olc::R).bHeld && timer % 10 == 0) {
				if (current == 3) {
					current = 1;
				}
				else {
					current++;
				}
			}
			int mx = GetMouseX();
			int my = GetMouseY();
			FillRect(mx, my, 10, 10, olc::GREEN);
			//Particle creation
			if (GetMouse(0).bHeld && timer % 5 == 0) {
				Particle p;
				p.x = mx;
				p.y = my;
				p.type = current;
				switch (current) {
				case 1:
					p.r = 255;
					p.g = 255;
					p.b = 0;
					break;
				case 2:
					p.r = 0;
					p.g = 128;
					p.b = 255;
					break;
				case 3:
					p.r = 73;
					p.g = 20;
					p.b = 20;
					break;
				}
				pars.push_back(p);
			}
			std::string cur = "Current type: " + std::to_string(current);
			DrawString(10, 10, cur);

			return true;
		}
		else {
			return true;
		}
		
	}


};

int main() {
	srand(time(NULL));
	Sand s;
	if (s.Construct(800, 900, 1, 1)) {
		s.Start();
	}
	return 0;
}