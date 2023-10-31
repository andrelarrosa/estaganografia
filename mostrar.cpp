#include "EasyBMP.h"

#include "funcoesProfessor.cpp"

using namespace std;

string showMessage(const int seed, BMP &image)
{
	int width = image.TellWidth();

    int height = image.TellHeight();
    
    int pixelId = 0;
    
    char character;
    
    string message;
    
    std::mt19937 rg (seed);
    
    std::uniform_int_distribution<int> distributionComponent(0,2);
	std::uniform_int_distribution<int> distributionBit(0,7);
	
	uint8_t messageSize = 0;
	
    for (int i = 0; i < sizeof(messageSize); i++) {
        for (int j = 0; j < 8; j++) {
            int x = pixelId % width;
            int y = pixelId / width;

            ebmpBYTE *byte;
            RGBApixel pixel = image.GetPixel(x, y);

            int component = distributionComponent(rg);

            switch (component) {
            case 0:
                byte = &pixel.Red;
                break;
            case 1:
                byte = &pixel.Green;
                break;
            case 2:
                byte = &pixel.Blue;
                break;
            }

            int bitPosition = distributionBit(rg);
            unsigned bitMessage = extract_bits(*byte, bitPosition, 1);
            messageSize = set_bits(messageSize, i * 8 + j, 1, static_cast<uint8_t>(bitMessage));
			
            pixelId++;
        }
    }
    
    for (int messageIndex = 0; messageIndex < messageSize; messageIndex++) {
        character = 0;
        for (int i = 0; i < 8; i++) {
            int x = pixelId % width;
            int y = pixelId / width;

            ebmpBYTE *byte;
            RGBApixel pixel = image.GetPixel(x, y);

            int component = distributionComponent(rg);

            switch (component) {
            case 0:
                byte = &pixel.Red;
                break;
            case 1:
                byte = &pixel.Green;
                break;
            case 2:
                byte = &pixel.Blue;
                break;
            }

            int bitPosition = distributionBit(rg);
            unsigned bitMessage = extract_bits(*byte, bitPosition, 1);
            character = set_bits(character, i, 1, static_cast<char>(bitMessage));
            
            pixelId++;
        }
        message += character;
    }

    return message;
}


int main() {
	BMP image;
	
	int seed = 5;
	
	if (!image.ReadFromFile("./sample/imagemEscondida.bmp")) {

        cerr << "Erro ao reescrever a mensagem de entrada." << endl;

        return 1;

    } else {

    	cout << "mensagem de entrada aberta com sucesso" << endl;

    }

	string teste = showMessage(seed, image);
	cout << teste << endl;

	return 0;

}
