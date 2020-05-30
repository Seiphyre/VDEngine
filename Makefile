NAME		=	bin/vdengine

CXX			=	clang++

CXXFLAGS	=	-std=c++17 -I includes -Wall -Wno-deprecated -g 

SRC			=	sources/glad/glad.cpp \
				sources/stb/stb_image.cpp \
				sources/GameEngine.cpp \
				sources/main.cpp \
				sources/TextureManager.cpp \
				sources/MeshFactory.cpp \
				sources/AShader.cpp \
				sources/DefaultShader.cpp \
				sources/MeshRenderer.cpp \
				sources/FileHandler.cpp \
				sources/Texture.cpp \
				sources/Mesh.cpp \
				sources/Image.cpp \
				sources/Transform.cpp \
				sources/Time.cpp \
				sources/Input.cpp \
				sources/Camera.cpp \
				resources/scripts/FPSCameraController.cpp

OBJ			=	$(SRC:.cpp=.o)

LIBS		=	-Llibs -lglfw3 -framework Cocoa -framework IOKit -framework OpenGL

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(LIBS)

clean:
	rm -f $(OBJ)

fclean:		clean
	rm -f $(NAME)

re:		fclean all