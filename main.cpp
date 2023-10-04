
#include "EasyBMP.h"

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



void teste(BMP &image, const string &message, const int &seed) {

	int width = image.TellWidth();

    int height = image.TellHeight();
    
    int messageIndex = 0;
    
    while (messageIndex <= message.size()) {
    
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				RGBApixel pixel = image.GetPixel(x, y);
				unsigned char redBits = (message[messageIndex] >> seed) & 7;
				
				pixel.Red = set_bits(pixel.Red, 0, 1, redBits);
				pixel.Green = set_bits(pixel.Green, 0, 1, redBits);
				pixel.Blue = set_bits(pixel.Blue, 0, 1, redBits);
				
				image.SetPixel(x, y, pixel);
			}
		}
		messageIndex++;    
    }
	image.WriteToFile("./sample/testando.bmp");
}


string showMessage(const int &seed, BMP &image)
{
	int width = image.TellWidth();
    int height = image.TellHeight();
	string message;
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			RGBApixel pixel = image.GetPixel(x, y);
			
			unsigned extractedBitRed = extract_bits(pixel.Red, 0, 1);
			unsigned extractedBitGreen = extract_bits(pixel.Green, 0, 1);
			unsigned extractedBitBlue = extract_bits(pixel.Blue, 0, 1);
			
			

		}
	}
	
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
	
	teste(image, message, seed);
	
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
