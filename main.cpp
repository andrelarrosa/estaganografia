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



void hideMessage(BMP &image, const string &message, const vector<unsigned> &seed)

{

	int width = image.TellWidth();

    int height = image.TellHeight();
    
    int messageIndex = 0;

    for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			RGBApixel pixel = image.GetPixel(x, y);
			
			if (messageIndex < message.length()) {
				if (seed[messageIndex % seed.size()] == 1) {
					char nextChar = message[messageIndex];

					unsigned redValue = pixel.Red;
					unsigned greenValue = pixel.Green;
					unsigned blueValue = pixel.Blue;
					
					unsigned calc = (nextChar >> (messageIndex % 8) & 1);
										
					redValue = set_bits(redValue, 0, 1, calc);
					greenValue = set_bits(greenValue, 0, 1, calc);
					blueValue = set_bits(blueValue, 0, 1, calc);

					pixel.Red = static_cast<ebmpBYTE>(redValue);
					pixel.Green = static_cast<ebmpBYTE>(greenValue);
					pixel.Blue = static_cast<ebmpBYTE>(blueValue);
					
					++messageIndex;

				}
				image.SetPixel(x, y, pixel);
			}
			else {
				break;
			}
		}
    }
}

string showMessage(const vector<unsigned> &seed, BMP &image)
{
	int width = image.TellWidth();
    int height = image.TellHeight();

    string extractedMessage;
    int messageIndex = 0;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            RGBApixel pixel = image.GetPixel(x, y);

            if (messageIndex < seed.size()) {
                if (seed[messageIndex % seed.size()] == 1) {
                    unsigned extractedBit = extract_bits(pixel.Red, 0, 1);
                    extractedMessage += static_cast<char>((extractedBit << (messageIndex % 8) & 1));
                    cout << messageIndex << endl;
                    messageIndex++;
                }
            }
        }
    }

    return extractedMessage;
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
    
    vector<unsigned> seed = {1, 0, 1, 0, 1, 0, 1};

    hideMessage(image, message, seed);
	
	string extractedMessage = showMessage(seed, image);
    cout << "Mensagem extraída: " << extractedMessage << endl;

	return 0;

}

