/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#pragma warning( push , 0)
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>

#pragma warning(pop)

#include "Vector3.h"
#include "Matrix3.h"

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Tank Game");

	// load tank hull/turret image and rotate it to match the forward direction of the tank in our matrix system
    Image tankHull = LoadImage("Tank_TopDown_Asset_By_Lesik/t34/t34_hull.png");
    ImageRotateCW(&tankHull);
	Image tankTurret = LoadImage("Tank_TopDown_Asset_By_Lesik/t34/t34_turret.png");
	ImageRotateCW(&tankTurret);

	// load bullet image and rotate it to match the forward direction of the tank in our matrix system
	Image bullet = LoadImage("Tank_TopDown_Asset_By_Lesik/bullet/bullet.png");
	ImageRotateCW(&bullet);

	// create a texture from the image and unload the image from CPU memory
    Texture2D textureHull = LoadTextureFromImage(tankHull);
    UnloadImage(tankHull);
	Texture2D textureTurret = LoadTextureFromImage(tankTurret);
	UnloadImage(tankTurret);

    // bullet texture
	Texture2D textureBullet = LoadTextureFromImage(bullet);
	UnloadImage(bullet);

	// transformation variables
	float hullRotation = 0.0f; // total world rotation of the hull in radians
	float rotationSpeed = 2.0f;
	float turretRotation = 0.0f; // local rotation of the turret in radians
	float rotationSpeedTurret = 3.0f;

	MathLibrary::Vector3 position(screenWidth / 2.0f, screenHeight / 2.0f, 0.0f); // position of the tank in world space
    float moveSpeed = 100.0f;

    MathLibrary::Vector3 bulletPosition(0.0f, 0.0f, 0.0f); // position of the bullet in world space
	bool bulletFired = false;
	MathLibrary::Vector3 bulletVelocity(0.0f, 0.0f, 0.0f); // velocity of the bullet in world space
	float bulletSpeed = 300.0f;
	float bulletRotation = 0.0f; // rotation of the bullet in radians

	Vector2 enemyPosition = { 100.0f, 100.0f }; // position of the enemy in world space
	float enemyRadius = 40.0f; // radius of the enemy for collision detection

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        float deltaTime = GetFrameTime();
        // create base rotation matrix of hull and get forward direction for tank's local x-axis
        MathLibrary::Matrix3 rotationMatrix = MathLibrary::Matrix3::MakeRotate(hullRotation);
        MathLibrary::Vector3 forward = rotationMatrix.GetForward();

		// create world matrices for hull and turret (turret is relative to hull)
		MathLibrary::Matrix3 hullWorldMatrix = MathLibrary::Matrix3::MakeTranslate(position) * rotationMatrix;
		MathLibrary::Matrix3 turretWorldMatrix = hullWorldMatrix * MathLibrary::Matrix3::MakeRotate(turretRotation);

        // handle position movement in the forward direction of the hull
        if (IsKeyDown(KEY_W)) position += forward * moveSpeed * deltaTime;
        if (IsKeyDown(KEY_S)) position -= forward * moveSpeed * deltaTime;
		// handle input for rotation
        if (IsKeyDown(KEY_D)) hullRotation += rotationSpeed * deltaTime;
        if (IsKeyDown(KEY_A)) hullRotation -= rotationSpeed * deltaTime;
		if (IsKeyDown(KEY_E)) turretRotation += rotationSpeedTurret * deltaTime;
		if (IsKeyDown(KEY_Q)) turretRotation -= rotationSpeedTurret * deltaTime;

        // handle bullet input and projection
        if (IsKeyDown(KEY_SPACE) && !bulletFired)
        {
			bulletFired = true;

			MathLibrary::Vector3 bulletOffset = turretWorldMatrix.GetForward() * (textureTurret.height / 2.0f); // offset to spawn bullet at the end of the turret
			bulletPosition = turretWorldMatrix.GetTranslate() + bulletOffset; // spawn bullet at the end of the turret
			bulletRotation = hullRotation + turretRotation; // set bullet angle to current turret angle on fire

			bulletVelocity = turretWorldMatrix.GetForward() * bulletSpeed; // set bullet velocity in the forward direction of the turret
        }

        if (bulletFired)
        {
			// move bullet independently in world space
			bulletPosition += bulletVelocity * deltaTime;

            if (bulletPosition.x < 0 || bulletPosition.x > screenWidth || bulletPosition.y < 0 || bulletPosition.y > screenHeight)
            {
				bulletFired = false; // destroy bullet if it goes off-screen
			}

            if (CheckCollisionCircles({bulletPosition.x, bulletPosition.y}, 5.0f, enemyPosition, enemyRadius))
            {
                bulletFired = false; // destroy bullet if it hits the enemy
            }
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

		// shared source rectangle for both hull and turret
        Rectangle sourceRec = { 0.0f, 0.0f, (float)textureHull.width, (float)textureHull.height };
		Rectangle bulletSourceRec = { 0.0f, 0.0f, (float)textureBullet.width, (float)textureBullet.height };

		// origins for rotation (center of the texture)
		Vector2 hullOrigin = { (float)textureHull.width / 2.0f, (float)textureHull.height / 2.0f };
		Vector2 turretOrigin = { (float)textureTurret.width / 2.0f, (float)textureTurret.height / 2.0f };

		// convert hull rotation from radians to degrees for raylib's DrawTexturePro function
        float hullDegrees = hullRotation * (180.0f / PI);
        DrawTexturePro(textureHull, sourceRec, { position.x, position.y, (float)textureHull.width, (float)textureHull.height }, hullOrigin, hullDegrees, WHITE); // draw the tank hull texture with current rotation

		// visual rotation is the sum of hull rotation and turret rotation
		float totalTurretDegrees = (hullRotation + turretRotation) * (180.0f / PI);
		DrawTexturePro(textureTurret, sourceRec, { position.x, position.y, (float)textureTurret.width, (float)textureTurret.height }, turretOrigin, totalTurretDegrees, WHITE); // draw the tank turret texture with current rotation

        // enemy circle
		DrawCircle(enemyPosition.x, enemyPosition.y, enemyRadius, PINK);

		// draw the bullet
        if (bulletFired)
        {
            DrawTexturePro(textureBullet, bulletSourceRec, { bulletPosition.x, bulletPosition.y, (float)textureBullet.width, (float)textureBullet.height }, { (float)textureBullet.width / 2.0f, (float)textureBullet.height / 2.0f }, bulletRotation * (180.0f / PI), WHITE);
        }

        DrawText("Use WASD to move, QE to rotate turret and space to fire bullet", 10, 10, 20, GRAY);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}