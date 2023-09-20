#include "EasyBMP.h"

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

int hideMessage(BMP &image, const string &message)
{
	int width = image.TellWidth();
    int height = image.TellHeight();
	
	
    
   return 0;
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
    
    BMP image_copy(image);
    
    unsigned x = 0;
	x = set_bits(x, 1, 2, static_cast<unsigned>(0x01));
	cout << x << endl;
	unsigned y = 7; // 8 bits e multiplos de 7
	y = extract_bits(y, static_cast<unsigned>(0x01),1);
	cout << y << endl;
    
    cout << "copiando a imagem..." << endl;
    //Copia Imagem
    image_copy.WriteToFile("./sample/test_copy.bmp");
    cout << "copiado com sucesso!" << endl;

	return 0;
}

