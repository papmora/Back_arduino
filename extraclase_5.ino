#include "LedControlMS.h" 
#include<stdio.h>
#define N 8



bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N]);
int obs =2;
int prueba[N][N] = 
      { {1, 1, 1, 1, 1, 1, 1, 1}, 
        {1, 1, 1, 1, 1, 1, 1, 1}, 
        {1, 1, 1, 1, 1, 1, 1, 1}, 
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1} 
        
    };


LedControl lc=LedControl(12,11,10,1); // Los numeros se refieren a que pin de ARDUINO tienes en cada uno de los terminales
/* 12 para el DIN, 11 para el CLK, 10 para el CS y el 1 se refiere a la asignacion de la matriz*/

byte Cara[] = 
{B00111100,
B01000010,
B10100101,
B10000001,
B10100101,
B10011001,
B01000010,
B00111100};

byte Cara2[] = 
{B00111100,
 B01000010,
 B10100101,
 B10000001,
 B10011001,
 B10100101,
 B01000010,
 B00111100};



void setup()
{
  // El numero que colocamos como argumento de la funcion se refiere a la direccion del decodificador
  lc.shutdown(0,false);
  lc.setIntensity(0,1);// La valores estan entre 1 y 15 
  lc.clearDisplay(0);
  
  
}
void loop()
{
 // Representar(Mensaje_datos,5000);
  
    
     
    solveMaze(genMatriz(obs, prueba));
    
  
  //trans();
  delay(500);
  lc.clearDisplay(0);
}



int genMatriz(int obs, int matriz[N][N])
{
    
  for (int i=0; i<obs;i++)
  {
    int ran1=random(N-1);
    int ran2= random(N-1);
    
    for (int j=0; j<N;j++)
    {
      for (int k=0; k<N;k++)
      {
       if(j==0 && k==0 || j==N-1 && k==N-1)
       {
         matriz[j][k]=1;
       }
       if(j==ran1 && k==ran2)
       {
        if(matriz[j][k]==1)
        { matriz[k][j]=0;}
        else{matriz[j][k]=0;}
       }
       else
       {
        if( matriz[j][k]!=0)
        {
          matriz[j][k]=1;
        }
       }
      }
 
    }
  }
  return matriz;
}

/* A utility function to check if x,y is valid index for N*N maze */
bool isSafe(int maze[N][N], int x, int y) 
{ 
    // if (x,y outside maze) return false 
    if(x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1){
        return true;} 
  
    else {
      
      return false;} 
} 


void printmatriz(int sol[N][N]) 
{
  for (int i = 0; i < N; i++) 
    { 
        for (int j = 0; j < N; j++) 
        if (sol[i][j]==0)
         lc.setLed(0,i,j,true);
    } 
}

bool solveMaze(int maze[N][N]) 
{ 

    printmatriz(maze);

  
    int sol[N][N] = { {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0} 
    }; 
  
    if(solveMazeUtil(maze, 0, 0, sol, 3) == false) 
    { 
        Representar(Cara2,5000);
        trans();
        return false; 
    } 
    
    Representar(Cara,5000);
    trans();
    obs=obs+2;
    solveMaze(genMatriz(obs,prueba));
    return true; 
} 

/* A recursive utility function to solve Maze problem */
bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N], int dir) 
{ 
    // if (x,y is goal) return true 
    if(x == N-1 && y == N-1) 
    { 
        sol[x][y] = 1;
        lc.setLed(0,x,y,true);
           
        return true; 
    } 
  
    // Check if maze[x][y] is valid 
    if(isSafe(maze, x, y) == true) 
    { 
        // mark x,y as part of solution path 
        sol[x][y] = 1; 
        lc.setLed(0,x,y,true);
        delay(500);
        lc.setLed(0,x,y,false);
        delay(500);
  
        /* Move forward in x direction */
        if (dir!=2 && solveMazeUtil(maze, x+1, y, sol, 3) == true) 
            
            return true; 
  
        /* If moving in x direction doesn't give solution then 
           Move down in y direction  */
        if (dir!=4 && solveMazeUtil(maze, x, y+1, sol, 5) == true) 
          
            return true; 

        if (dir!=3 && solveMazeUtil(maze, x-1, y, sol, 2) == true) 
          
            return true;

        if (dir!=5 && solveMazeUtil(maze, x, y-1, sol, 4) == true) 
          
            return true;
  
        /* If none of the above movements work then BACKTRACK:  
            unmark x,y as part of solution path */
        sol[x][y] = 0; 
       
        
        return false; 
    }    
  
    return false; 
} 








// Funcion para representar una transicion animada

void trans(){ //Funcion de transicion para llenar y vaciar la pantalla de puntos
  for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      lc.setLed(0,col,row,true); // 
      delay(25);
    }
  }
 
  for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      lc.setLed(0,col,row,false); // 
      delay(25);
    }
  }
}

// Definimos una funcion para representar las figuras

void Representar(byte *Datos,int retardo) //Funcion para la representacion de bytes de datos para una matriz de 8x8 
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setColumn(0,i,Datos[7-i]);
  }
  delay(retardo);
}
