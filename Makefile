NAME		=	bin/vdengine

CXX			=	clang++

CXXFLAGS	=	-std=c++17 -I includes -Wall -Wno-deprecated -g

SRC			=	sources/glad/glad.cpp \
				sources/stb/stb_image.cpp \
				sources/GameEngine.cpp \
				sources/GameObject.cpp \
				sources/Component.cpp \
				sources/main.cpp \
				sources/ModelLoader.cpp \
				sources/Model.cpp \
				sources/TextureManager.cpp \
				sources/ShaderManager.cpp \
				sources/MaterialManager.cpp \
				sources/MeshFactory.cpp \
				sources/Shader.cpp \
				sources/MeshRenderer.cpp \
				sources/FileHandler.cpp \
				sources/Texture.cpp \
				sources/Mesh.cpp \
				sources/Material.cpp \
				sources/Image.cpp \
				sources/Transform.cpp \
				sources/Time.cpp \
				sources/Input.cpp \
				sources/Camera.cpp \
				sources/Light.cpp \
				sources/StringCast.cpp \
				resources/scripts/FPSCameraController.cpp

OBJ			=	$(SRC:.cpp=.o)

LIBS		=	-Llibs -lglfw3 -lz -lIrrXML -lassimp -lrttr_core -framework Cocoa -framework IOKit -framework OpenGL

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(LIBS)

clean:
	rm -f $(OBJ)

fclean:		clean
	rm -f $(NAME)

re:		fclean all
