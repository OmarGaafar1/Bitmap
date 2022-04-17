// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: Picture_Editing_Tool.cpp
// Last Modification Date: 17/4/2022
// Author1 and ID and Group: Mohamed Waleed / 20210362 / A
// Author2 and ID and Group: Omar Gaafar / 2021xxxx / A
// Author3 and ID and Group: xxxxx xxxxx
// Teaching Assistant: xxxxx xxxxx

// Purpose:RGB 256x256 image editor

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE][RGB];

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
    loadImage();
    while (true)
    {
        char input;
        cout << "Please select a filter to apply or 0 to exit: " << endl;
        cout << " 1- Black & White Filter\n 2- Invert Filter\n 3- Merge Filter\n 4- Flip Image\n 5- Rotate Image\n";
        cout << " 6- Darken and Lighten Image\n 7- Detect Image Edges\n 8- Enlarge Image\n 9- Shrink Image\n a- Mirror 1/2 Image\n";
        cout << " b- Shuffle Image\n c- Blur Image\n s- Save the image to a file\n 0- Exit\n";
        cin >> input;

        switch (input)
        {
        case '1':
            filterBW();
            break;
        case '2':
            filterInvertImage ();
            break;
        case '3':
            mergeImage ();
            break;
        case '4':
            flipImage();
            break;
        case '5':
            rotateImage ();
            break;
        case '6':
            filterLuminance ();
            break;
        case '7':
            imageEdges ();
            break;
        case '8':
            imageEnlarge ();                  
            break;
        case '9':
            imageShrink ();
            break;
        case 'a':
            imageMirror ();
            break;
        case 'b':
            imageShuffle ();
            break;
        case 'c':
            imageBlur ();
            break;
        case 's':
            saveImage();
            break;
        case '0':
            return 0;
        default:
            cout << "Invalid input, please try again.\n" << endl;
            break;        
                


        }


    }
    
}

//___________________________________________________________________
void loadImage (){
    char imageFileName[999];
    cout << "Please enter file name of the image to process: ";
    cin >> imageFileName;
    strcat(imageFileName,".bmp");
    readRGBBMP(imageFileName, image);
}
//___________________________________________________________________
void saveImage (){
    char imageFileName[999];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    strcat(imageFileName,".bmp");
    writeRGBBMP(imageFileName, image);
}
//___________________________________________________________________
void filterBW(){ // 1 done
   for (int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for (int k = 0; k < 1; k++){
                if ( image[i][j][k]+ image[i][j][k+1]+ image[i][j][k+2]  >= 382){
                    image[i][j][k]   = 255;
                    image[i][j][k+1] = 255;
                    image[i][j][k+2] = 255;
                }
                else{
                    image[i][j][k]   = 0;
                    image[i][j][k+1] = 0;
                    image[i][j][k+2] = 0;
                }
            }
        } 
    }

}
//___________________________________________________________________
void filterInvertImage(){ // 2 done
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j< SIZE; j++)
            for (int k = 0; k < RGB; k++){
                image[i][j][k] = 255 - image[i][j][k];
            }
            
}
//___________________________________________________________________
void mergeImage(){ // 3 done
    unsigned char imageMerge[SIZE][SIZE][RGB];
    char imageFileName[999];
    cout << "Please enter file name of the image to merge: ";
    cin >> imageFileName;
    strcat(imageFileName,".bmp");
    readRGBBMP(imageFileName, imageMerge);
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                int avg = (imageMerge[i][j][k] + image[i][j][k]) / 2;
                image[i][j][k] = avg;
            }
        }
    }
}
//___________________________________________________________________
void flipImage (){ // 4  done
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            for ( int k = 0; k < RGB; k++){
                if (i > SIZE/2 - 1)
                    break;
                int temp = image[i][j][k];
                image[i][j][k] = image[SIZE - i - 1][SIZE - j - 1][k];
                image[SIZE - i - 1][SIZE - j - 1][k] = temp;
            }
        }
    }
}
//___________________________________________________________________
void rotateImage(){ // 5 gets more blurry as the rotations increases

    unsigned char rotated[256][256][3];
    int x =0 , y=255 ,rotation; 
    cout <<"To rotate image 90-Degree Enter '1'\nTo rotate image 180-Degree Enter '2'\nTo rotate image 270-Degree Enter '3': ";
    cin >> rotation;

    for (int k = 0; k < RGB; k++){

            for(int i = 0 ; i < rotation; i++)
            {
                    for (int i = 0; i < SIZE; i++)
                    {
                            for (int j = 0; j< SIZE; j++)
                            {

                                rotated[i][j][k] = image[x++][y][k];
                            }
                            x = 0;
                            y--;
                    }
                    for (int i = 0; i < SIZE; i++)
                            for (int j = 0; j < SIZE; j++)
                                image[i][j][k] = rotated[i][j][k];
            }
    }
}
//___________________________________________________________________
void filterLuminance(){ // 6 done
    char input;
    cout << "Do you want to (d)arken or (l)ighten?" << endl;
    cin >> input;
    switch(input){
        // darkening works
        case 'd':
            for (int i = 0; i < SIZE; i++){
                for (int j = 0; j < SIZE; j++){
                    for (int k = 0; k < RGB; k++){
                        image[i][j][k] =  image[i][j][k] - 0.5*image[i][j][k];
                    }
                }
            }
            break;
        // lightnening works
        case 'l':
            for (int i = 0; i < SIZE; i++){
                for (int j = 0; j < SIZE; j++){
                    for (int k = 0; k < RGB; k++){
                        int temp = image[i][j][k];
                        image[i][j][k] = image[i][j][k] + 0.5*(image[i][j][k]) ;
                        if (temp >= 170)
                            image[i][j][k] = 255;
                    }
                }
            }
            break;
        default:
            cout << "Invalid input, please try again." << endl;
            break;
    }
}
//___________________________________________________________________
void imageEdges(){ // 7 done
    filterBW();

    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                if (image[i][j+1][k]  - image[i][j][k]  != 0)
                    image[i][j][k]  = 0;
                else if (i != 0 && i != 1)
                    if (image[i+1][j][k]  - image[i][j][k]  != 0)
                        image[i][j][k]  = 0;
                else
                    image[i][j][k] = 255;
            }
        }
    }
}
//___________________________________________________________________
void imageEnlarge(){ // 8 In progress
    
}
//___________________________________________________________________
void imageShrink(){ // 9 In progress

}
//___________________________________________________________________
void imageMirror(){ // a  done

    char input;
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?" << endl;
    cin >> input;
    switch (input)
    {
        case 'l':
            for(int i = 0; i < SIZE; i++){
                for(int j = 0; j < SIZE; j++){
                    for (int k = 0; k < RGB; k++){
                        image[i][SIZE - j][k] = image[i][j][k];
                        if (j == SIZE/2 - 1)
                            break;
                    }
                }
            }
            break;
        case 'r':
            for(int i = 0; i < SIZE; i++){
                for(int j = 0; j < SIZE; j++){
                    for (int k = 0; k < RGB; k++){
                        image[i][j][k] = image[i][SIZE - j][k];
                        if (j == SIZE/2 - 1)
                            break;
                    }
                }
            }
            break;
        case 'u':
            for(int i = 0; i < SIZE; i++){
                for (int j = 0; j < SIZE; j++){
                    for (int k = 0; k < RGB; k++){
                        image[SIZE - j][i][k] = image[j][i][k];
                        if (j == SIZE/2 -1)
                            break;
                    }
                }
            }
            break;
        case 'd':
            for(int i = 0; i < SIZE; i++){
                for (int j = 0; j < SIZE; j++){
                    for (int k = 0; k < RGB; k++){
                        image[j][i][k] = image[SIZE - j][i][k];
                        if (j == SIZE/2 -1)
                            break;
                    }
                }
            }
            break;
        default:
            cout << "Invalid input, please try again." << endl;
            break;
    }
}
//___________________________________________________________________
void imageShuffle(){ // In progress

}
//___________________________________________________________________
void imageBlur(){ // c  needs cleaning in parots blur
    unsigned char H_blur[256][256][3],V_blur[256][256][3] ;
    int   average, sum ,average_2 , sum_2;
    for (int k = 0; k < RGB; k++){
        for (int i = 0; i < SIZE; i++)
        {   
            
            average = (image[i][0][k] + image[i][1][k]+ image[i][2][k]+ image[i][3][k] + image[i][4][k]+ image[i][5][k]) /6;
            sum = average;
            for (int j = 0; j < SIZE; j++)
            {   
                H_blur[i][j][k] = sum;
                sum= sum  - int((image[i][j][k])/6) + int((image[i][j+6][k])/6);
            }
        }

        for (int i = 0; i < SIZE; i++)
        {   
            average_2 = (H_blur[0][i][k] + H_blur[1][i][k] +  H_blur[2][i][k]+ H_blur[3][i][k] +  H_blur[4][i][k]+ H_blur[5][i][k]) / 6 ;
            sum_2 = average_2;
            for (int j = 0; j < SIZE; j++)
            { 
            V_blur[j][i][k] = sum_2;
            sum_2 = sum_2 - int ((H_blur[j][i][k])/6) +  int ((H_blur[j+6][i][k])/6) ;
            }
        }
        
        for (int i = 0; i < SIZE; i++)
        {             
            for (int j = 0; j < SIZE; j++)
            {   
            image[i][j][k] = V_blur[i][j][k];
            }
        }
    }

}
