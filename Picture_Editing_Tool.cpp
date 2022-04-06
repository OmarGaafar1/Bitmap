// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: Picture_Editing_Tool.cpp
// Last Modification Date: 31/3/2022
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
    loadImage();
    while (true)
    {
        char input;
        cout << "Please select a filter to apply or 0 to exit: " << endl;
        cout << " 1- Black & White Filter\n 2- Invert Filter\n 3- Merge Filter\n 4- Flip Image\n 5- Rotate Image\n";
        cout << " 6- Darken and Lighten Image\n 7- Detect Image Edges\n 8- Enlarge Image\n 9- Shrink Image\n a- Mirror 1/2 Image\n";
        cout << " b- Shuffle Image\n c- Blur Image\n s- Save the image to a file\n r- Enter a new image\n 0- Exit\n";
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
            //mergeImage ();
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
            //imageEnlarge ();                  
            break;
        case '9':
            //imageShrink ();
            break;
        case 'a':
            imageMirror ();
            break;
        case 'b':
            //imageShuffle ();
            break;
        case 'c':
            imageBlur ();
            break;
        case 's':
            saveImage();
            break;
        case 'r':
            loadImage();
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
void filterBW(){ // 1 done
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
void filterInvertImage(){ // 2 done
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j< SIZE; j++)
            image[i][j] = 255 - image[i][j];
}
//___________________________________________________________________
void flipImage (){ // 4  done
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if (i > SIZE/2 - 1)
                break;
            int temp = image[i][j];
            image[i][j] = image[SIZE - i - 1][SIZE - j - 1];
            image[SIZE - i - 1][SIZE - j - 1] = temp;
        }
    }
}
//___________________________________________________________________
void rotateImage(){ // 5 Done !
    unsigned char rotated[256][256];
    int x =0 , y=255 ,rotation; 
    cout <<"To rotate image 90-Degree Enter '1'\nTo rotate image 180-Degree Enter '2'\nTo rotate image 270-Degree Enter '3': ";
    cin >> rotation;
    
    for(int i = 0 ; i < rotation; i++)
    {
            for (int i = 0; i < SIZE; i++)
            {
                    for (int j = 0; j< SIZE; j++)
                    {

                        rotated[i][j] = image[x++][y];
                    }
                    x = 0;
                    y--;
            }
            for (int i = 0; i < SIZE; i++)
                    for (int j = 0; j < SIZE; j++)
                        image[i][j] = rotated[i][j];
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
                    image[i][j] =  image[i][j] - 0.5*image[i][j];
                }
            }
            break;
        // lightnening works
        case 'l':
            for (int i = 0; i < SIZE; i++){
                for (int j = 0; j < SIZE; j++){
                    int temp = image[i][j];
                    image[i][j] = image[i][j] + 0.5*(image[i][j] + 1) ;
                    if (temp > image[i][j])
                        image[i][j] = 256 - image[i][j];
                }
            }
            break;
        default:
            cout << "Invalid input, please try again." << endl;
            break;
    }
    
}
//___________________________________________________________________
void imageEdges(){ // 7 works but not the best
    filterBW();
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if (image[i][j+1] - image[i][j] != 0)
                image[i][j] = 0;
            else if (i != 0 && i != 1)
                if (image[i+1][j] - image[i][j] != 0)
                    image[i][j] = 0;
            else
                image[i][j] = 255;
        }
    }
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
//___________________________________________________________________
void imageBlur(){ // c   Done!
    unsigned char H_blur[256][256],V_blur[256][256] ;
    int   average, sum ,average_2 , sum_2;
    for (int i = 0; i < SIZE; i++)
    {   
        
        average = (image[i][0] + image[i][1]+ image[i][2]+ image[i][3] + image[i][4]+ image[i][5]) /6;
        sum = average;
        for (int j = 0; j < SIZE; j++)
        {   
            H_blur[i][j] = sum;
            sum= sum  - int((image[i][j])/6) + int((image[i][j+6])/6);
        }
   }

    for (int i = 0; i < SIZE; i++)
    {   
        average_2 = (H_blur[0][i] + H_blur[1][i] +  H_blur[2][i]+ H_blur[3][i] +  H_blur[4][i]+ H_blur[5][i]) / 6 ;
        sum_2 = average_2;
        for (int j = 0; j < SIZE; j++)
        { 
           V_blur[j][i] = sum_2;
           sum_2 = sum_2 - int ((H_blur[j][i])/6) +  int ((H_blur[j+6][i])/6) ;
        }
    }
    
    for (int i = 0; i < SIZE; i++)
    {             
        for (int j = 0; j < SIZE; j++)
        {   
           image[i][j] = V_blur[i][j];
        }
    }
}
