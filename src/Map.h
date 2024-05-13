//-----------------------------MAP----------------------------------------------
#define mapX 8  //map width
#define mapY 8  //map height
#define mapS 64 //map cube size

//Edit these 3 arrays with values 0-4 to create your own level!
/*

1: Normal Wall,
2: Brick Wall,
3: Silver Wall,
4: Door,
5: Dark Normal Wall,
6: End Wall(Colourful),
7: Dark Silver Wall,
8: Wall With Button,
9: Dark Normal Wall,
10-19:Sky Texture,

Past That is Garbage. 
*/

int mapW[] = 
    {
        1,1,1,1,2,2,2,2,
        6,0,0,1,0,0,0,2,
        1,0,0,4,0,2,0,2,
        1,5,4,5,0,0,0,2,
        2,0,0,0,0,0,0,1,
        2,0,0,0,0,1,0,1,
        2,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,
};
int mapW2[] = 
    {
        1,1,1,1,1,2,2,2,
        6,0,0,0,1,0,0,2,
        1,1,1,0,4,0,0,2,
        3,0,1,0,1,0,0,2,
        3,0,4,0,1,0,0,2,
        3,0,1,1,1,0,0,2,
        3,0,0,0,0,0,0,2,
        3,3,3,3,2,2,2,2,
};

/*
1: Brick Floor
2: Silver Floor
3: door
4: Light Nrmal Floor
5: End door
6: Light Silver Floor
7: Button Floor
8: Dark Normal Floor


Past That is Garbage.
*/

int mapF[] = //floors
    {
        0,0,0,0,0,0,0,0,
        0,0,0,0,2,2,2,0,
        0,0,0,0,2,2,2,0,
        0,0,8,0,2,2,2,0,
        0,0,2,0,0,2,2,0,
        0,0,2,0,8,2,2,0,
        0,1,1,1,1,2,2,0,
        0,0,0,0,0,0,0,0,
};


/* 

Same as the floor, but for the ceiling.


*/

int mapC[] = //ceiling
    {
        0,0,0,0,0,0,0,0,
        0,4,4,4,0,0,0,0,
        0,0,0,4,4,0,0,0,
        0,0,0,4,0,0,0,0,
        0,4,4,4,0,0,0,0,
        0,0,2,0,0,0,0,0,
        0,0,2,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
};