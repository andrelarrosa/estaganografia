#include "EasyBMP.h"
using namespace std;
int hideMessage(BMP &image, const string &message)
{
	int width = image.TellWidth();
    int height = image.TellHeight();
   
    int messageIndex = 0;
     
    for (int y = 0; y < height; ++y) {
       for (int x = 0; x < width; ++x) {
           RGBApixel pixel = image.GetPixel(x, y);
           if (messageIndex < message.length()) {
               
               cout << messageIndex;
               ++messageIndex;
           }
       }
   }
    
   return 0;
}

int main() {
 	BMP image;
    if (!image.ReadFromFile("./sample/EasyBMPtext.bmp")) {
        cerr << "Erro ao abrir a imagem de entrada." << endl;
        return 1;
    }
    
    std::string message = "testeFoto";
    
    hideMessage(image, message);

}

