#include "EasyBMP.h"

#include <random>
#include <iostream>
#include <string>
#include <vector>

using namespace std;



template <typename T>

inline T extract_bits (const T v, const unsigned bstart, const unsigned blength) {

	const T mask = (1 << blength) - 1;


	return ((v >> bstart) & mask);

}



template <typename T>

inline T set_bits (const T v, const unsigned bstart, const unsigned blength, const T bits) {

	const T mask = ((1 << blength) - 1) << bstart;


	return (v & ~mask) | (bits << bstart);

}


void hideMessage(BMP &image, const string &message, const int seed) {

	int width = image.TellWidth();

    int height = image.TellHeight();
    
    int pixelId = 0;
    
    std::mt19937 rg (seed);
    
    std::uniform_int_distribution<int> distributionComponent(0,2);
	std::uniform_int_distribution<int> distributionBit(0,7);

    for (int messageIndex = 0; messageIndex < message.size(); messageIndex++) {
    	for(int i = 0; i < 8; i++){
    		unsigned bitMessage = extract_bits(message[messageIndex], i, 1);
			int x = pixelId % width;
			int y = pixelId / width;
			
			int component = distributionComponent(rg);
			
			ebmpBYTE* byte;
			
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
	image.WriteToFile("./sample/testando.bmp");
}

string showMessage(const int &seed, BMP &image)
{
	int width = image.TellWidth();
    int height = image.TellHeight();
	
}



int main() {

 	BMP image;

 	//Abre imagem

    if (!image.ReadFromFile("./sample/EasyBMPtext.bmp")) {

        cerr << "Erro ao abrir a imagem de entrada." << endl;

        return 1;

    } else {

    	cout << "imagem de entrada aberta com sucesso" << endl;

    }

    

    std::string message = "testeFoto";
    
    int seed = 5;
	
	hideMessage(image, message, seed);
	
	if (!image.ReadFromFile("./sample/testando.bmp")) {

        cerr << "Erro ao reescrever a mensagem de entrada." << endl;

        return 1;

    } else {

    	cout << "mensagem de entrada aberta com sucesso" << endl;

    }


	string teste = showMessage(seed, image);
	cout << teste;

	return 0;

}
