# makefile

GXX=g++
# Les librairies utilisées sont celles compatibles avec SDL 1.2

# Si necessaire mettre le chemin jusqu'aux headers :
# -I/path/to/header/directory SDL/SDL.h
# -I/path/to/header/directory SDL/SDL_ttf.h
# -I/path/to/header/directory SDL/SDL_image.h
# et si ca ne suffit pas :
# -I/path/to/header SDL.h pour SDL_image.h
# Sinon laissez la variable vide
HEADPATH=-I/opt/homebrew/Cellar/sdl/1.2.15_3/include/SDL -I/opt/homebrew/Cellar/sdl/1.2.15_3/include -I/opt/homebrew/Cellar/sdl_image/1.2.12_7/include -I/opt/homebrew/Cellar/sdl_ttf/2.0.11_1/include
# Ne changez pas cette variable
CFLAGS=-Wall $(HEADPATH) -c

# Si necessaire mettre le chemin jusqu'aux librairies :
# -L/path/to/library libSDL.a et libSDLmain.a
# -L/path/to/library libSDL_image.a
# -L/path/to/library libSDL_ttf.a
# Sous mac, ajouter les frameworks pour libSDLmain :
# -framework Foundation -framework Cocoa
# Sinon laissez la variable vide
LIBPATH=-L/opt/homebrew/Cellar/sdl/1.2.15_3/lib -L/opt/homebrew/Cellar/sdl_image/1.2.12_7/lib -L/opt/homebrew/Cellar/sdl_ttf/2.0.11_1/lib -framework Foundation -framework Cocoa
# Ne changez cette variable que si la syntaxe est incorrecte
LDFLAGS=-Wall $(LIBPATH) -lSDL -lSDLmain -lSDL_image -lSDL_ttf -o

# Ne touchez pas au reste
DEL=rm -f

SOURCES=main.cpp CApp.cpp CApp_OnCleanup.cpp CApp_OnEvent.cpp CApp_OnInit.cpp CApp_OnLoop.cpp CApp_OnRender.cpp CSurface.cpp CEvent.cpp CAnimation.cpp CEntity.cpp CArea.cpp CMap.cpp CTile.cpp CCamera.cpp CEntityCol.cpp CFPS.cpp CPlayer.cpp CApp_Text.cpp CTimer.cpp CPokimac.cpp CHouse.cpp CMenu.cpp CBattle.cpp CRand.cpp CVFX.cpp
OBJECTS=$(SOURCES:.cpp=.o)

HEADERS=CApp.h CSurface.hpp CEvent.hpp CAnimation.hpp CEntity.hpp Define.h CArea.hpp CMap.hpp CTile.hpp CCamera.hpp CFPS.hpp CPlayer.hpp CTimer.hpp CPokimac.hpp CHouse.hpp CMenu.hpp CBattle.hpp CVFX.hpp

EXECUTABLE=Pokimac

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE):	$(OBJECTS)
	$(GXX) $(LDFLAGS) $@ $^

main.o: main.cpp $(HEADERS)
	$(GXX) $(CFLAGS) $<

%.o: %.cpp $(HEADERS)
	$(GXX) $(CFLAGS) $<

clean:
	$(DEL) *.o $(EXECUTABLE)
