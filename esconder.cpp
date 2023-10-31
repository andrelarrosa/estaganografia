#include "EasyBMP.h"

#include "funcoesProfessor.cpp"

using namespace std;

void hideMessage(BMP &image, const string &message, const int seed) {

	int width = image.TellWidth();

    int height = image.TellHeight();
    
    int pixelId = 0;
    
    std::mt19937 rg (seed);
    
    std::uniform_int_distribution<int> distributionComponent(0,2);
	std::uniform_int_distribution<int> distributionBit(0,7);
	
	uint8_t messageSize = message.size();
	 
	for (int i = 0; i < sizeof(messageSize); i++) {
        for (int j = 0; j < 8; j++) {
            unsigned bitMessage = extract_bits(messageSize, j, 1);

            int x = pixelId % width;
            int y = pixelId / width;

            int component = distributionComponent(rg);
            ebmpBYTE *byte;
            RGBApixel pixel = image.GetPixel(x, y);

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
            *byte = set_bits(*byte, bitPosition, 1, static_cast<ebmpBYTE>(bitMessage));
            image.SetPixel(x, y, pixel);

            pixelId++;
        }
    }

    for (int messageIndex = 0; messageIndex < messageSize; messageIndex++) {
        for (int i = 0; i < 8; i++) {
            unsigned bitMessage = extract_bits(message[messageIndex], i, 1);

            int x = pixelId % width;
            int y = pixelId / width;

            int component = distributionComponent(rg);
            ebmpBYTE *byte;
            RGBApixel pixel = image.GetPixel(x, y);

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
            *byte = set_bits(*byte, bitPosition, 1, static_cast<ebmpBYTE>(bitMessage));
            image.SetPixel(x, y, pixel);

            pixelId++;
        }
    }
	image.WriteToFile("./sample/imagemEscondida.bmp");
}


int main() {

 	BMP image;

    if (!image.ReadFromFile("./sample/EasyBMPtext.bmp")) {

        cerr << "Erro ao abrir a imagem de entrada." << endl;

        return 1;

    } else {

    	cout << "imagem de entrada aberta com sucesso" << endl;

    }

    std::string message = "testeFoto";
    
    int seed = 5;
	
	hideMessage(image, message, seed);
	
	cout << "imagem de entrada escondida com sucesso" << endl;
	
	return 0;
}
