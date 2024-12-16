#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include <raylib/raylib.h>
#include <raylib/raymath.h>

#define WIDTH 1000
#define HEIGHT 800
#define FACTOR 1
#define ITERATIONS 200

typedef struct {
    double r; // real component
    double i; // imaginary component
} Complex;

Complex pow2c(Complex z) {
    // (a + bi)^2 = a^2 - b^2 + 2abi
    double a = z.r;
    double b = z.i;
    return (Complex){ .r = a*a - b*b, .i = 2 * a * b };
}

Complex addc(Complex z1, Complex z2) {
    return (Complex){ .r = z1.r + z2.r, .i = z1.i + z2.i };
}

double absc(Complex z) {
    // |(a + bi)| = sqrt(a^2 + b^2)
    double a = z.r;
    double b = z.i;
    return sqrt(a*a + b*b);
}

int main() {
    InitWindow(WIDTH, HEIGHT, "Mandelbrot set visualization in C");

    int w = WIDTH * FACTOR;
    int h = HEIGHT * FACTOR;

    // image data WIDTH x HEIGHT x 3 (RGBA)
    char *data = malloc(w * h * 4);

    Image image = {
        .data = data,
        .width = w,
        .height = h,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };

    ImageClearBackground(&image, BLACK);

    // iterate every pixel
    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            // map screen coordinates to x = [-2, 1] & y = [-1, 1]
            double nx = (double)x / image.width * 3.0f - 2.0f; // -2..1
            double ny = (double)y / image.height * 2.0f - 1.0f; // -1..1

            Complex c = { nx, ny };
            Complex z = { 0, 0 };

            ImageDrawPixel(&image, x, y, BLACK);

            for (int i = 0; i < ITERATIONS; i++) {
                z = addc(pow2c(z), c);

                if (absc(z) > 100000) {
                    float v = (float)i / ITERATIONS;

                    Color c = ColorFromHSV(v * 360, 0.75, 1.0);

                    ImageDrawPixel(&image, x, y, c);
                    break;
                }
            }
        }
    }

    Texture2D texture = LoadTextureFromImage(image);

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawTexturePro(
            texture,
            (Rectangle) {0, 0, texture.width, texture.height},
            (Rectangle) {0, 0, WIDTH, HEIGHT},
            (Vector2) {0},
            0,
            WHITE
        );

        EndDrawing();
    }

    UnloadTexture(texture);

    free(data);

    CloseWindow();
    return 0;
}