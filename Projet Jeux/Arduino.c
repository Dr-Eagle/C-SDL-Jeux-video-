#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>

FILE *f;

void intialiserArduino(FILE *f1)
{
    f=fopen("/dev/ttyACM0","w+");
    f1=f;
}

void Getf(FILE *f1)
{
    f1=f;
}

int arduinoReadDataMenu(int x[])

{
    printf(" arduino read Menu \n");

    if(f!=NULL)
    {
        if(!feof(f))
        {
            fscanf(f,"%d,%d,%d,%d",&x[0],&x[1],&x[2],&x[3]);
            printf("i'm reading\n");
        }

    }
    else return EXIT_FAILURE;


    //  fclose(f);

    return(0);
}

int arduinoReadDataLoad(int x[])
{
    printf(" arduino read load \n");

    if(f!=NULL)
    {
        if(!feof(f))
        {
            fscanf(f,"%d,%d,%d,%d",&x[0],&x[1],&x[2],&x[3]);
            printf("i'm reading\n");
        }

    }
    else return EXIT_FAILURE;


    //  fclose(f);

    return(0);
}

int arduinoReadDataNew(int x[])
{
    printf(" arduino read new \n");

    if(f!=NULL)
    {
        if(!feof(f))
        {
            fscanf(f,"%d,%d,%d,%d",&x[0],&x[1],&x[2],&x[3]);
            printf("i'm reading\n");
        }

    }
    else return EXIT_FAILURE;


    //  fclose(f);

    return(0);
}

int arduinoReadDataSaisi(int x[])
{
    printf(" arduino read saisi \n");

    if(f!=NULL)
    {
        if(!feof(f))
        {
            fscanf(f,"%d,%d,%d,%d",&x[0],&x[1],&x[2],&x[3]);
            printf("i'm reading\n");
        }

    }
    else return EXIT_FAILURE;


    //  fclose(f);

    return(0);
}

int arduinoReadDataMulti(int x[])
{
    printf(" arduino read Multi \n");

    if(f!=NULL)
    {
        if(!feof(f))
        {
            fscanf(f,"%d,%d,%d,%d",&x[0],&x[1],&x[2],&x[3]);
            printf("i'm reading\n");
        }

    }
    else return EXIT_FAILURE;


    //  fclose(f);

    return(0);
}

int arduinoReadDataSet(int x[])
{
    printf(" arduino read Setting \n");

    if(f!=NULL)
    {
        if(!feof(f))
        {
            fscanf(f,"%d,%d,%d,%d",&x[0],&x[1],&x[2],&x[3]);
            printf("i'm reading\n");
        }

    }
    else return EXIT_FAILURE;


    //  fclose(f);

    return(0);
}

int arduinoReadDataEx(int x[])
{
    printf(" arduino read Exit \n");

    if(f!=NULL)
    {
        if(!feof(f))
        {
            fscanf(f,"%d,%d,%d,%d",&x[0],&x[1],&x[2],&x[3]);
            printf("i'm reading\n");
        }

    }
    else return EXIT_FAILURE;


    //  fclose(f);

    return(0);
}

/*void arduinoWriteData(char x[])
{



    fprintf(f,"%s",x);
    //fclose(f);


}*/

int arduinoReadDataAutre(int x[])

{
    printf(" arduino read Autre \n");

    if(f!=NULL)
    {
        if(!feof(f))
        {
            fscanf(f,"%d,%d,%d,%d",&x[0],&x[1],&x[2],&x[3]);
            printf("i'm reading\n");
        }

    }
    else return EXIT_FAILURE;


    //  fclose(f);

    return(0);
}

int arduinoReadDataInput(int x[])
{
    printf(" arduino read input \n");

    if(f!=NULL)
    {
        if(!feof(f))
        {
            fscanf(f,"%d,%d,%d,%d",&x[0],&x[1],&x[2],&x[3]);
            printf("i'm reading\n");
        }

    }
    else return EXIT_FAILURE;


    //  fclose(f);

    return(0);
}
int arduinoReadDataEnigme(int x[])
{
    printf(" arduino read Enigme \n");

    if(f!=NULL)
    {
        if(!feof(f))
        {
            fscanf(f,"%d,%d,%d,%d",&x[0],&x[1],&x[2],&x[3]);
            printf("i'm reading\n");
        }

    }
    else return EXIT_FAILURE;


    //  fclose(f);

    return(0);
}
