// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: a7a editing tool.cpp
// Last Modification Date: 30/3/2022
// Author1 and ID and Group: Mohamed Waleed / 20210362 / A
// Author2 and ID and Group: Omar Gaafar / 2021xxxx / A
// Author3 and ID and Group: xxxxx xxxxx
// Teaching Assistant: xxxxx xxxxx
// Purpose:..........

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE];

void loadImage ();
void saveImage ();

void filterBW (); // 1
void filterInvertImage (); // 2
void mergeImage (); // 3
void flipImage (); // 4
void rotateImage (); // 5
void filterLuminance (); // 6
void imageEdges (); // 7
void imageEnlarge (); // 8
void imageShrink (); // 9
void imageMirror (); // a
void imageShuffle (); // b
void imageBlur (); // c


int main()
{
    cout << "Ahlan ya user ya habibi :)" << endl;

    while (true){
        char input;
        cout << "Please select a filter to apply or 0 to exit: " << endl;
        cout << " 1- Black & White Filter\n 2- Invert Filter\n 3- Merge Filter\n 4- Flip Image\n 5- Darken and Lighten Image\n";
        cout << " 6- Rotate Image\n 7- Detect Image Edges\n 8- Enlarge Image\n 9- Shrink Image\n a- Mirror 1/2 Image\n";
        cout << " b- Shuffle Image\n c- Blur Image\n s- Save the image to a file\n 0- Exit\n";
        cin >> input;
        switch (input)
        {
        case '1':
            loadImage();
            filterBW();
            break;
        case '2':
            loadImage();
            filterInvertImage ();
            break;
        case '3':
            loadImage();
            //mergeImage ();
            break;
        case '4':
            loadImage();
            flipImage();
            break;
        case '5':
            loadImage();
            //rotateImage ();
            break;
        case '6':
            loadImage();
            //filterLuminance ();
            break;
        case '7':
            loadImage();
            imageEdges ();
            break;
        case '8':
            loadImage();
            //imageEnlarge ();
            break;
        case '9':
            loadImage();
            //imageShrink ();
            break;
        case 'a':
            loadImage();
            imageMirror ();
            break;
        case 'b':
            loadImage();
            //imageShuffle ();
            break;
        case 'c':
            loadImage();
            //imageBlur ();
            break;
        case 's':
            //loadImage();
            saveImage();
            break;
        case '0':
            return 0;
        default:
            cout << "Invalid input, please try again.\n" << endl;
            break;
        }
    }

  return 0;
}

//___________________________________________________________________
void loadImage (){
    char imageFileName[999];
    cout << "Please enter file name of the image to process: ";
    cin >> imageFileName;
    strcat(imageFileName,".bmp");
    readGSBMP(imageFileName, image);
}
//___________________________________________________________________
void saveImage (){
    char imageFileName[999];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    strcat(imageFileName,".bmp");
    writeGSBMP(imageFileName, image);
}
//___________________________________________________________________
void filterBW(){ // 1
    for (int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        } 
    }
}
//___________________________________________________________________
void filterInvertImage(){ // 2
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j< SIZE; j++)
            image[i][j] = 255 - image[i][j];
}
//___________________________________________________________________
void flipImage (){ // 4
}
//___________________________________________________________________
void imageEdges(){ // 7
}
//___________________________________________________________________
void imageMirror(){ // a
    char input;
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?" << endl;
    cin >> input;
    switch (input)
    {
        case 'l':
            for(int i = 0; i < SIZE; i++){
                for(int j = 0; j < SIZE; j++){
                    image[i][SIZE - j] = image[i][j];
                    if (j == SIZE/2 - 1)
                        break;
                }
            }
            break;
        case 'r':
            for(int i = 0; i < SIZE; i++){
                for(int j = 0; j < SIZE; j++){
                    image[i][j] = image[i][SIZE - j];
                    if (j == SIZE/2 - 1)
                        break;
                }
            }
            break;
        case 'u':
            for(int i = 0; i < SIZE; i++){
                for (int j = 0; j < SIZE; j++){
                    image[SIZE - j][i] = image[j][i];
                    if (j == SIZE/2 -1)
                        break;
                }
            }
            break;
        case 'd':
            for(int i = 0; i < SIZE; i++){
                for (int j = 0; j < SIZE; j++){
                    image[j][i] = image[SIZE - j][i];
                    if (j == SIZE/2 -1)
                        break;
                }
            }
            break;
        default:
            cout << "Invalid input, please try again." << endl;
            break;
    }
}