--[[

	Game engine features
	 - permitir uma entity anexada à outra
	 - usar spatial partition nas colis�es  https://gameprogrammingpatterns.com/spatial-partition.html
	 - Melhorar o algoritmo que percorre as entities por layer (est� O(n) )
	 - adicionar novos tipos de colis�es (circle collision .....)
	 - integrar uma physics engine (Box2D talvez, ver se existem outras)
	 - manter o aspect ratio (o radar descola do top right quando outros tamanhos de tela)
	 - adicionar components de audio (efeitos e background music)
	 - implementar event queue https://gameprogrammingpatterns.com/event-queue.html
	 - permitir usar LuaScriptComponent para cuidar das l�gicas de gameplay, AI etc
	 - implementar components de Networking (SDL_Net)
	 - tile editor 
	 - camera shake
	 - melhorar sistema de animations (permitir animar todas as sprites linha x coluna e n�o somente linha)
	 - Game Editor (permitir construir as cenas e gravar em scripts lua)
	 - como fazer algo parecido com Prefabs da Unity? a ideia seria reaproveitar a entity j� carregada na memoria
	   talvez usar o prototype?  https://gameprogrammingpatterns.com/prototype.html
	 - State Machine para o game (gameover, menus, telas, transi��es etc)
	 - 3D Game Engine ( estudos em OpenGL )
]]

-- oop em lua

function divisores(num) 
	for i = 1, num, 1 do
		if num % i == 0 then
			print(i, " ", num/i)
		end
	end
end

divisores(1024)
