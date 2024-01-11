#include <stdio.h>
#include <math.h>

void clearScreen()
{
#if defined(_WIN32) || defined(_WIN64)
     system("cls");
#elif defined (__APPLE__) || defined(__linux__) 
     system("clear");
#endif
}

float calculateRatio(float area, float perimeter) {
    return area / perimeter;
}

void compareShapes(float perimeter) {
    float square_length, area_square, ratio_square;
    float triangle_length, area_triangle, ratio_triangle;
    float hexagon_length, area_hexagon, ratio_hexagon;

    square_length = perimeter / 4;
    area_square = square_length * square_length;
    
    triangle_length = perimeter / 3;
    area_triangle = (sqrt(3) / 4) * triangle_length * triangle_length;
    
    hexagon_length = perimeter / 6; 
    area_hexagon = (3 * sqrt(3) / 2) * hexagon_length * hexagon_length;
   
    printf("\n\tPerimeter: %.2f", perimeter);
    printf("\n\t--------------\n");
    printf("\tLength of each sides of the shape: \n");
    printf("\tSquare:   %.2f\n", square_length);
    printf("\tTriangle: %.2f\n", triangle_length);
    printf("\tHexagon:  %.2f\n", hexagon_length);
    printf("\t--------------\n");
    printf("\tArea of each shape:\n");
    printf("\tSquare:   %.2f\n", area_square);
    printf("\tTriangle: %.2f\n", area_triangle);
    printf("\tHexagon:  %.2f\n", area_hexagon);
    printf("\t--------------\n");
   
    
    ratio_square = calculateRatio(area_square, perimeter);
    ratio_triangle = calculateRatio(area_triangle, perimeter);
    ratio_hexagon = calculateRatio(area_hexagon, perimeter);
    
    printf("\tRatio of Area to Perimeter:\n");
    printf("\tSquare:   %.2f\n", ratio_square);
    printf("\tTriangle: %.2f\n", ratio_triangle);
    printf("\tHexagon:  %.2f\n", ratio_hexagon);
    printf("\t--------------\n");
    
    if (ratio_hexagon > ratio_square && ratio_hexagon > ratio_triangle) 
    {
        printf("\nA regular hexagon is the most efficient shape for a honeycomb.\n\n");
    } 
    else 
    {
        printf("\nAnother shape is more efficient than a hexagon for a honeycomb.\n\n");
    }
}

int main() 
{
    float perimeter;

    clearScreen();

    printf("Enter the Perimeters of the shapes: ");
    scanf("%f", &perimeter);

    clearScreen();
    compareShapes(perimeter);

    return 0;
}