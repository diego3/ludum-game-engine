#pragma once

#include "../Core/Game.h"
#include "../Core/Component.h"


class MouseControlComponent : public Component {

public:
	bool isMouseButtonPressed;
	MouseControlComponent() {
		isMouseButtonPressed = false;
	}

	void Initialize() override {

	}

	void Update(float deltaTime) override {

	}

	void Render() override {
		// TODO CHALENGE: draw a line from mousedown position until mouseup position

		/* pasted from transform component, just in case
			SDL_Rect rectangle = {
				(int)position.x,
				(int)position.y,
				width, height
			};

			SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(Game::renderer, &rectangle);
		*/

		SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);

		// acho q precisa de 4 linhas que devem ser desenhadas
		// ao mesmo tempo mas cada uma em sua direção e posição
		// duas pra direita e duas na vertical
		// *------    |     |
		//			  |		|	
		//  ------	  |		|
		// 
		
		int x1 = 0;
		int x2 = 0;
		int y1 = 0;
		int y2 = 0;
		SDL_RenderDrawLine(Game::renderer, x1, y1, x2, y2);
	}
};

/*


case SDL_MOUSEBUTTONDOWN:
		{
			if (event.button.button == SDL_BUTTON_LEFT
				&& event.button.state == SDL_PRESSED) {
				IS_MOUSE_PRESSED = true;
				std::cout << "x[" << event.button.x
					<< "]y[" << event.button.y << "]" << std::endl;
			}
		}
		case SDL_MOUSEBUTTONUP:
		{
			if (event.button.button == SDL_BUTTON_LEFT
				&& event.button.state == SDL_RELEASED) {
				std::cout << "button UP" << std::endl;
				IS_MOUSE_PRESSED = false;
			}
		}
		case SDL_MOUSEMOTION:
		{
			if (IS_MOUSE_PRESSED) {
				std::cout << "paiting x[" << event.button.x
					<< "]y[" << event.button.y << "]" << std::endl;
			}
		}


*/