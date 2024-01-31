#include <raylib.h>
#include <math.h>
#include <iostream>
Camera2D originCam;
int cameraMode = 0;
Vector2 MouseVector;
//variable declarations
#define levelWidth 100
#define levelHeight 100
int tileWidth = 32;
int tileHeight = 32;
int mouseX, mouseY;
Vector2 PlayerVector = {200, 200};
float x = PlayerVector.x;
float y = PlayerVector.y;
int tileSelection = 1;

//Game variables
double gravity = 1600;
int bufferJumpTimer = 0;
bool playerCanMove = true;

// level array
int levelArray[levelHeight][levelWidth];

// level setup function (fills the levelarray with zeros)

void SetupLevel(){
    
    for(int j = 0; j < levelHeight; j++){
        
    for(int i = 0; i < levelWidth; i++)
    {
        levelArray[j][i] = 0;
    }
    
    }
}

//raycasting function
Vector3 RayCollideRec(float startX, float startY, float endX, float endY){

float originX = startX/tileWidth;
float originY = startY/tileHeight;
float targetX = endX/tileWidth;
float targetY = endY/tileHeight;
float dx = (targetX - originX);
float dy = (targetY - originY);
float rayLengthTotal = sqrt(dx*dx+dy*dy);
float normalizedX = dx/rayLengthTotal;
float normalizedY = dy/rayLengthTotal;
float unitStepSizeX, unitStepSizeY;
unitStepSizeX = sqrt(1+(normalizedY/normalizedX)*(normalizedY/normalizedX));
unitStepSizeY = sqrt(1+(normalizedX/normalizedY)*(normalizedX/normalizedY));


float rayLengthX, rayLengthY;
int XStep, YStep;
int MapCheckX = originX;
int MapCheckY = originY;

if(normalizedX < 0)
{
    XStep = -1;
    rayLengthX = ((originX-(float(MapCheckX)))*unitStepSizeX);
}
else
{
    XStep = 1;
    rayLengthX = ((float(MapCheckX)+1) - originX) * unitStepSizeX;
}

if(normalizedY < 0)
{
    YStep = -1;
    rayLengthY = (originY-(MapCheckY)) * unitStepSizeY;
}
else
{
    YStep = 1;
    rayLengthY = (((MapCheckY+1)) - originY) * unitStepSizeY;
}

bool tileFound = false;
float maxDist = 100.0f;
float distance = 0.0f;

while(!tileFound && distance < maxDist){

if(rayLengthX < rayLengthY){
    MapCheckX += XStep;
    distance = rayLengthX;
    rayLengthX += unitStepSizeX;
}

else {
    MapCheckY += YStep;
    distance = rayLengthY;
    rayLengthY += unitStepSizeY;
}

//if(MapCheckX >= 0 && MapCheckX < levelWidth && MapCheckY >= 0 && MapCheckY < levelHeight){
if (levelArray[MapCheckY][MapCheckX] == 1)
{
    tileFound = true;
//}
}
}
float intersectionX;
float intersectionY;
if(tileFound){
intersectionX = originX + normalizedX*distance;
intersectionY = originY + normalizedY*distance;
}
DrawLine(startX, startY, endX, endY, YELLOW);
DrawCircle(intersectionX*tileWidth, intersectionY*tileHeight, 4, YELLOW);
DrawText(TextFormat("distance: %f, Xunitdist: %f, Yunitdist: %f, MapCheckX: %i, MapCheckY: %i, \n dx: %f, dy: %f, raylengthx:%f, raylengthy:%f, normX:%f, normY:%f \n raylength:%f, tileFound:%i \n intersectionX:%f, intersectionY:%f", distance, unitStepSizeX, unitStepSizeY, MapCheckX, MapCheckY, dx, dy, rayLengthX,rayLengthY, normalizedX, normalizedY, rayLengthTotal, tileFound, intersectionX, intersectionY), 100, 100, 20, WHITE);
return Vector3{intersectionX*tileWidth, intersectionY*tileHeight, float(tileFound)};

}

//player raycasting function
//raycasting function
Vector3 PlayerRayCollideRec(float startX, float startY, float endX, float endY){

float originX = startX/tileWidth;
float originY = startY/tileHeight;
float targetX = endX/tileWidth;
float targetY = endY/tileHeight;

float dx = (targetX - originX);
float dy = (targetY - originY);
float rayLengthTotal = sqrt(dx*dx+dy*dy);
float normalizedX = dx/rayLengthTotal;
float normalizedY = dy/rayLengthTotal;
float unitStepSizeX, unitStepSizeY;
unitStepSizeX = sqrt(1+(normalizedY/normalizedX)*(normalizedY/normalizedX));
unitStepSizeY = sqrt(1+(normalizedX/normalizedY)*(normalizedX/normalizedY));


float rayLengthX, rayLengthY;
int XStep, YStep;
int MapCheckX = originX;
int MapCheckY = originY;

if(normalizedX < 0)
{
    XStep = -1;
    rayLengthX = ((originX-(float(MapCheckX)))*unitStepSizeX);
}
else
{
    XStep = 1;
    rayLengthX = ((float(MapCheckX)+1) - originX) * unitStepSizeX;
}

if(normalizedY < 0)
{
    YStep = -1;
    rayLengthY = (originY-(MapCheckY)) * unitStepSizeY;
}
else
{
    YStep = 1;
    rayLengthY = (((MapCheckY+1)) - originY) * unitStepSizeY;
}

bool tileFound = false;
float maxDist = 100.0f;
float distance = 0.0f;

while(!tileFound && distance < maxDist){

if(rayLengthX < rayLengthY){
    MapCheckX += XStep;
    distance = rayLengthX;
    rayLengthX += unitStepSizeX;
}

else {
    MapCheckY += YStep;
    distance = rayLengthY;
    rayLengthY += unitStepSizeY;
}

//if(MapCheckX >= 0 && MapCheckX < levelWidth && MapCheckY >= 0 && MapCheckY < levelHeight){
if (levelArray[MapCheckY][MapCheckX] == 1)
{
    tileFound = true;
//}
}
}
float intersectionX;
float intersectionY;
if(tileFound){
intersectionX = originX + normalizedX*distance;
intersectionY = originY + normalizedY*distance;
}
DrawLine(startX, startY, endX, endY, YELLOW);
DrawCircle(intersectionX*tileWidth, intersectionY*tileHeight, 4, YELLOW);
DrawText(TextFormat("distance: %f, Xunitdist: %f, Yunitdist: %f, MapCheckX: %i, MapCheckY: %i, \n dx: %f, dy: %f, raylengthx:%f, raylengthy:%f, normX:%f, normY:%f \n raylength:%f, tileFound:%i \n intersectionX:%f, intersectionY:%f", distance, unitStepSizeX, unitStepSizeY, MapCheckX, MapCheckY, dx, dy, rayLengthX,rayLengthY, normalizedX, normalizedY, rayLengthTotal, tileFound, intersectionX, intersectionY), 100, 100, 20, WHITE);
return Vector3{intersectionX*tileWidth, intersectionY*tileHeight, float(tileFound)};

}

// structures and classes
class PhysicsRectangle {
        public:
        float X;
        float Y;
        float newX;
        float newY;
        double VelX;
        double VelY;
        double SizeX;
        double SizeY;
        double AccX;
        double AccY;

        PhysicsRectangle(double PositionX, double PositionY, double VelocityX, double VelocityY, double ScaleX, double ScaleY) {
        
        SizeX = ScaleX;
        SizeY = ScaleY;
        X = PositionX;
        Y = PositionY;
        VelX = VelocityX;
        VelY = VelocityY;
        }
    // DO NOT RUN THIS FUNCTION FOR THE PLAYER, instead use the dedicated runPlayerPhysics function!
    void runPhysics() {
            X = X+VelX;
            Y = Y+VelY;
            VelX = VelX+AccX;
            VelY = VelY+AccY;
        }


    };

    // Player Object C lass, inherits PhysicsRectangle Class
class Player: public PhysicsRectangle {
    public:


//constructor
    Player( double posx, double posy, double speedx, double speedy, double jump, double speed, double playergravitymod, double width, double height): PhysicsRectangle(posx, posy, speedx, speedy, width, height)  {

        jumpHeight = jump;
        walkSpeed = speed;
        gravityModifier = playergravitymod;
    }
        double jumpHeight;
        double walkSpeed;
        double gravityModifier = 1;
        double floorSpeedX = 0;
        double floorSpeedY = 0;
        bool grounded;
        bool jumping;
        double targetSpeed;
        double velComponentJump;
        bool wallClinging = false;
        Color playerColor = WHITE;

        void setPlayerPosition(double Xpos, double Ypos){

            X = Xpos;
            Y = Ypos;

        }

//physics functions

        void runGravityPhysics() {

            AccY = gravity*gravityModifier;

        }


        void runPlayerPhysics() {

 
            VelX = VelX+AccX*GetFrameTime();
            VelY = VelY+AccY*GetFrameTime();
            newX = X+VelX*GetFrameTime();
            newY = Y+VelY*GetFrameTime();
            if(PlayerRayCollideRec(X, Y, newX, newY).z == 1){
            float rayX = PlayerRayCollideRec(X, Y, newX, newY).x;
            float rayY = PlayerRayCollideRec(X, Y, newX, newY).y;
            
            if(VelX > 0)
            {
                if(rayX < newX){
                    newX = rayX-1;
                    VelX = 0;
                    wallClinging = true;
                }
            }
            if(VelX < 0)
            {
                if(rayX > newX){
                    newX = rayX+1;
                    VelX = 0;
                    wallClinging = true;
                }
            }
            if(VelY > 0)
            {
                if(rayY < newY){
                    newY = rayY-1;
                    VelY = 0;
                    //if you're colliding with the ground downwards, you can jump now.
                    grounded = true;
                }
            }
            if(VelY < 0)
            {
                if(rayY > newY){
                    newY = rayY+1;
                    VelY = 0;
                    jumping = false;
                }
            }
            }

            X = newX;
            Y = newY;
        }


//other functions

        double getLeftOf(){
            return X-SizeX/2;
        }

        double getRightOf(){
            return X+SizeX/2;
        }

        double getTopOf(){
            return Y-SizeY/2;
        }

        double getBottomOf(){
            return Y+SizeY/2;
        }
};

    Player player(256, 256, 0, 0, 600, 300, 1, 32, 32);



void SetupGame(){
    


}


void MoveCamera()
{

BeginMode2D(originCam);

}

void playerJump(){
    if(player.grounded)
    {
    player.grounded = false;
    player.jumping = true;
    player.VelY = -player.jumpHeight + player.floorSpeedY;
    }

    if(!player.grounded)
    {
    bufferJumpTimer = 10;
    }
}

void takeInput() {

if(playerCanMove){
//horizontal movement
if(IsKeyDown(KEY_A)) {

    player.VelX = -player.walkSpeed + player.floorSpeedX;

}

if(IsKeyDown(KEY_D)) {

    player.VelX = player.walkSpeed + player.floorSpeedX;

}

if(IsKeyUp(KEY_A) && IsKeyUp(KEY_D)){

    player.VelX = player.floorSpeedX;

}

//vertical movement
if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_SPACE) ){

    playerJump();

}

if(IsKeyDown(KEY_S) && !player.grounded){

    player.gravityModifier = 3;
    
}

if(IsKeyPressed(KEY_R)){
    player.X = 32;
    player.Y = 32;
    player.VelY = 0;
    player.VelX = 0;
}

if(IsKeyPressed(KEY_C)){
    if(cameraMode == 1){
        cameraMode = 0;
    }
    if(cameraMode == 0){
        cameraMode = 1;
    }
}


}

}

void RunLogic() {
mouseX = GetMousePosition().x;
mouseY = GetMousePosition().y;
if(IsKeyDown(KEY_UP)){
    PlayerVector.y -= 256*GetFrameTime();
}
if(IsKeyDown(KEY_LEFT)){
    PlayerVector.x -= 256*GetFrameTime();
}
if(IsKeyDown(KEY_DOWN)){
    PlayerVector.y += 256*GetFrameTime();
}
if(IsKeyDown(KEY_RIGHT)){
    PlayerVector.x += 256*GetFrameTime();
}
if(IsKeyPressed(KEY_ONE)){
    tileSelection = 1;
}
if(IsKeyPressed(KEY_ZERO)){
    tileSelection = 0;
}
if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
int coordToTileX = mouseX/tileWidth;
int coordToTileY = mouseY/tileHeight;
levelArray[coordToTileY][coordToTileX] = tileSelection;
}

if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
    DrawLine(mouseX, mouseY, PlayerVector.x, PlayerVector.y, WHITE);
    DrawCircle(RayCollideRec(PlayerVector.x, PlayerVector.y, mouseX, mouseY).x, RayCollideRec(PlayerVector.x, PlayerVector.y, mouseX, mouseY).y, 4, YELLOW);
}

//player logic
player.runGravityPhysics();
player.runPlayerPhysics();

//jumplogic
if(bufferJumpTimer > 0){
    bufferJumpTimer--;
}

if(player.jumping == true){

    if(IsKeyUp(KEY_W)){
       //if player is moving up, double the force of gravity until they're not moving up, then apply normal gravity
        if(player.VelY < 0){
        player.gravityModifier = 2.5;
        }

        

    }

    if(player.VelY >= 0){
            player.gravityModifier = 1;
        }

    if(player.grounded){
        player.jumping = false;
        player.gravityModifier = 1;
        }

    if(player.grounded && bufferJumpTimer > 0){
        playerJump();
    } 

}

}

void DrawLevel(){

    for(int y = 0; y < levelHeight; y++){

        for(int x = 0; x < levelWidth; x++){

            //checks the level array values to see what tile to print

            if(levelArray[y][x] == 1){
            //for some reason, wallTile number 10 thinks its y value is at zero. this is an issue.
            DrawRectangle(x*tileWidth, y*tileHeight, tileWidth, tileHeight, GRAY);

            
            }
        }
    }
}

void drawPlayer() {

DrawRectangle(player.getLeftOf(), player.getTopOf(), player.SizeX, player.SizeY, player.playerColor);
DrawCircle(player.X, player.Y, 4, RED);
}

void DrawGame(){

DrawCircle(PlayerVector.x, PlayerVector.y, 4, RED);
DrawCircle(GetMouseX(), GetMouseY(), 4, GREEN);
drawPlayer();
DrawLevel();


}

int main()
{

    const int screenWidth = 1280;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Platformer Raycasting Prototype");
    SetTargetFPS(60);
    SetupGame();
    SetupLevel();
    while (!WindowShouldClose())
    {
        BeginDrawing();
       // MoveCamera();
        ClearBackground(BLACK);
        takeInput();
        RunLogic();
        DrawGame();
        EndDrawing();
       // EndMode2D();
    }

    CloseWindow();
    return 0;
}