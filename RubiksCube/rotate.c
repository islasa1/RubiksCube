#include <stdio.h>
#include <stdlib.h>

#define MAX 5
#define ASCII_A 65

void rotate(unsigned char img[MAX][MAX], unsigned char newImg[MAX][MAX], int rotation);

int main(void)
{
  unsigned char img[MAX][MAX], newImg[MAX][MAX];
  int i, j;
  for(i = 0; i < MAX; i++)
  {
    for(j = 0; j < MAX; j++)
    {
      img[i][j] = ASCII_A + i*MAX + j;
      printf("%c ", img[i][j]);
    }
    printf("\n");
  }
  
  printf("Rotate 1:\n");
  rotate(img, newImg, 1);
  for(i = 0; i < MAX; i++)
  {
    for(j = 0; j < MAX; j++)
    {
      printf("%c ", newImg[i][j]);
    }
    printf("\n");
  }
  
  printf("Rotate 2:\n");
  rotate(img, newImg, 2);
  for(i = 0; i < MAX; i++)
  {
    for(j = 0; j < MAX; j++)
    {
      printf("%c ", newImg[i][j]);
    }
    printf("\n");
  }
  
  printf("Rotate 3:\n");
  rotate(img, newImg, -5);
  for(i = 0; i < MAX; i++)
  {
    for(j = 0; j < MAX; j++)
    {
      printf("%c ", newImg[i][j]);
    }
    printf("\n");
  }
  
  printf("Rotate 4:\n");
  rotate(img, newImg, -4);
  for(i = 0; i < MAX; i++)
  {
    for(j = 0; j < MAX; j++)
    {
      printf("%c ", newImg[i][j]);
    }
    printf("\n");
  }
}

void rotate(unsigned char img[MAX][MAX], unsigned char newImg[MAX][MAX], int rotation)
{
  rotation %= 4;
  int i,j;
  for(i = 0; i < MAX; i++)
  {
    for(j = 0; j < MAX; j++)
    {
      switch(rotation)
      {
        case 1:
        case -3:
          newImg[j][i] = img[MAX - i - 1][j];
          break;
        case 2:
        case -2:
          newImg[j][i] = img[MAX - j - 1][MAX - i - 1];
          break;
        case 3:
        case -1:
          newImg[j][i] = img[i][MAX - j - 1];
          break;
        case 0: 
          newImg[i][j] = img[i][j];
      }
    }
  }
}
